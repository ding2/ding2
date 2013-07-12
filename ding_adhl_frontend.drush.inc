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
function ding_adhl_frontend_drush_cache_clear(&$types) {
  $types['ding-adhl-recommendations'] = 'ding_adhl_frontend_flush_caches';
}

