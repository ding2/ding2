<?php
/**
 * @file
 * ding_ting_frontend.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_ting_frontend_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_facetbrowser_facets';
  $strongarm->value = array(
    0 => array(
      'name' => 'facet.subject',
      'title' => 'Emne',
      'weight' => '-10',
    ),
    1 => array(
      'name' => 'facet.creator',
      'title' => 'Forfatter',
      'weight' => '-9',
    ),
    2 => array(
      'name' => 'facet.type',
      'title' => 'Materialetype',
      'weight' => '-8',
    ),
    3 => array(
      'name' => 'facet.category',
      'title' => 'Kategori',
      'weight' => '-7',
    ),
    4 => array(
      'name' => 'facet.language',
      'title' => 'Sprog',
      'weight' => '-6',
    ),
    5 => array(
      'name' => 'facet.date',
      'title' => 'Årstal',
      'weight' => '-5',
    ),
    6 => array(
      'name' => 'facet.acSource',
      'title' => 'Kilde',
      'weight' => '-4',
    ),
  );
  $export['ding_facetbrowser_facets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_search_disabled_node';
  $strongarm->value = FALSE;
  $export['page_manager_search_disabled_node'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_user_view_disabled';
  $strongarm->value = FALSE;
  $export['page_manager_user_view_disabled'] = $strongarm;

  return $export;
}
