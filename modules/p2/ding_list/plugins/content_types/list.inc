<?php

/**
 * @file
 * Information about list info pane.
 */

$plugin = array(
  'title' => t('View list'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_content_type_render',
  'required context' => new ctools_context_required(t('Ding list'), 'ding_list_list'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();
  $block->content = array(
    '#theme' => 'ding_list_list',
    '#display' => 'view list',
    '#list' => $list,
  );

  return $block;
}
