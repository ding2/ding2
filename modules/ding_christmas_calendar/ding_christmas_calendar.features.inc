<?php
/**
 * @file
 * ding_christmas_calendar.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_christmas_calendar_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ding_christmas_calendar_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
