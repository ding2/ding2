<?php

/**
 * @file
 * ding_staff.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_special_user_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_special_user_views_api() {
  return array(
    'api' => '3.0',
    'path' => drupal_get_path('module', 'ding_special_user'),
  );
}

/**
 * Implements hook_default_profile2_type().
 */
function ding_special_user_default_profile2_type() {
  $items = array();
  $items['ding_special_user_profile'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "special_user",
    "label" : "Special user",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');
  return $items;
}

