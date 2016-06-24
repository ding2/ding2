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
}
