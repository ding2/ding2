<?php
/**
 * @file
 * ding_content.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function ding_content_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'ding_content_workbench_recent_content';
  $pm_existing_page->label = 'Workbench: All recent content';
  $pm_existing_page->context = '';
  $pm_existing_page->paths = 'admin/workbench/content/all';
  $export['ding_content_workbench_recent_content'] = $pm_existing_page;

  return $export;
}
