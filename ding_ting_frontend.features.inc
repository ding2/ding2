<?php
/**
 * @file
 * ding_ting_frontend.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_ting_frontend_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
}
