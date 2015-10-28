<?php
/**
 * @file
 * ding_groups.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_groups_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_groups_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ding_groups_node_info() {
  $items = array(
    'ding_group' => array(
      'name' => t('Group'),
      'base' => 'node_content',
      'description' => t('Create and new group that can be used to group related content together (temapages)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
