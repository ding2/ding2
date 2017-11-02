<?php
/**
 * @file
 * Admin forms definition.
 */

/**
 * Defines pane list form.
 */
function ding_ipe_filter_admin_panes_form($form, $form_state) {
  $form = array();

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

  $form['ding_ipe_filter_panes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available panel panes'),
    '#description' => t('Select the panel panes that should be available in the editor when clicking the "add" buttons.'),
  );

  // Select table header definition.
  $header = array(
    'category' => t('Category'),
    'type' => t('Type'),
    'title' => t('Title'),
    'description' => t('Description'),
  );

  // Get all panes based on their categories.
  ctools_include('content');
  $content_types = ctools_content_get_available_types();
  $panel_editor = new panels_renderer_editor();
  $categories = $panel_editor->get_categories($content_types);

  $options = array();
  foreach ($categories as $key => $category) {
    foreach ($category['content'] as $content) {
      $options[$key . ':' . $content['subtype_name']] = array(
        'category' => $category['title'],
        'type' => $content['subtype_name'],
        'title' => $content['title'],
        'description' => isset($content['description']) ? check_plain($content['description']) : '',
      );
    }
  }

  $form['ding_ipe_filter_panes']['ding_ipe_filter_panes_selected'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#default_value' => _ding_ipe_filter_selected_panes(),
    '#empty' => t('No categories found'),
  );

  return system_settings_form($form);
}
