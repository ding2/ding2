<?php

/**
 * @file
 * ding_serendipity.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_serendipity_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
