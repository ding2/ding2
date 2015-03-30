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
   * Log a notice.
   */
  public function notice($message) {
    watchdog('fbs', $message, array(), WATCHDOG_NOTICE);
  }

  /**
   * Log a critical.
   */
  public function critical($message) {
    watchdog('fbs', $message, array(), WATCHDOG_CRITICAL);
  }
}
