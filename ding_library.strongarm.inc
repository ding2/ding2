<?php
/**
 * @file
 * ding_library.strongarm.inc
 */

/**
 * Implementation of hook_strongarm().
 */
function ding_library_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_ding_library';
  $strongarm->value = '2';
  $export['language_content_type_ding_library'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_ding_library';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_ding_library'] = $strongarm;

  return $export;
}
