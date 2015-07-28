<?php
/**
 * @file
 * ding_frontend.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function ding_frontend_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'comments';
  $pm_existing_page->label = 'comments';
  $pm_existing_page->context = '';
  $pm_existing_page->paths = 'comment/reply/%node
comment/%comment/edit
comment/%/view
comment/%
comment/%/delete
comment/%/approve';
  $export['comments'] = $pm_existing_page;

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'user';
  $pm_existing_page->label = 'user';
  $pm_existing_page->context = 'entity|user|uid';
  $pm_existing_page->paths = 'user/password
user/reset/%/%/%
user';
  $export['user'] = $pm_existing_page;

  return $export;
}
