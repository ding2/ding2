<?php


namespace Page;

use SensioLabs\Behat\PageObjectExtension\PageObject\Factory;
use SensioLabs\Behat\PageObjectExtension\PageObject\Page;

class LogMessages extends Page
{
  /**
   * @var string $messageCollection
   * contains all log messages from verbose mode
   */
  protected $messageCollection = '';

  /**
   * @return string
   * Resets the log messages. They can only be read once.
   */
  public function getMessages() {
    return $this->messageCollection;
    $this->messageCollection = "";
  }


  /**
   * log_msg - prints message on log if condition is true.
   *
   * @param $ifTrue
   * @param $msg
   */
  public function logMsg($ifTrue, $msg) {
    if ($ifTrue) {
      if ($msg != "") {
        $this->messageCollection = $this->messageCollection . $msg . "\n";
      }
    }
  }

  /**
   * log_timestamp - puts a timestamp in the log. Good for debugging timing issues.
   * @param $ifTrue
   * @param $msg
   */
  public function logTimestamp($ifTrue, $msg) {
    // this is so we can use this function with verbose-checking
    if ($ifTrue) {
      // get the microtime, format it and print it.
      $t = microtime(true);
      $micro = sprintf("%06d",($t - floor($t)) * 1000000);
      $d = new DateTime( date('Y-m-d H:i:s.'.$micro, $t) );
      $this->messageCollection = $this->messageCollection . $msg . " " . $d->format("Y-m-d H:i:s.u") . "\n";
    }
  }

}