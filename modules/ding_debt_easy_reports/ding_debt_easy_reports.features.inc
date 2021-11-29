<?php
/**
 * @file
 * ding_debt_easy_reports.features.inc
 */

/**
 * Implements hook_views_api().
 */
function ding_debt_easy_reports_views_api($module = NULL, $api = NULL) {
  return array(
    "api" => "3.0",
    'path' => drupal_get_path('module', 'ding_debt_easy_reports') . '/includes',
  );
}
