<?php
/**
 * @file
 * ding_event.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_event_taxonomy_default_vocabularies() {
  return array(
    'category' => array(
      'name' => 'Category',
      'machine_name' => 'category',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'ding_event',
      'weight' => '0',
    ),
  );
}
