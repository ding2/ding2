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
