<?php
/**
 * @file
 * This file implements support for drush into the module.
 */
// TODO BBS-SAL: Move all opensearch related caches (probably all in this file
// to opensearch.
/**
 * Implements hook_drush_cache_clear().
 *
 * Adds a cache clear option for the recommendation cache.
 */
function ting_drush_cache_clear(&$types) {
  // TODO BBS-SAL: Add a opensearch alias for each of these cache tables.
  // eg, leave the key (but rename the function).
  // $types['ting_object'] = 'opensearch_object_cache_clear';
  // But then add
  // $types['opensearch_object'] = 'opensearch_object_cache_clear';
  // Default cache table.
  $types['ting'] = 'ting_flush_caches';

  // Ting object cache.
  $types['ting_object'] = 'ting_object_cache_clear';

  // Ting object fulltext cache.
  $types['ting_object_fulltext'] = 'ting_object_fulltext_cache_clear';

  // Ting collection cache.
  $types['ting_collection'] = 'ting_collection_cache_clear';

  // Ting reply cache.
  $types['ting_reply'] = 'ting_reply_cache_clear';
}

/**
 * Clear all ting objects from the ting cache table.
 */
function ting_object_cache_clear() {
  cache_clear_all(TING_CACHE_TING_OBJECT, 'cache_ting', TRUE);
}

/**
 * Clear all ting objects fulltext from the ting cache table.
 */
function ting_object_fulltext_cache_clear() {
  cache_clear_all(TING_CACHE_TING_OBJECT_FULLTEXT, 'cache_ting', TRUE);
}

/**
 * Clear all ting collections from the ting cache table.
 */
function ting_collection_cache_clear() {
  cache_clear_all(TING_CACHE_COLLECTION, 'cache_ting', TRUE);
}

/**
 * Clear all ting reply from the ting cache table.
 */
function ting_reply_cache_clear() {
  cache_clear_all(TING_CACHE_REPLY, 'cache_ting', TRUE);
}
