<?php
/**
 * @file
 * ding_list_installer.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_list_installer_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "pm_existing_pages" && $api == "pm_existing_pages") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_list_installer_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
