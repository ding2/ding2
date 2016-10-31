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
    $this->url = isset($_SERVER['DDBTEST_URL']) ? $_SERVER['DDBTEST_URL'] : 'http://ding2tal.easyting.dk';
    $this->locale = isset($_SERVER['DDBTEST_LOCALE']) ? $_SERVER['DDBTEST_LOCALE'] : 'en';
    $this->user = isset($_SERVER['DDBTEST_USER']) ? $_SERVER['DDBTEST_USER'] : '3206596642';
    $this->pass = isset($_SERVER['DDBTEST_PASS']) ? $_SERVER['DDBTEST_PASS'] : '12345';
    $this->lms = isset($_SERVER['DDBTEST_LMS']) ? $_SERVER['DDBTEST_LMS'] : '';
    $this->screenshotPath = isset($_SERVER['DDBTEST_SCREENSHOT_PATH']) ? $_SERVER['DDBTEST_SCREENSHOT_PATH'] : '';
    $this->screenshotUrl = isset($_SERVER['DDBTEST_SCREENSHOT_URL']) ? $_SERVER['DDBTEST_SCREENSHOT_URL'] : '';
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

  public function getScreenshotPath() {
    return $this->screenshotPath;
  }

  public function getScreenshotUrl() {
    return $this->screenshotUrl;
  }
}
