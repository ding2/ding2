<?php
/**
 * @file
 * Drupal log interface.
 */

namespace Ting;

/**
 * Simple Drupal logging interface.
 */
class TingLogDrupal implements TingLogInterface {

  protected $identity;

  /**
   * TingLogDrupal constructor.
   *
   * @param string $identity
   *   Identification of the logger instance.
   */
  public function __construct($identity) {
    $this->identity = $identity;
  }

  /**
   * {@inheritdoc}
   */
  public function debug($message) {
    watchdog($this->identity, $message, array(), WATCHDOG_DEBUG);
  }

  /**
   * {@inheritdoc}
   */
  public function info($message) {
    watchdog($this->identity, $message, array(), WATCHDOG_INFO);
  }

  /**
   * {@inheritdoc}
   */
  public function critical($message) {
    watchdog($this->identity, $message, array(), WATCHDOG_CRITICAL);
  }
}
