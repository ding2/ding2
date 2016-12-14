<?php
/**
 * @file
 * Permissions form pane.
 */

$plugin = array(
  'title' => t('Share ding list'),
  'description' => t('Share list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_share_list_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_share_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();
  $block->title = check_plain(entity_label('ding_type', $list));
  $block->content = drupal_get_form('ding_list_list_permissions_form', $list);

  return $block;
}
