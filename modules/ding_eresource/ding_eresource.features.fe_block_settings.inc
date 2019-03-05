<?php
/**
 * @file
 * ding_eresource.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function ding_eresource_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-98880b6fbff6f74deeae473932e04e0b'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '98880b6fbff6f74deeae473932e04e0b',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'ddbasic' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'ddbasic',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
