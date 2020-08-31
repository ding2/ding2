<?php
/**
 * @file
 * ding_user_frontend.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function ding_user_frontend_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'user_contact';
  $pm_existing_page->label = 'User contact';
  $pm_existing_page->context = 'entity|user|uid';
  $pm_existing_page->paths = 'user/%user/contact';
  $export['user_contact'] = $pm_existing_page;

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'user_roles';
  $pm_existing_page->label = 'User roles';
  $pm_existing_page->context = 'entity|user|uid';
  $pm_existing_page->paths = 'user/%user/roles';
  $export['user_roles'] = $pm_existing_page;

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'user_scheduler';
  $pm_existing_page->label = 'User scheduler';
  $pm_existing_page->context = 'entity|user|uid';
  $pm_existing_page->paths = 'user/%/scheduler';
  $export['user_scheduler'] = $pm_existing_page;

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'user_shortcuts';
  $pm_existing_page->label = 'User shortcuts';
  $pm_existing_page->context = 'entity|user|uid';
  $pm_existing_page->paths = 'user/%user/shortcuts';
  $export['user_shortcuts'] = $pm_existing_page;

  return $export;
}
