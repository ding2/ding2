<?php
/**
 * @file
 * ding_nodelist.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_nodelist_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_nodelist_cache_default_time';
  $strongarm->value = '1800';
  $export['ding_nodelist_cache_default_time'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_nodelist_node_types';
  $strongarm->value = array(
    'ding_event' => 'ding_event',
    'ding_news' => 'ding_news',
    'ding_page' => 'ding_page',
    'ding_campaign' => 0,
    'ding_library' => 0,
  );
  $export['ding_nodelist_node_types'] = $strongarm;

  return $export;
}
