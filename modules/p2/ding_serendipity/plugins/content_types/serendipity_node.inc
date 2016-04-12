<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

/**
 * Plugin description.
 */
$plugin = array(
  'title' => t('Ding serendipity content with nodes'),
  'description' => t('Display serendipity content of nodes based on the current entity.'),
  'admin info' => 'ding_serendipity_serendipity_node_admin_info',
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
function ding_serendipity_serendipity_node_admin_info($subtype, $conf, $context) {
  return ding_serendipity_get_default_admin_info($subtype, $conf, $context);
}

/**
 * Implements hook_content_type_render().
 */
function ding_serendipity_serendipity_node_content_type_render($subtype, $conf, $panel_args, $context) {
  $context_data = array();

  // Build a context that can be rendered by the serendipity plugins.
  // Transfer selected keys from panel settings.
  if (isset($conf['selected_keys'])) {
    foreach ($conf['selected_keys'] as $key => $value) {
      $context_data[$key] = TRUE;
    }
  }

  // Transfer current node nid.
  if (!empty($context[0]->data)) {
    $context_data['node'] = $context[0]->data;
    $context_data['node_nid'] = $panel_args[0];
  }
  
  // Insert optional manual search term.
  if (!empty($context[1]->data)) {
    $context_data['search_term'] = $context[1]->data;
  }
  
  // Insert term and tid.
  if (!empty($context[2]->data)) {
    $context_data['taxonomy_term'] = $context[2]->data;
    $context_data['taxonomy_tid'] = $panel_args[0];
  }
  
  // Insert manually selected object ids.
  if (!empty($context[3]->data)) {
    $context_data['ting_object'] = $context[2]->data;
    $context_data['ting_object_id'] = $panel_args[0];
  }

  // Complete the context array.
  $context_data += array(
    'view_mode' => isset($conf['view_mode']) ? $conf['view_mode'] : 'teaser',
    'bundle' => isset($conf['bundle']) ? $conf['bundle'] : 'teaser',
    'sort_weight' => isset($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => isset($conf['max']) ? $conf['max'] : 0,
    'min' => isset($conf['min']) ? $conf['min'] : 0,
    'random' => isset($conf['random']) ? $conf['random'] : FALSE,
  );

  // And render the array.
  $content = ding_serendipity_render($context_data);

  $output = array();
  if (!empty($content)) {
    foreach ($content as $key => $item) {
      $item['#weight'] = $key;
      if (isset($item['#serendipity_info'])) {
        $item['serendipity_info'] = array(
          '#theme' => 'ding_serendipity_info',
          '#title' => t('Serendipity info') . ':',
          '#information' => $item['#serendipity_info'],
          '#weight' => 50,
        );
      }
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
function ding_serendipity_serendipity_node_content_type_edit_form($form, &$form_state) {

  $form += ding_serendipity_form_base($form_state);
  $form += ding_serendipity_form_base_keys($form_state);
    
  $bundles = array();
  foreach ($entity_info['bundles'] as $key => $bundle) {
    $bundles[$key] = $bundle['label'];
  }
  
  $form['bundle'] = array(
    '#type' => 'select',
    '#title' => t('Bundle'),
    '#options' => $bundles,
    '#default_value' => (isset($form_state['conf']['bundle'])) ? $form_state['conf']['bundle'] : '',
    '#description' => t('Select the bundle to list serendipity content for.'),
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_serendipity_serendipity_node_content_type_edit_form_validate($form, &$form_state) {
  if (!isset($form_state['values']['selected_keys']) || empty($form_state['values']['selected_keys'])) {
    form_error($form['selected_keys'], t('Please specify some keys for the serendipity filter.'));
  }
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_serendipity_node_content_type_edit_form_submit($form, &$form_state) {
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['selected_keys'] = !empty($form_state['values']['selected_keys']) ? $form_state['values']['selected_keys'] : FALSE;
  $form_state['conf']['view_mode'] = !empty($form_state['values']['view_mode']) ? $form_state['values']['view_mode'] : FALSE;
  $form_state['conf']['bundle'] = !empty($form_state['values']['bundle']) ? $form_state['values']['bundle'] : FALSE;
}
