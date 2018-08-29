<?php
/**
 * @file
 * ding_ting_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_ting_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "pm_existing_pages" && $api == "pm_existing_pages") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "ting_field_search" && $api == "ting_field_search_default_profiles") {
    return array("version" => "1");
  }
}
