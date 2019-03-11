<?php

/**
 * @file
 * Ding section dashboard administrative interface.
 */

/**
 * Creates an administrative block on the configuration page.
 *
 * It is necessary for grouping various settings.
 *
 * @return string
 *   HTML for the block.
 */
function ding_sections_admin_menu_block_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  if ($content) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }

  return $output;
}

/**
 * Content type selection form.
 *
 * Interface for selecting node types which should be a part
 * of teh section system.
 */
function ding_sections_admin_content_types($form, $form_state) {
  $node_types = node_type_get_types();
  $node_bundles = array();

  foreach ($node_types as $type) {
    $node_bundles[$type->type] = $type->name;
  }

  $form['ding_section_content_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available node types'),
    '#description' => t('Select which nodes should be a part of section system'),
    '#options' => $node_bundles,
    '#default_value' => variable_get('ding_section_content_types', array()),
  );

  $form['#submit'][] = 'ding_sections_admin_content_types_submit';

  return system_settings_form($form);
}

/**
 * Custom submit handler for content types admin form.
 *
 * Create hidden fields for selected content types that will contain
 * section status of the node.
 */
function ding_sections_admin_content_types_submit($form, $form_state) {
  $input = $form_state['input'];
  $node_types = array_filter($input['ding_section_content_types']);
  $last_setting = array_filter(variable_get('ding_section_content_types', array()));

  if (empty($node_types) && empty($last_setting)) {
    return;
  }

  $instance_definition = array(
    'label' => 'Section',
    'field_name' => 'field_ding_section',
    'entity_type' => 'node',
    'required' => 0,
    'default_value' => NULL,
    'widget' => array(
      'type' => 'options_select',
      'module' => 'options',
      'active' => 1,
      'settings' => array(),
    ),
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'display' => array(
      'default' => array(
        'label' => 'above',
        'type' => 'hidden',
        'settings' => array(),
        'module' => '',
      ),
    ),
  );

  // For each selected node bundle, create a field instance and attach it.
  foreach ($node_types as $type) {
    if (!field_read_instance('node', 'field_ding_section', $type)) {
      $instance_definition['bundle'] = $type;

      $t = array(
        '@instance' => $instance_definition['label'],
        '@bundle' => $instance_definition['bundle'],
      );

      $error = FALSE;

      try {
        field_create_instance($instance_definition);
      }
      catch (FieldException $e) {
        $error = TRUE;
        watchdog_exception('ding_sections', $e, t('Exception thrown when creating field instance @instance for bundle @bundle.'), $t, WATCHDOG_CRITICAL);
        drupal_set_message(t('Error when creating field instance <strong>@instance</strong> for bundle <strong>@bundle</strong>.', $t), 'error');
      }

      if (!$error) {
        drupal_set_message(t('Field instance @instance for bundle @bundle <strong>created</strong> successfully.', $t));
      }
    }
  }

  // Cleanup left over fields.
  $left_over = array_diff($last_setting, $node_types);
  foreach ($left_over as $entry) {
    $instance = field_read_instance('node', 'field_ding_section', $entry);

    field_delete_instance($instance, FALSE);

    $t = array(
      '@instance' => $instance['label'],
      '@bundle' => $instance['bundle'],
    );

    drupal_set_message(t('Field instance @instance for bundle @bundle <strong>deleted</strong> successfully.', $t));
  }
}
