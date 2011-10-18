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
    'ding_content_tags' => array(
      'name' => 'Tags',
      'machine_name' => 'ding_content_tags',
      'description' => NULL,
      'hierarchy' => '0',
      'module' => 'ding_content',
      'weight' => '0',
    ),
    'ding_event' => array(
      'name' => 'Event category',
      'machine_name' => 'ding_event',
      'description' => NULL,
      'hierarchy' => '0',
      'module' => 'ding_event',
      'weight' => '0',
    ),
  );
}
