<?php

/**
 * @file
 * This file implements support for drush into the module.
 */

/**
 * Implements hook_drush_cache_clear().
 *
 * Adds a cache clear option for the ting search ortograf cache.
 */
function ting_search_ortograf_drush_cache_clear(&$types) {
  $types['ting_search_ortograf'] = 'ting_search_ortograf_flush_caches';
}
