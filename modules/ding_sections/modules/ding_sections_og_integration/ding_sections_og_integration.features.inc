<?php
/**
 * @file
 * ding_sections_og_integration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_sections_og_integration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ding_sections_og_integration_node_info() {
  $items = array(
    'section' => array(
      'name' => t('Section'),
      'base' => 'node_content',
      'description' => t('Organic Group for ding sections needs'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
