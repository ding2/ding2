<?php
/**
 * @file
 * mkdru_ding.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mkdru_ding_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mkdru_defaults';
  $strongarm->value = array(
    'settings' => array(
      'sp_server_auth' => 0,
      'sp_user' => 'LBR',
      'sp_pass' => '2HAawKzq',
      'pz2_path' => '/service-proxy',
      'is_service_proxy' => 1,
      'facets' => array(
        'source' => array(
          'displayName' => 'Source',
          'pz2Name' => 'xtargets',
          'multiLimit' => 0,
          'max' => '10',
          'orderWeight' => '1',
          'remove' => 'Remove source facet',
        ),
        'subject' => array(
          'displayName' => 'Subject',
          'pz2Name' => 'subject',
          'multiLimit' => 1,
          'max' => '10',
          'orderWeight' => '2',
          'remove' => 'Remove subject facet',
        ),
        'author' => array(
          'displayName' => 'Author',
          'pz2Name' => 'author',
          'multiLimit' => 0,
          'max' => '10',
          'orderWeight' => '3',
          'remove' => 'Remove author facet',
        ),
      ),
    ),
    'pz2_path' => '/service-proxy',
    'sp_user' => 'LBR',
    'sp_pass' => '2HAawKzq',
    'sp_server_auth' => 0,
    'facets' => array(
      'source' => array(
        'displayName' => 'Source',
        'pz2Name' => 'xtargets',
        'multiLimit' => 0,
        'max' => '10',
        'orderWeight' => '1',
        'remove' => 'Remove source facet',
      ),
      'subject' => array(
        'displayName' => 'Subject',
        'pz2Name' => 'subject',
        'multiLimit' => 1,
        'max' => '10',
        'orderWeight' => '2',
        'remove' => 'Remove subject facet',
      ),
      'author' => array(
        'displayName' => 'Author',
        'pz2Name' => 'author',
        'multiLimit' => 0,
        'max' => '10',
        'orderWeight' => '3',
        'remove' => 'Remove author facet',
      ),
    ),
  );
  $export['mkdru_defaults'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mkdru_ding';
  $strongarm->value = array(
    'pz2_path' => '/pazpar2/search.pz2',
    'use_sessions' => 1,
    'sp' => array(
      'user' => '',
      'pass' => '',
    ),
    'facets' => array(
      'source' => array(
        'displayName' => 'Source',
        'pz2Name' => 'xtargets',
        'limiter' => NULL,
        'multiLimit' => NULL,
        'max' => 10,
        'orderWeight' => 1,
      ),
      'subject' => array(
        'displayName' => 'Subject',
        'pz2Name' => 'subject',
        'limiter' => 'su',
        'multiLimit' => 1,
        'max' => 10,
        'orderWeight' => 2,
      ),
      'author' => array(
        'displayName' => 'Author',
        'pz2Name' => 'author',
        'limiter' => 'au',
        'multiLimit' => 0,
        'max' => 10,
        'orderWeight' => 3,
      ),
    ),
  );
  $export['mkdru_ding'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_manager_search_disabled_mkdru_ding';
  $strongarm->value = FALSE;
  $export['page_manager_search_disabled_mkdru_ding'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_active_modules';
  $strongarm->value = array(
    'node' => 'node',
    'mkdru_ding' => 'mkdru_ding',
    'ting_search' => 'ting_search',
    'file_entity' => 0,
    'user' => 0,
  );
  $export['search_active_modules'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_default_module';
  $strongarm->value = 'ting_search';
  $export['search_default_module'] = $strongarm;

  return $export;
}
