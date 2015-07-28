<?php
/**
 * @file
 * ding_staff.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_staff_taxonomy_default_vocabularies() {
  return array(
    'ding_staff_department' => array(
      'name' => 'Department',
      'machine_name' => 'ding_staff_department',
      'description' => 'Available department labels in staff profiles',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
