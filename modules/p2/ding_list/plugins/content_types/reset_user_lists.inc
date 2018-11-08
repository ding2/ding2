<?php

/**
 * @file
 * Add list form pane.
 */

$plugin = array(
  'title' => t('Reset user lists'),
  'description' => t('Reset all lists.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Ding!'),
  'render callback' => 'ding_list_reset_user_lists_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_reset_user_lists_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = drupal_get_form('ding_list_reset_user_form', $context->data);

  return $block;
}
