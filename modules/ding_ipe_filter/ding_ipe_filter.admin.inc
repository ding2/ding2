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
  $form['ding_ipe_filter_table'] = array(
    '#theme' => 'ding_ipe_filter_table',
    '#header' => array(t('Content'), t('Show')),
  );

  $settings = variable_get('ding_ipe_filter_table', array());
  foreach ($categories as $key => $category) {
    $form['ding_ipe_filter_table'][$key] = array(
      '#type' => 'item',
      '#markup' => $category['title'],
    );
    foreach ($category['content'] as $content) {
      $form['ding_ipe_filter_table'][$content['subtype_name']]['title'] = array(
        '#type' => 'item',
        '#markup' => $content['title'],
      );
      $value = 0;
      if (isset($settings[$content['subtype_name']]['value']) && $settings[$content['subtype_name']]['value'] == 1) {
        $value = 1;
      }
      $form['ding_ipe_filter_table'][$content['subtype_name']]['value'] = array(
        '#type' => 'checkbox',
        '#default_value' => $value,
      );
      $form['ding_ipe_filter_table'][$content['subtype_name']]['category'] = array(
        '#type' => 'hidden',
        '#value' => $key,
      );
      $form['ding_ipe_filter_table'][$content['subtype_name']]['delta'] = array(
        '#type' => 'hidden',
        '#value' => $content['title'],
      );
      $form['ding_ipe_filter_table'][$content['subtype_name']]['type'] = array(
        '#type' => 'hidden',
        '#value' => $content['type_name'],
      );
      $form['ding_ipe_filter_table'][$content['subtype_name']]['subtype'] = array(
        '#type' => 'hidden',
        '#value' => $content['subtype_name'],
      );
    }
  }

  return system_settings_form($form);
}
