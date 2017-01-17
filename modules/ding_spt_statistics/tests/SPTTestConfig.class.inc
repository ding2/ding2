<?php
/**
 * This file must be in directory lib. 
 * @file
 * Config class implementation.
 *
 * Uses environment variables as a default setting.
 */
class SPTTestConfig {
  private $browser;
  private $url;
  private $user;
  private $pass;

  public function __construct() {
    $this->browser = isset($_SERVER['SPTTEST_BROWSER']) ? $_SERVER['SPTTEST_BROWSER'] : '*firefox';
    $this->url = isset($_SERVER['SPTTEST_URL']) ? $_SERVER['SPTTEST_URL'] : 'http://spt-v2.ddbcms.dev.inlead.dk/';
    $this->user = isset($_SERVER['SPTTEST_USER']) ? $_SERVER['SPTTEST_USER'] : '1850402031';
    $this->pass = isset($_SERVER['SPTTEST_PASS']) ? $_SERVER['SPTTEST_PASS'] : '7891';
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
}
