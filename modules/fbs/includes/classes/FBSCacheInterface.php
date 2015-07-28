<?php
/**
 * @file
 * Cache interface.
 */

/**
 * Simple cache interface.
 */
interface FBSCacheInterface {
  /**
   * Set a cache entry.
   *
   * @param string $key
   *   Key to cache under.
   * @param mixed $value
   *   Data to cache.
   */
  public function set($key, $value);

  /**
   * Get a cache entry.
   *
   * @param string $key
   *   Key to fetch.
   *
   * @return mixed|null
   *   The data or null.
   */
  public function get($key);

  /**
   * Delete a cache entry.
   *
   * @param string $key
   *   Key to delete.
   */
  public function delete($key);
}
