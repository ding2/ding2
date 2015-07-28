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
function ting_search_autocomplete_drush_cache_clear(&$types) {
  $types['ting_search_autocomplete'] = 'ting_search_autocomplete_flush_caches';
}
