<?php
/**
 * @file
 * Log interface.
 */

namespace Ting;

/**
 * Simple logging interface.
 */
interface TingLogInterface {
  /**
   * Log a debug message.
   *
   * @param string $message
   *   Message to be logged.
   */
  public function debug($message);

  /**
   * Log a info message.
   *
   * @param string $message
   *   Message to be logged.
   */
  public function info($message);

  /**
   * Log a critical message.
   *
   * @param string $message
   *   Message to be logged.
   */
  public function critical($message);

}
