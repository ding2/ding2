<?php
/**
 * @file
 * STDOUT log interface.
 */

namespace Ting;

/**
 * Simple STDOUT logging interface.
 */
class TingLogStdout implements TingLogInterface {
  protected $stdout;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->stdout = fopen('php://stdout', 'wb');
  }

  /**
   * {@inheritdoc}
   */
  public function debug($message) {
    $this->log('[debug] ' . $message);
  }

  /**
   * {@inheritdoc}
   */
  public function info($message) {
    $this->log('[info] ' . $message);
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
