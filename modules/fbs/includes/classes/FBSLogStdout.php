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
   * {@inheritdoc}
   */
  public function notice($message) {
    $this->log('[notice] ' . $message);
  }

  /**
   * {@inheritdoc}
   */
  public function critical($message) {
    $this->log('[critical] ' . $message);
  }

  /**
   * Log a message to stdout.
   *
   * @param string $message
   *   String to output.
   */
  protected function log($message) {
    fwrite($this->stdout, $message . "\n");
  }
}
