<?php
/**
 * @file
 * ding_user_frontend.strongarm.inc
 */

/**
 * Implementation of hook_strongarm().
 */
function ding_user_frontend_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_date_only';
  $strongarm->value = 'd.m.Y';
  $export['date_format_date_only'] = $strongarm;

  return $export;
}
