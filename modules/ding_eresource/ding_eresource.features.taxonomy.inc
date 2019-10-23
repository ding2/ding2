<?php
/**
 * @file
 * ding_eresource.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_eresource_taxonomy_default_vocabularies() {
  return array(
    'e_resource_availability' => array(
      'name' => 'E-resource availability',
      'machine_name' => 'e_resource_availability',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'e_resource_category' => array(
      'name' => 'E-resource category',
      'machine_name' => 'e_resource_category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
