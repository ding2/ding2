<?php
/**
 * @file
 * smart_search_string.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function smart_search_string_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_smart_search_content';
  $strongarm->value = '0';
  $export['language_content_type_smart_search_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_smart_search_content';
  $strongarm->value = array();
  $export['menu_options_smart_search_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_smart_search_content';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_smart_search_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_smart_search_content';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_smart_search_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_smart_search_content';
  $strongarm->value = 0;
  $export['node_submitted_smart_search_content'] = $strongarm;

  return $export;
}
