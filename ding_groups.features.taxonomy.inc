<?php
/**
 * @file
 * ding_groups.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_groups_taxonomy_default_vocabularies() {
  return array(
    'group_category' => array(
      'name' => 'Group category',
      'machine_name' => 'group_category',
      'description' => 'Category used to group groups (temapages)',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
