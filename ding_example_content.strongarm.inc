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
      'title' => 'Nelson Mandela',
      'subtitle' => 'Nelson Mandela',
      'query' => '22048775 or 22444948 or 28492952 or 26443814 or 27723829 or 28181167 or 24371646 or 28200609 or 24587428 or 28160232 or 24172872 or 28222920',
    ),
    1 => array(
      'title' => 'Sommerlæsning',
      'subtitle' => 'Idéer til sommerlæsning',
      'query' => '29932018 or 29919860 or 29897395 or 29912025 or 29937818 or 29491046 or 29932158 or 29913889 or 29919712 or 29974861 or 29950679',
    ),
    2 => array(
      'title' => 'Fra eksamen til dimissionsfester',
      'subtitle' => 'Fra eksamen til dimissionsfester',
      'query' => '29074623 or 28594119 or 27351786 or 29125031 or 28704445 or 28699069    ',
    ),
    3 => array(
      'title' => 'Krimibøger',
      'subtitle' => 'En god krimi i ferien',
      'query' => '29869308 or 29867453 or 29406154 or 29427364 or 29602697 or 28682433 or 29348812 or 29339376 or 29558124 or 29654719 or 29265917 or 29506817 or 29318859 or 29258430 or 29504245',
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
