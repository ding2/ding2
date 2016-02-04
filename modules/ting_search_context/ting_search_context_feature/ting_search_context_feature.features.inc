<?php
/**
 * @file
 * ting_search_context_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_search_context_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
