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
   * {@inheritdoc}
   */
  public function set($key, $value) {
    $this->data[$key] = $value;
  }

  /**
   * {@inheritdoc}
   */
  public function get($key) {
    if (isset($this->data[$key])) {
      return $this->data[$key];
    }

    return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function delete($key) {
    unset($this->data[$key]);
  }
}
