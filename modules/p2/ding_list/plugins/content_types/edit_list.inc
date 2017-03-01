<?php

/**
 * @file
 * Edit list form pane.
 */

$plugin = array(
  'title' => t('Edit ding list'),
  'description' => t('Edit list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Ding!'),
  'render callback' => 'ding_list_edit_list_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_edit_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();
  $block->title = check_plain(entity_label('ding_type', $list));
  $block->content = array(drupal_get_form('ding_list_create_list_form', $list));

  return $block;
}
