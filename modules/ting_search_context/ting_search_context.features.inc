<?php
/**
 * @file
 * ting_search_context.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_search_context_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ting_search_context_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ting_search_context_node_info() {
  $items = array(
    'ding_search_context_link' => array(
      'name' => t('Search Context Link'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  return $items;
}
