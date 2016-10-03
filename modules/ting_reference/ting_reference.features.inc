<?php
/**
 * @file
 * ting_reference.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ting_reference_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "relation" && $api == "relation_type_default") {
    return array("version" => "1");
  }
}
