<?php
/**
 * @file
 * ding_page.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_page_taxonomy_default_vocabularies() {
  return array(
    'ding_page' => array(
      'name' => 'Page category',
      'machine_name' => 'ding_page',
      'description' => NULL,
      'hierarchy' => '0',
      'module' => 'ding_page',
      'weight' => '0',
    ),
  );
}
