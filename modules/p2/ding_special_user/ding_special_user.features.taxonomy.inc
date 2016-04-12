<?php

/**
 * @file
 * special_user.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_special_user_taxonomy_default_vocabularies() {
  return array(
    'special_user_category' => array(
      'name' => 'Special user category',
      'machine_name' => 'special_user_category',
      'description' => 'Categories for special users',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}

