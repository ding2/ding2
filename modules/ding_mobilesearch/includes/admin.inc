<?php

/**
 * @file
 * Mobilesearch administration and plugins settings UI.
 */

/**
 * Content exporting settings form.
 */
function ding_mobilesearch_settings($form, &$form_state) {
  $form['export'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export'),
    '#description' => t('Specify the node types which should be exported.'),
  );

  // Content types exporting settings.
  $form['export']['types'] = array(
    '#theme' => 'ding_mobilesearch_types_table',
    '#tree' => TRUE,
  );
  $names = node_type_get_names();

  $base_trigger = array(
    'hook_node_insert' => t('Node hooks (insert, update, delete)'),
  );
  $workflow_enabled = module_exists('workflownode');
  if ($workflow_enabled) {
    $type_map = workflow_get_workflow_type_map();
  }

  $plugin_info = module_invoke_all('ding_mobilesearch_plugin_info');
  $plugins = array();
  foreach ($plugin_info as $key => $info) {
    $plugins[$key] = $info['title'];
  }
  foreach ($names as $machine_name => $name) {
    $trigger = $base_trigger;
    if ($workflow_enabled) {
      if (!empty($type_map[$machine_name])) {
        $wid = $type_map[$machine_name];
        $workflow = workflow_load($wid);
        foreach ($workflow->states as $state) {
          if ($state->name == '(creation)') {
            continue;
          }
          $trigger['hook_workflow__' . $state->name] = $state->state;
        }
      }
    }

    $key = 'mobilesearch_type__' . $machine_name;
    $form['export']['types']['rows'][$machine_name]['type'] = array(
      '#type' => 'checkbox',
      '#title' => $name,
      '#default_value' => variable_get($key, FALSE),
    );
    $form['export']['types']['rows'][$machine_name]['trigger'] = array(
      '#type' => 'radios',
      '#options' => $trigger,
      '#default_value' => variable_get($key . '__trigger', 'hook_node_insert'),
    );
    $form['export']['types']['rows'][$machine_name]['plugin'] = array(
      '#type' => 'select',
      '#options' => $plugins,
      '#default_value' => variable_get($key . '__plugin', NULL),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for the settings form.
 */
function ding_mobilesearch_settings_submit($form, &$form_state) {
  $types = $form_state['values']['types']['rows'];

  // Assing CT's with flag (if possible).
  if (module_exists('flag')) {
    $flag = flag_get_flag('push_to_mongo');
    if ($flag !== FALSE) {
      db_delete('flag_types')
        ->condition('fid', $flag->fid)
        ->execute();
      foreach ($types as $machine_name => $row) {
        if ($row['type']) {
          db_insert('flag_types')
            ->fields(array(
              'fid' => $flag->fid,
              'type' => $machine_name,
            ))
            ->execute();
        }
      }
    }
  }

  // Save CT's settings.
  foreach ($types as $machine_name => $row) {
    $key = 'mobilesearch_type__' . $machine_name;
    variable_set($key, $row['type']);
    variable_set($key . '__trigger', $row['trigger']);
    variable_set($key . '__plugin', $row['plugin']);
  }

  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Content exporting plugins settings form.
 */
function ding_mobilesearch_plugin_settings($form, &$form_state) {
  $form['vt'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );

  $plugin_info = module_invoke_all('ding_mobilesearch_plugin_info');
  foreach ($plugin_info as $plugin => $info) {
    $config_form_func = $info['config_form_callback'];
    if (function_exists($config_form_func)) {
      $form['plugin__' . $plugin] = array(
        '#type' => 'fieldset',
        '#title' => $info['title'],
        '#description' => $info['description'],
        '#group' => 'vt',
      );
      $form['plugin__' . $plugin] += $config_form_func($form['plugin__' . $plugin], $form_state);
    }
    if (!empty($info['config_form_validate']) && function_exists($info['config_form_validate'])) {
      $form['#validate'][] = $info['config_form_validate'];
    }
    if (!empty($info['config_form_submit']) && function_exists($info['config_form_submit'])) {
      $form['#submit'][] = $info['config_form_submit'];
    }
  }

  return system_settings_form($form);
}
