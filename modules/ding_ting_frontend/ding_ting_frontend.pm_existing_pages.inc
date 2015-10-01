<?php
/**
 * @file
 * ding_ting_frontend.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function ding_ting_frontend_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'fulltext';
  $pm_existing_page->label = 'Fulltext';
  $pm_existing_page->context = 'entity|ting_object|tid';
  $pm_existing_page->paths = 'ting/object/%ting_fulltext_object/fulltext';
  $export['fulltext'] = $pm_existing_page;

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'infomedia';
  $pm_existing_page->label = 'Infomedia';
  $pm_existing_page->context = '';
  $pm_existing_page->paths = 'ting/object/infomedia/%';
  $export['infomedia'] = $pm_existing_page;

  return $export;
}
