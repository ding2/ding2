<?php
/**
 * @file
 * ding_news.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ding_news_taxonomy_default_vocabularies() {
  return array(
    'ding_news' => array(
      'name' => 'News category',
      'machine_name' => 'ding_news',
      'description' => NULL,
      'hierarchy' => '0',
      'module' => 'ding_news',
      'weight' => '0',
    ),
  );
}
