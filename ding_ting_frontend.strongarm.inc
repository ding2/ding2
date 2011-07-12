<?php
/**
 * @file
 * ding_ting_frontend.strongarm.inc
 */

/**
 * Implementation of hook_strongarm().
 */
function ding_ting_frontend_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_search_disabled_node';
  $strongarm->value = FALSE;
  $export['page_manager_search_disabled_node'] = $strongarm;

  return $export;
}
