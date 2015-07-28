<?php
/**
 * @file
 * ding_contact.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_contact_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_contact_site_disabled';
  $strongarm->value = FALSE;
  $export['page_manager_contact_site_disabled'] = $strongarm;

  return $export;
}
