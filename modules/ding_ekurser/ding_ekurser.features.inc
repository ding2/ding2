<?php
/**
 * @file
 * ding_ekurser.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_ekurser_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "oembed" && $api == "oembed_provider") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
