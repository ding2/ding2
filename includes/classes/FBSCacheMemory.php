<?php
/**
 * @file
 * Memory cache implementation.
 */

/**
 * Simple memory cache interface.
 */
class FBSCacheMemory implements FBSCacheInterface {
  protected $data = array();

  /**
   * Set a cache entry.
   */
  public function set($key, $value) {
    $this->data[$key] = $value;
  }

  /**
   * Get a cache entry.
   */
  public function get($key) {
    if (isset($this->data[$key])) {
      return $this->data[$key];
    }

    return NULL;
  }

  /**
   * Delete a cache entry.
   */
  public function delete($key) {
    unset($this->data[$key]);
  }
}
