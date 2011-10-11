<?php
/**
 * @file
 * ding_page.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_page_ctools_plugin_api() {
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
function ding_page_node_info() {
  $items = array(
    'ding_page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('A basic page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
