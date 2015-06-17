<?php
/**
 * @file
 * ding_search_context.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_search_context_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
