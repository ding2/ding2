<?php
/**
 * @file
 * Admin forms definition.
 */

/**
 * Defines pane list form.
 */
function ding_ipe_filter_admin_panes_form() {
  ctools_include('content');
  $content_types = ctools_content_get_available_types();
  $panel_editor = new panels_renderer_editor();
  $categories = $panel_editor->get_categories($content_types);

  $form = array('#tree' => TRUE);
  $form['ding_ipe_filter_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration settings'),
  );
  $configs = variable_get('ding_ipe_filter_settings', array());
  $form['ding_ipe_filter_settings']['admin_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display IPE menu for super admin'),
    '#default_value' => !empty($configs['admin_display']) ? $configs['admin_display'] : 0,
  );
  $form['ding_ipe_filter_table'] = array(
    '#theme' => 'ding_ipe_filter_table',
    '#header' => array('', t('Content'), t('Show'), t('Weight')),
    '#type' => 'fieldset',
    '#title' => t('Menu items'),
    '#collapsible' => TRUE,
    '#collapsed' => 'collapsed',
  );

  // Update settings variable.
  $settings = variable_get('ding_ipe_filter_table', array());
  foreach ($categories as $key => $category) {
    foreach ($category['content'] as $content) {
      $settings[$content['subtype_name']] = array(
        'value' => (!empty($settings[$content['subtype_name']]['value'])) ? $settings[$content['subtype_name']]['value'] : 0,
        'weight' => (!empty($settings[$content['subtype_name']]['weight'])) ? $settings[$content['subtype_name']]['weight'] : 0,
        'category' => $key,
        'title' => $content['title'],
        'type' => $content['type_name'],
        'subtype' => $content['subtype_name'],
      );
    }
  }

  foreach ($settings as $key => $setting) {
    $form['ding_ipe_filter_table'][$setting['subtype']]['delta'] = array(
      '#type' => 'item',
      '#markup' => $setting['title'],
      '#value' => $setting['title'],
    );
    $form['ding_ipe_filter_table'][$setting['subtype']]['value'] = array(
      '#type' => 'checkbox',
      '#default_value' => $setting['value'],
    );
    $form['ding_ipe_filter_table'][$setting['subtype']]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => $settings[$setting['subtype']]['weight'] ? $settings[$setting['subtype']]['weight'] : 0,
    );
    $form['ding_ipe_filter_table'][$setting['subtype']]['title'] = array(
      '#type' => 'hidden',
      '#value' => $setting['title'],
    );
    $form['ding_ipe_filter_table'][$setting['subtype']]['category'] = array(
      '#type' => 'hidden',
      '#value' => $setting['category'],
    );
    $form['ding_ipe_filter_table'][$setting['subtype']]['type'] = array(
      '#type' => 'hidden',
      '#value' => $setting['type'],
    );
    $form['ding_ipe_filter_table'][$setting['subtype']]['subtype'] = array(
      '#type' => 'hidden',
      '#value' => $setting['subtype'],
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Filter variables and save form.
 */
function ding_ipe_filter_admin_panes_form_submit($form, &$form_state) {
  $table = $form_state['values']['ding_ipe_filter_table'];

  if (!empty($table)) {
    uasort($table, 'drupal_sort_weight');
  }

  $table = array_filter($table, function ($setting) {
    return ($setting['value']);
  });

  variable_set('ding_ipe_filter_settings', $form_state['values']['ding_ipe_filter_settings']);
  variable_set('ding_ipe_filter_table', $table);
}
