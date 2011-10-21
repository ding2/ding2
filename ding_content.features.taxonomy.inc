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
    'ding_content_tags' => array(
      'name' => 'Tags',
      'machine_name' => 'ding_content_tags',
      'description' => NULL,
      'hierarchy' => '0',
      'module' => 'ding_content',
      'weight' => '0',
    ),
  );
}
