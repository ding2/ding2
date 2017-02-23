<?php

/**
 * @file
 * Provides related content as a Panels content type.
 */

$plugin = array(
  'title' => t('Ting search context'),
  'description' => t('Display nodes related to the current search context'),
  'single' => TRUE,
  'content_types' => array('search_context'),
  'render callback' => 'ting_search_context_search_context_content_type_render',
  'category' => t('Ting'),
  'render last' => TRUE,
);

/**
 * Return the pane contents.
 */
function ting_search_context_search_context_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // Calculate context.
  $search_results = drupal_static('ting_search_results');
  if ($search_results) {
    module_load_include('search_context.inc', 'ting_search_context');
    $context_id = ting_search_context_calculate_context($search_results->facets, $search_results->numTotalObjects, $search_results->search_key);

    // Get position setting.
    $position = variable_get('ting_search_context_position', 'js-below-search-result');

    // Empty block to be filled by an ajax callback.
    $block->content = theme('ting_search_context', array('context_id' => $context_id, 'position' => $position));

  } else {
    $block->content = '';
  }
  return $block;
}

/**
 * Return the pane titles.
 */
function ting_search_context_search_context_content_type_admin_title($subtype, $conf, $context) {
  return t('Ting search context');
}

/**
 * Returns an edit form for the content type.
 */
function ting_search_context_search_context_content_type_edit_form($form, &$form_state) {
  return $form;
}
