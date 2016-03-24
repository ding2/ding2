<?php
/**
 * @file
 * ding_editorial_dashboard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_dashboard_comments_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
