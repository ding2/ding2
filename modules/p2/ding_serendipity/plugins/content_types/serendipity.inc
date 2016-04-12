<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

$plugin = array(
  'title' => t('Ding serendipity content'),
  'description' => t('Display serendipity content'),
  'admin info' => 'ding_serendipity_admin_info',
  'single' => TRUE,
  'required context' => array(
    new ctools_context_optional(t('Node'), 'node'),
    new ctools_context_optional(t('Search term'), 'string'),
    new ctools_context_optional(t('Taxonomy terms'), 'terms'),
  ),
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration information in panels.
 */
function ding_serendipity_admin_info($subtype, $conf, $context) {
  return ding_serendipity_get_default_admin_info($subtype, $conf, $context);
}

/**
 * Implements hook_content_type_render().
 */
function ding_serendipity_serendipity_content_type_render($subtype, $conf, $panel_args, $context) {
  $context_data = array();
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
  
  $context_data += array(
    'view_mode' => isset($conf['view_mode']) ? $conf['view_mode'] : 'teaser',
    'sort_weight' => isset($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => isset($conf['max']) ? $conf['max'] : 0,
    'min' => isset($conf['min']) ? $conf['min'] : 0,
    'random' => isset($conf['random']) ? $conf['random'] : FALSE,
  );
  
  if (isset($conf['selected_keys'])) {
    foreach ($conf['selected_keys'] as $key => $value) {
      $context_data[$key] = TRUE;
    }
  }

  $content = ding_serendipity_render($context_data);

  $output = array();
  if (!empty($content)) {
    foreach ($content as $key => $item) {
      $item['#weight'] = $key;
      $output['content'][] = $item;
    }
  }
  
  $block = new stdClass();
  $block->title = t('Serendipity content');
  $block->content = $output;
  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_serendipity_content_type_edit_form($form, &$form_state) {
  
  $form += ding_serendipity_form_base($form_state);
  $form += ding_serendipity_form_base_keys($form_state);

  return $form;
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_serendipity_content_type_edit_form_submit($form, &$form_state) {
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['selected_keys'] = !empty($form_state['values']['selected_keys']) ? $form_state['values']['selected_keys'] : FALSE;
}
