<?php
/**
 * @file
 * ding_campaign_ctype.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_campaign_ctype_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_ding_campaign';
  $strongarm->value = '1';
  $export['language_content_type_ding_campaign'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_ding_campaign';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_ding_campaign'] = $strongarm;

  return $export;
}
