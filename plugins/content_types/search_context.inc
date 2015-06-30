<?php

$plugin = array(
  'title' => t('Ting search - search context'),
  'description' => t('Show a number or nodes with relevant info'),
  'single' => TRUE,
  'content_types' => array('search_context'),
  'render callback' => 'search_context_content_type_render',
  'category' => t('Ting'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function search_context_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  // Add ajax-js and the search context to Drupal.settings
  $search_results = drupal_static('ting_search_results');
  if ($search_results) {
    ting_search_context_set_search_context($search_results);
  }
  // Add position settings to Drupal.settings
  ting_search_context_set_position();

  // Empty block to be filled by an ajax callback
  $block->content = '<!--Related content container. Ajax callback fills it.-->';
  return $block;
}

/**
 * Add the search context to Drupal.settings for later use in the ajax request
 * Add js that loads the related content in an ajax request
 */
function ting_search_context_set_search_context($search_results) {
  module_load_include('search_context.inc', 'ting_search_context');
  $context = ting_search_context_calculate_context($search_results->facets, $search_results->numTotalObjects);

  drupal_add_js(drupal_get_path('module', 'ting_search_context') . '/js/ting_search_context.js');
  drupal_add_js(array('ting_search_context' => $context), 'setting');
}

/**
 * Add the value of the related content position-setting on the search page to Drupal.settings
 */
function ting_search_context_set_position() {
  $position = variable_get('ting_search_context_position', 'js-below-search-result');
  drupal_add_js(array('ting_search_context_position' => $position), 'setting');
}





/**
 * Enable admin settings page
 */
function ting_search_context_search_context_content_type_edit_form($form, &$form_state) {
  return $form;
}

