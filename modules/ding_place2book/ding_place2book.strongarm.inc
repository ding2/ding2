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
  $strongarm->name = 'ding_p2b_default_event_maker';
  $strongarm->value = '540';
  $export['ding_p2b_default_event_maker'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'p2b_kultunaut_age_group';
  $strongarm->value = array(
    'Alle' => 'Alle',
    'k' => 'v',
  );
  $export['p2b_kultunaut_age_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'p2b_kultunaut_export_category';
  $strongarm->value = array(
    1 => 'Koncert: Musical',
  );
  $export['p2b_kultunaut_export_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'p2b_library_event_maker';
  $strongarm->value = array(
    21 => '227',
  );
  $export['p2b_library_event_maker'] = $strongarm;

  return $export;
}
