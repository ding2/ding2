<?php
/**
 * @file
 * ding_contact.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function ding_contact_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['formblock-contact_site'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'contact_site',
    'module' => 'formblock',
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
