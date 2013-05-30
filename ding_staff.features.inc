<?php
/**
 * @file
 * ding_staff.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_staff_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_profile2_type().
 */
function ding_staff_default_profile2_type() {
  $items = array();
  $items['staff'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "staff",
    "label" : "Staff",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');
  return $items;
}
