<?php
/**
 * @file
 * A wrapper around a legacy Ting Open Search reply.
 */

namespace Drupal\ting;

/**
 * Class TingWrapper
 *
 * Used during the implementation of the Ting search abstraction layer. Makes it
 * easier to track where legacy-code is accessing the Ting reply-object that
 * the abstraction-layer is supposed to superseed.
 *
 * @package Drupal\ting
 */

class TingLegacyObjectWrapper implements \ArrayAccess, TingObjectInterface {

  /**
   * @var array $wrappedReply
   *   Internal array that holds the data being set and read when the object is
   *   accessed as an array.
   */
  protected $wrappedReply;

  /**
   * @var TingLogInterface $logger
   */
  protected $logger;

  /**
   * TingWrapper constructor.
   *
   * @param TingLogInterface $logger
   *   An initialized logger, if not provieded a TingLogDrupal logger will be
   *   used.
   */
  public function __construct($logger = NULL) {
    $this->logger = $logger;
    if (NULL === $this->logger) {
      $this->logger = new TingLogDrupal('Ting');
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getTitle() {
    $title = FALSE;

    if (!empty($this->wrappedReply['dc:title'])) {
      // Use first title with dkdcplus:full if available.
      if (isset($this->wrappedReply['dc:title']['dkdcplus:full'])) {
        $title = $this->wrappedReply['dc:title']['dkdcplus:full'][0];
      }
      else {
        $title = $this->wrappedReply['dc:title'][''][0];
      }
    }
    return $title;
  }

  /**
   * {@inheritdoc}
   *
   * Required by \ArrayAccess.
   */
  public function offsetExists($offset) {
    return isset($this->wrappedReply[$offset]);
  }

  /**
   * {@inheritdoc}
   *
   * Required by \ArrayAccess.
   */
  public function &offsetGet($offset) {
    $this->logCaller();
    $this->logger->debug("Getting $offset");
    return $this->wrappedReply[$offset];
  }

  /**
   * {@inheritdoc}
   *
   * Required by \ArrayAccess.
   */
  public function offsetSet($offset, $value) {
    $this->logCaller();
    $this->logger->debug("Setting $offset = $value");
    $this->wrappedReply[$offset] = $value;
  }

  /**
   * {@inheritdoc}
   *
   * Required by \ArrayAccess.
   */
  public function offsetUnset($offset) {
    unset($this->wrappedReply[$offset]);
  }

  /**
   * Log who is calling the function.
   */
  protected function logCaller() {
    $trace = debug_backtrace(2);
    $this->logger->debug(
      ' access by ' . $trace[1]['file'] . ':' . $trace[1]['line']
    );
  }
}
