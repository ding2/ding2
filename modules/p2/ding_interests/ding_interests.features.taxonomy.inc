<?php

/**
 * @file
 * ding_news.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_interests_taxonomy_default_vocabularies() {
  return array(
    'interest_status' => array(
      'name' => 'Interest status',
      'machine_name' => 'interest_status',
      'description' => 'Status of taxonomy terms marked as an interest.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
