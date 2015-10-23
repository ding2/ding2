<?php
/**
 * @file
 * ding_content.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_content_taxonomy_default_vocabularies() {
  return array(
    'category' => array(
      'name' => 'Category',
      'machine_name' => 'category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'ding_content_tags' => array(
      'name' => 'Tags',
      'machine_name' => 'ding_content_tags',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'ding_content',
      'weight' => 0,
    ),
  );
}
