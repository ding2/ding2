<?php
/**
 * @file
 * ding_place2book.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_place2book_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_capacity';
  $strongarm->value = '0';
  $export['ding_p2b_default_capacity'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_event_maker';
  $strongarm->value = '540';
  $export['ding_p2b_default_event_maker'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_kultunaut_export';
  $strongarm->value = 0;
  $export['ding_p2b_default_kultunaut_export'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_passive';
  $strongarm->value = 0;
  $export['ding_p2b_default_passive'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_price_name';
  $strongarm->value = 'Adgang';
  $export['ding_p2b_default_price_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_synchronize';
  $strongarm->value = 1;
  $export['ding_p2b_default_synchronize'] = $strongarm;

  return $export;
}
