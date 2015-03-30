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
   */
  public function set($key, $value);

  /**
   * Get a cache entry.
   */
  public function get($key);

  /**
   * Delete a cache entry.
   */
  public function delete($key);
}
