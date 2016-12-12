<?php
/**
 * @file
 * Ding_list_installer.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function ding_list_installer_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'dinglist';
  $pm_existing_page->label = 'Dinglist';
  $pm_existing_page->context = 'entity|ding_type|id';
  $pm_existing_page->paths = 'ding_type/ding_list/%';
  $export['dinglist'] = $pm_existing_page;

  return $export;
}
