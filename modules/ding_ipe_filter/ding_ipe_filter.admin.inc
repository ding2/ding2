<?php
/**
 * @file
 *
 * ding_ipe_filter.admin.inc
 */

/**
 * Defines pane list form.
 */
function ding_ipe_filter_admin_panes() {
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

/**
 * Defines admin form.
 */
function ding_ipe_filter_default_settings() {
  $form = array();
  $form['filter_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default IPE filter settings.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $roles = user_roles(TRUE);
  // Unset anonymous and authenticated roles.
  unset($roles[1], $roles[2]);

  $ipe_roles = variable_get('ding_ipe_filter_roles', array());
  $form['filter_fieldset']['ding_ipe_filter_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => $roles,
    '#default_value' => $ipe_roles,
  );

  // Clear theme cache for hook_theme_registry_alter implementation.
  $form['#submit'][] = 'drupal_theme_rebuild';

  return system_settings_form($form);
}
