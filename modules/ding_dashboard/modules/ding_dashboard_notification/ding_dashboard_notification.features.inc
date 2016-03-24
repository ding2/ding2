<?php
/**
 * @file
 * ding_dashboard_notification.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_dashboard_notification_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
