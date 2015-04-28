<?php
/**
 * @file
 * ding_content.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_content_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
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
}

/**
 * Implements hook_views_api().
 */
function ding_content_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
