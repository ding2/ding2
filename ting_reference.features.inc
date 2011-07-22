<?php
/**
 * @file
 * ting_reference.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ting_reference_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "relation" && $api == "relation_default") {
    return array("version" => "1");
  }
}
