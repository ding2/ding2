<?php
/**
 * @file
 * STDOUT log interface.
 */

/**
 * Simple STDOUT logging interface.
 */
class FBSLogStdout implements FBSLogInterface {
  protected $stdout;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->stdout = fopen('php://stdout', 'w');
  }
  /**
   * Log a notice.
   */
  public function notice($message) {
    $this->log('[notice] ' . $message);
  }

  /**
   * Log a critical.
   */
  public function critical($message) {
    $this->log('[critical] ' . $message);
  }

  protected function log($message) {
    fwrite($this->stdout, $message . "\n");
  }
}
