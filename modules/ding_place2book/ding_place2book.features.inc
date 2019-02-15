<?php
/**
 * @file
 * ding_place2book.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_place2book_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
