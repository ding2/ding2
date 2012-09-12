<?php
/**
 * @file
 * ding_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
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
 * Implements hook_node_info().
 */
function ding_page_node_info() {
  $items = array(
    'ding_page' => array(
      'name' => t('Side'),
      'base' => 'node_content',
      'description' => t('Indholdsside med en venstremenu'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  return $items;
}
