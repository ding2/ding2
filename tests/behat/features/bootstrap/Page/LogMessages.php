<?php

/**
 * @file
 * Implements messages to be logged to the output for the benefit of the tester.
 *
 * Essentially the messages are a queue, which can be added to
 * until it is emptied, whereby all messages queued up will be printed.
 */

namespace Page;

use SensioLabs\Behat\PageObjectExtension\PageObject\Factory;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

/**
 * Class LogMessages
 *
 * @package Page
 */
class LogMessages extends Page {
  /**
   * Contains all log messages from verbose mode.
   *
   * @var string $messageCollection
   *   This is where we store all the queued messages.
   */
  protected $messageCollection = '';

  /**
   * Resets the log messages. They can only be read once.
   *
   * @return string
   *   The string to be shown.
   */
  public function getAndClearMessages() {
    $tmp = $this->messageCollection;
    $this->messageCollection = "";
    return $tmp;
  }


  /**
   * Log_msg - prints message on log if condition is true.
   *
   * @param bool $ifTrue
   *   True indicates verbose mode, so we will print the timestamp, otherwise not.
   * @param string $msg
   *   This is the string we will show if the condition is true.
   */
  public function logMsg($ifTrue, $msg) {
    if ($ifTrue) {
      if ($msg != "") {
        $this->messageCollection = $this->messageCollection . $msg . "\n";
      }
    }
  }

  /**
   * Log_timestamp - puts a timestamp in the log. Good for debugging timing issues.
   *
   * @param bool $ifTrue
   *   True indicates verbose mode, so we will print the timestamp, otherwise not.
   * @param string $msg
   *   This is the message we will print before the timestamp. Default empty.
   */
  public function logTimestamp($ifTrue, $msg = "") {
    // This is so we can use this function with verbose-checking.
    if ($ifTrue) {
      // Get the microtime, format it and print it.
      $t = microtime(true);
      $micro = sprintf("%06d", ($t - floor($t)) * 1000000);
      $d = new DateTime(date('Y-m-d H:i:s.' . $micro, $t));
      $this->messageCollection = $this->messageCollection . $msg . " " . $d->format("Y-m-d H:i:s.u") . "\n";
    }
  }
}
