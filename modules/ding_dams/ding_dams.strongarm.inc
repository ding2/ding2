<?php
/**
 * @file
 * ding_dams.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_dams_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_lock_hook';
  $strongarm->value = 'all';
  $export['file_lock_hook'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_lock_mode';
  $strongarm->value = 'all';
  $export['file_lock_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_lock_pattern';
  $strongarm->value = '*';
  $export['file_lock_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_lock_regex';
  $strongarm->value = '/.*/';
  $export['file_lock_regex'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_temporary_path';
  $strongarm->value = 'sites/default/files/tmp';
  $export['file_temporary_path'] = $strongarm;

  return $export;
}
