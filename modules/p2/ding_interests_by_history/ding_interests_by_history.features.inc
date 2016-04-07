<?php

/**
 * @file
 * ding_news.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_interests_by_history_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ding_interests_by_history_views_api() {
  return array(
    'api' => 3,
    'path' => drupal_get_path('module', 'ding_interests_by_history') . '/views',
  );
}
