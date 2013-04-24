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
    'news_category' => array(
      'name' => 'News Category',
      'machine_name' => 'news_category',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
