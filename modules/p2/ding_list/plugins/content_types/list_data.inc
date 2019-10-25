<?php

/**
 * @file
 * Information about list data pane.
 */

$plugin = array(
  'title' => t('Ding list data'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_data_content_type_render',
  'required context' => new ctools_context_required(t('Ding list'), 'ding_list_list'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_data_content_type_render($subtype, $conf, $panel_args, $context) {
  
  $list = $context->data;

  $block = new stdClass();
  $block->content = array(
    '#theme' => 'ding_list_data',
    '#list' => $list,
  );

  return $block;
}
