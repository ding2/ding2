<?php
/**
 * @file
 * ding_example_content.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_example_content_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_carousel_search_queries';
  $strongarm->value = array(
    0 => array(
      'title' => 'Krimi',
      'subtitle' => 'Krimi 2013',
      'query' => 'bog AND krimi AND 2013 AND dansk',
    ),
    1 => array(
      'title' => 'Italiensk film',
      'subtitle' => 'Italiensk film fra 2013',
      'query' => 'spillefilm AND 2013 AND italiensk',
    ),
  );
  $export['ting_carousel_search_queries'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_carousel_search_queries_hidden';
  $strongarm->value = array();
  $export['ting_carousel_search_queries_hidden'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_search_carousel_description_toggle';
  $strongarm->value = 1;
  $export['ting_search_carousel_description_toggle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_search_carousel_tabs_position';
  $strongarm->value = 'bottom';
  $export['ting_search_carousel_tabs_position'] = $strongarm;

  return $export;
}
