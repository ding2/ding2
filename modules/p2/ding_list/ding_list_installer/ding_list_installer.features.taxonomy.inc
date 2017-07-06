<?php

/**
 * @file
 * ding_list_installer.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_list_installer_taxonomy_default_vocabularies() {
  return array(
    'content_status' => array(
      'name' => 'Content status',
      'machine_name' => 'content_status',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
