<?php
/**
 * @file
 * ting_new_materials.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_new_materials_ctools_plugin_api() {
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
 * Implements hook_node_info().
 */
function ting_new_materials_node_info() {
  $items = array(
    'new_materials' => array(
      'name' => t('New Materials'),
      'base' => 'node_content',
      'description' => t('Creates a list of new materials'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
