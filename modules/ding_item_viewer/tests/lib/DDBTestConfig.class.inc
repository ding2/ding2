<?php
/**
 * @file
 * Config class implementation.
 *
 * Uses environment variables as a default setting.
 */
class DDBTestConfig {
  private $browser;
  private $url;
  private $locale;
  private $user;
  private $pass;
  private $lms;

  public function __construct() {
    $this->browser = isset($_SERVER['DDBTEST_BROWSER']) ? $_SERVER['DDBTEST_BROWSER'] : '*firefox';
    $this->url = isset($_SERVER['DDBTEST_URL']) ? $_SERVER['DDBTEST_URL'] : 'http://md.ding2.dev.inlead.dk/';
    $this->user = isset($_SERVER['DDBTEST_USER']) ? $_SERVER['DDBTEST_USER'] : 'admin';
    $this->pass = isset($_SERVER['DDBTEST_PASS']) ? $_SERVER['DDBTEST_PASS'] : '1234';
  }

  /**
   * Get the browser that will hold the tests.
   *
   * @return string
   *   Tested browser.
   */
  public function getBrowser() {
    return $this->browser;
  }

  /**
   * Get the target URL, where tests are to run.
   *
   * @return string
   *   Tests target URL.
   */
  public function getUrl() {
    return $this->url;
  }

  /**
   * Get the URL locale suffix.
   *
   * @return string
   *   Drupal locale string.
   */
  public function getLocale() {
    return $this->locale;
  }

  /**
   * Get the user login, used for authenticated tests.
   *
   * @return string
   *   User login.
   */
  public function getUser() {
    return $this->user;
  }

  /**
   * Get the user password, used for authenticated tests.
   *
   * @return string
   *   User password.
   */
  public function getPass() {
    return $this->pass;
  }

  public function getLms() {
    return $this->lms;
  }
}
