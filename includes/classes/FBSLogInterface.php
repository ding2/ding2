<?php
/**
 * @file
 * Log interface.
 */

/**
 * Simple logging interface.
 */
interface FBSLogInterface {
  /**
   * Log a notice.
   */
  public function notice($message);

  /**
   * Log a critical.
   */
  public function critical($message);

}
