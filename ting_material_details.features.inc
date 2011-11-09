<?php
/**
 * @file
 * material_details_field_group.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function material_details_field_group_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
