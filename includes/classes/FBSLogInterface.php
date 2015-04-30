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
   *
   * @param string $massage.
   */
  public function notice($message);

  /**
   * Log a critical.
   *
   * @param string $massage.
   */
  public function critical($message);

}
