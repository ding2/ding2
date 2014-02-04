<?php

/**
 * @file
 * This file implements support for drush into the module.
 */

/**
 * Implements hook_drush_cache_clear().
 *
 * Rebuild permissions on cache clear.
 */
function ding_permissions_drush_cache_clear(&$types) {
  $types['ding_permissions'] = 'secure_permissions_rebuild';
}

