<?php
/**
 * @file
 * ting_field_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_field_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "ting_field_search" && $api == "ting_field_search_default_profiles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ting_field_search_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ting_field_search_node_info() {
  $items = array(
    'ting_field_search_search_guide' => array(
      'name' => t('Search guide'),
      'base' => 'node_content',
      'description' => t('A content-type that can be used to create search guides to be shown on a profile page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
