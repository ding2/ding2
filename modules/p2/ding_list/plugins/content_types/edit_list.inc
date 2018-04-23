<?php

/**
 * @file
 * Edit list form pane.
 */

$plugin = array(
  'title' => t('Edit ding list'),
  'description' => t('Edit list.'),
  'single' => TRUE,
  'category' => t('Ding!'),
  'render callback' => 'ding_list_edit_list_content_type_render',
  'required context' => new ctools_context_required(t('Ding list'), 'ding_list_list'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_edit_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();
  $block->title = check_plain($list->getTitle());
  $block->content = array(drupal_get_form('ding_list_edit_list_form', $list));

  return $block;
}
