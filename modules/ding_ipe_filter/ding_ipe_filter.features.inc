<?php
/**
 * @file
 * ding_ipe_filter.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_ipe_filter_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
