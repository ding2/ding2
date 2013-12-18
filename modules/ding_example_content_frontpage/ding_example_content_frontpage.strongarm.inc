<?php
/**
 * @file
 * ding_example_content_frontpage.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_example_content_frontpage_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_carousel_search_queries';
  $strongarm->value = array(
    0 => array(
      'title' => 'Unge',
      'subtitle' => 'Nye bøger til unge',
      'query' => '870970-basis:29983739 OR 870970-basis:29983585 OR 870970-basis:29989702 OR 870970-basis:29997829 OR  870970-basis:29997918 OR 870970-basis:29986215 OR 870970-basis:50532615 OR 870970-basis:50613038 OR 870970-basis:50618374',
    ),
    1 => array(
      'title' => 'Til de små',
      'subtitle' => 'Bøger til de små',
      'query' => '870970-basis:50612910  OR 870970-basis:29981299 OR  870970-basis:29967326  OR 870970-basis:50561488 OR 870970-basis:29618518 OR 870970-basis:50530671 OR 870970-basis:50577384  OR 870970-basis:50561445 OR 870970-basis:50587177 OR  870970-basis:50618404  ',
    ),
  );
  $export['ting_carousel_search_queries'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ting_carousel_search_queries_hidden';
  $strongarm->value = array();
  $export['ting_carousel_search_queries_hidden'] = $strongarm;

  return $export;
}
