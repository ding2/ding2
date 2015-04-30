<?php
/**
 * @file
 * Drupal log interface.
 */

/**
 * Simple Drupal logging interface.
 */
class FBSLogDrupal implements FBSLogInterface {
  /**
   * {@inheritdoc}
   */
  public function notice($message) {
    watchdog('fbs', $message, array(), WATCHDOG_NOTICE);
  }

  /**
   * {@inheritdoc}
   */
  public function critical($message) {
    watchdog('fbs', $message, array(), WATCHDOG_CRITICAL);
  }
}
