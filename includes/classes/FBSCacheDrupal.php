<?php
/**
 * @file
 * Drupal cache implementation.
 */

/**
 * Simple Drupal cache interface.
 */
class FBSCacheDrupal implements FBSCacheInterface {
  /**
   * Set a cache entry.
   */
  public function set($key, $value) {
    cache_set($key, $value, 'cache', CACHE_TEMPORARY);
  }

  /**
   * Get a cache entry.
   */
  public function get($key) {
    if ($cache = cache_get($key)) {
      return $cache->data;
    }

    return NULL;
  }

  /**
   * Delete a cache entry.
   */
  public function delete($key) {
    cache_clear_all($key, 'cache');
  }
}
