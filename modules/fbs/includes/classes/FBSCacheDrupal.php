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
   * {@inheritdoc}
   */
  public function set($key, $value) {
    cache_set($key, $value, 'cache', CACHE_TEMPORARY);
  }

  /**
   * {@inheritdoc}
   */
  public function get($key) {
    if ($cache = cache_get($key)) {
      return $cache->data;
    }

    return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function delete($key) {
    cache_clear_all($key, 'cache');
  }
}
