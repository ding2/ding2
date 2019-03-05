<?php

/**
 * @file
 * Add search to list button.
 */

$plugin = array(
  'title' => t('Add search to list'),
  'description' => t('Add search query to list.'),
  'single' => TRUE,
  // 'content_types' => array('list'),.
  'content_types' => array('ting_search'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_search_query_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_search_query_content_type_render($subtype, $conf, $panel_args, $context) {
  $render_variables = ding_list_search_query_add_button($context);

  if (empty($render_variables)) {
    return NULL;
  }

  $block = new stdClass();
  $block->content = $render_variables;

  return $block;
}
