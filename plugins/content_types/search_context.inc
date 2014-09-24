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
  $search_results = drupal_static('ting_search_results');
  if ($search_results) {
    ting_search_context_set_search_context($search_results);
  }
  $block->content = '<div id="ting-search-context"> </div>';
  return $block;
}

function ting_search_context_set_search_context($search_results) {
  module_load_include('search_context.inc', 'ting_search_context');
  $context = ting_search_context_calculate_context($search_results->facets, $search_results->numTotalObjects); 
  $js_settings = array(
    'searchcontext' => $context,
    'path' => '/ting/searchcontext/ajax'
  );
  drupal_add_js(drupal_get_path('module', 'ting_search_context') . '/js/ting_search_context.js');
  drupal_add_js(array('ting_search_context' => $context), 'setting');
}

/**
 * Enable admin settings page
 */
function ting_search_context_search_context_content_type_edit_form($form, &$form_state) {
  return $form;
}

