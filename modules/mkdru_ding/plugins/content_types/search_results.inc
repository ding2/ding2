<?php
/**
 * @file
 * Search result pane plugin.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Mkdru DING! search results'),
  'description' => t('The results of a search using keywords.'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
  'render callback' => 'mkdru_ding_search_result_render',
  'edit form' => 'mkdru_ding_search_result_edit_form',
  'category' => t('MKDRU'),
);

/**
 * Render callback.
 */
function mkdru_ding_search_result_render($subtype, $conf, $args, $context) {
  $search_info = search_get_info();
  if (empty($search_info['mkdru_ding'])) {
    return;
  }
  $info = $search_info['mkdru_ding'];

  $keys = NULL;
  if (!empty($context) && isset($context->data)) {
    $keys = $context->data;
  }

  // Build the content type block.
  $block = new stdClass();

  $results = '';
  $conditions = array();

  // Collect the search results.
  $results = search_data($keys, $info['module'], $conditions);
  $block->content = theme('mkdru_results');

  return $block;
}

/**
 * Edit form callback.
 */
function mkdru_ding_search_result_edit_form($form, &$form_state) {
  return $form;
}
