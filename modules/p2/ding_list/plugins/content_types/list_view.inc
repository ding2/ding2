<?php

/**
 * @file
 * View a list pane.
 */

$plugin = array(
  'title' => t('Ding list_view'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_view_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_view_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();
  $block->title = entity_label('ding_type', $list);
  module_load_include('inc', 'ding_list', 'ding_list.pages');
  // @TODO: ding_list_list_page() function doesn't seem to exist?
  $block->content[] = ding_list_list_page($list);

  return $block;
}
