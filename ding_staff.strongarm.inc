<?php
/**
 * @file
 * ding_staff.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_staff_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'realname_pattern';
  $strongarm->value = '[user:profile-ding-staff-profile:field_ding_staff_forename] [user:profile-ding-staff-profile:field_ding_staff_surname]';
  $export['realname_pattern'] = $strongarm;

  return $export;
}
