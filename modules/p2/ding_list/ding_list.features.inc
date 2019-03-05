<?php
/**
 * @file
 * ding_list.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_list_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
