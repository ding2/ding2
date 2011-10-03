<?php
/**
 * @file
 * ding_library.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_library_ctools_plugin_api() {
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
 * Implementation of hook_node_info().
 */
function ding_library_node_info() {
  $items = array(
    'ding_library' => array(
      'name' => t('Library'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
