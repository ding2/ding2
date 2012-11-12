<?php

/**
 * @file
 * This file implements support for drush into the module.
 */

/**
 * Adds a cache clear option for the recommendation cache.
 */
function ding_adhl_frontend_drush_cache_clear(&$types) {
  $types['ding-adhl-recommendation'] = 'ding_adhl_frontend_flush_caches';
}

