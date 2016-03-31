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
  $strongarm->value = '1';
  $export['ding_p2b_default_capacity'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_event_maker';
  $strongarm->value = '227';
  $export['ding_p2b_default_event_maker'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_kultunaut_export';
  $strongarm->value = 1;
  $export['ding_p2b_default_kultunaut_export'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_passive';
  $strongarm->value = 1;
  $export['ding_p2b_default_passive'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_price_name';
  $strongarm->value = '2';
  $export['ding_p2b_default_price_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_default_synchronize';
  $strongarm->value = 1;
  $export['ding_p2b_default_synchronize'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_kultunaut_age_group';
  $strongarm->value = array(
    54 => 'Unge',
    50 => 'Alle',
    55 => 'Voksne',
    51 => 'Ældre',
    52 => 'Børn',
    53 => 'Børn',
  );
  $export['ding_p2b_kultunaut_age_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_kultunaut_export_category';
  $strongarm->value = array(
    44 => 'Koncert: Funk/Blues/R&B',
    45 => 'Teater: Musical',
    46 => 'Teater: Dans',
    47 => 'Teater: Dans',
    48 => 'Teater: Ballet',
    49 => 'Teater: Dans',
  );
  $export['ding_p2b_kultunaut_export_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_p2b_library_event_makers';
  $strongarm->value = array(
    3 => '227',
    4 => '540',
  );
  $export['ding_p2b_library_event_makers'] = $strongarm;

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
    44 => 'Koncert: Andet/Ukendt',
    45 => 'Koncert: Club/DJ',
    46 => 'Koncert: Folk/Vise/Country',
    47 => 'Koncert: Dans',
    48 => 'Koncert: Musical',
    49 => 'Koncert: Opera/Operette',
  );
  $export['p2b_kultunaut_export_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'p2b_library_event_maker';
  $strongarm->value = array(
    3 => '227',
    4 => '540',
  );
  $export['p2b_library_event_maker'] = $strongarm;

  return $export;
}
