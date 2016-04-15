<?php
/**
 * @file
 * ding_dams.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_dams_taxonomy_default_vocabularies() {
  return array(
    'dams_category' => array(
      'name' => 'Ding DAMS Category',
      'machine_name' => 'dams_category',
      'description' => 'Categories used for DAMS',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
