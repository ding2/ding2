<?php
/**
 * @file
 * This file implements support for drush into the module.
 */

/**
 * Implements hook_drush_cache_clear().
 *
 * Adds a cache clear option for the recommendation cache.
 */
function opensearch_drush_cache_clear(&$types) {
  $types['ting'] = 'opensearch_flush_caches';
  $types['opensearch'] = 'opensearch_flush_caches';

  // Ting object cache.
  $types['ting_object'] = 'opensearch_object_cache_clear';
  $types['opensearch_object'] = 'opensearch_object_cache_clear';

  // Ting object fulltext cache.
  $types['ting_object_fulltext'] = 'opensearch_object_fulltext_cache_clear';
  $types['opensearch_object_fulltext'] = 'opensearch_object_fulltext_cache_clear';

  // Ting collection cache.
  $types['ting_collection'] = 'opensearch_collection_cache_clear';
  $types['opensearch_collection'] = 'opensearch_collection_cache_clear';

  // Ting reply cache.
  $types['ting_reply'] = 'opensearch_reply_cache_clear';
  $types['opensearch_reply'] = 'opensearch_reply_cache_clear';
}

/**
 * Clear all ting objects from the ting cache table.
 */
function opensearch_object_cache_clear() {
  cache_clear_all(OPENSEARCH_CACHE_TING_OBJECT, 'cache_ting', TRUE);
}

/**
 * Clear all ting objects fulltext from the ting cache table.
 */
function opensearch_object_fulltext_cache_clear() {
  cache_clear_all(OPENSEARCH_CACHE_TING_OBJECT_FULLTEXT, 'cache_ting', TRUE);
}

/**
 * Clear all ting collections from the ting cache table.
 */
function opensearch_collection_cache_clear() {
  cache_clear_all(OPENSEARCH_CACHE_COLLECTION, 'cache_ting', TRUE);
}

/**
 * Clear all ting reply from the ting cache table.
 */
function opensearch_reply_cache_clear() {
  cache_clear_all(OPENSEARCH_CACHE_REPLY, 'cache_ting', TRUE);
}
