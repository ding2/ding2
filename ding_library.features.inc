<?php
/**
 * @file
 * ding_library.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_library_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "openlayers" && $api == "openlayers_maps") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_library_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ding_library_node_info() {
  $items = array(
    'ding_library' => array(
      'name' => t('Library'),
      'base' => 'node_content',
      'description' => t('Add a new library to the site.'),
      'has_title' => '1',
      'title_label' => t('Navn'),
      'help' => '',
    ),
  );
  return $items;
}
