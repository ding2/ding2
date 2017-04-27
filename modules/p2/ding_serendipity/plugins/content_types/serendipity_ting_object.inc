<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

$plugin = array(
  'title' => t('Ding serendipity with TingObject'),
  'description' => t('Display serendipity content of type the ting object.'),
  'admin info' => 'ding_serendipity_serendipity_ting_object_admin_info',
  'single' => TRUE,
  'required context' => array(
    new ctools_context_optional(t('Node'), 'node'),
    new ctools_context_optional(t('Search term'), 'string'),
    new ctools_context_optional(t('Taxonomy terms'), 'terms'),
    new ctools_context_optional(t('Ting object'), 'ting_object'),
  ),
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration information in panels.
 */
function ding_serendipity_serendipity_ting_object_admin_info($subtype, $conf, $context) {
  return ding_serendipity_get_default_admin_info($subtype, $conf, $context);
}

/**
 * Implements hook_content_type_render().
 */
function ding_serendipity_serendipity_ting_object_content_type_render($subtype, $conf, $panel_args, $context) {
  // Only show on front if serendipity is enabled for the frontpage.
  // See ding_frontpage config at /admin/config/ding/frontend.
  if (isset($conf['selected_keys']['frontpage']) && !variable_get('ding_frontpage_serendipity') && variable_get('ding_frontpage_promoter') != 'serendipity') {
    return;
  }

  $context_data = array();
  if (isset($conf['selected_keys'])) {
    foreach ($conf['selected_keys'] as $key => $value) {
      $context_data[$key] = TRUE;
    }
  }

  if (!empty($context[0]->data)) {
    $context_data['node'] = $context[0]->data;
    $context_data['node_nid'] = $panel_args[0];
  }

  if (!empty($context[1]->data)) {
    $context_data['search_term'] = $context[1]->data;
  }

  if (!empty($context[2]->data)) {
    $context_data['taxonomy_term'] = $context[2]->data;
    $context_data['taxonomy_tid'] = $panel_args[0];
  }

  if (!empty($context[3]->data)) {
    $context_data['ting_object'] = $context[2]->data;
    $context_data['ting_object_id'] = $panel_args[0];
  }

  $context_data += array(
    'view_mode' => isset($conf['view_mode']) ? $conf['view_mode'] : 'compact',
    'sort_weight' => isset($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => isset($conf['max']) ? $conf['max'] : 0,
    'min' => isset($conf['min']) ? $conf['min'] : 0,
    'random' => isset($conf['random']) ? $conf['random'] : FALSE,
    'bundle' => 'ting_object',
  );

  $content = ding_serendipity_render($context_data);

  $output = array();
  if (!empty($content)) {

    $path = drupal_get_path('module', 'ding_serendipity');

    $output['#attached']['library'][] = array('system', 'drupal.ajax');
    $output['#attached']['css'][] = $path . '/css/ding_serendipity.css';
    $output['#attached']['js'][] = $path . '/js/ding_serendipity.js';
    $output['#attached']['js'][] = array(
      'data' => array(
        'ding_serendipity' => array('context' => $context_data),
      ),
      'type' => 'setting',
    );

    $tmp = array();
    foreach ($content as $key => $item) {
      $item['#weight'] = $key;
      $tmp[] = $item;
    }

    $output['content'][] = array(
      '#theme' => 'ting_carousel',
      '#objects' => $tmp,
    );
  }

  $block = new stdClass();
  $block->title = t('Serendipity materials');
  $block->content = $output;

  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_serendipity_ting_object_content_type_edit_form($form, &$form_state) {

  $form += ding_serendipity_form_base($form_state);
  $form += ding_serendipity_form_base_keys($form_state);

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_serendipity_serendipity_ting_object_content_type_edit_form_validate($form, &$form_state) {
  if (!isset($form_state['values']['selected_keys']) || empty($form_state['values']['selected_keys'])) {
    form_error($form['selected_keys'], t('Please specify some keys for the serendipity filter.'));
  }
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_serendipity_ting_object_content_type_edit_form_submit($form, &$form_state) {
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['selected_keys'] = !empty($form_state['values']['selected_keys']) ? $form_state['values']['selected_keys'] : FALSE;
}
