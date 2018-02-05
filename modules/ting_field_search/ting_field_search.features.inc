<?php
/**
 * @file
 * ting_field_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_field_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ting_field_search" && $api == "ting_field_search_default_profiles") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
