<?php
/**
 * @file
 * ding_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_event_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
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
function ding_event_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ding_event_node_info() {
  $items = array(
    'ding_event' => array(
      'name' => t('Begivenhed'),
      'base' => 'node_content',
      'description' => t('A content type for events concerning libraries.'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => t('This is the heading usually displayed with a big font size (h1) on the top of the page.'),
    ),
  );
  return $items;
}
