<?php
/**
 * @file
 * Page abstractions implementation.
 */

/**
 * DDBTestPageAbstraction class.
 */
class DDBTestPageAbstraction {
  private $phpunit_instance = NULL;
  const WAIT_FOR_PAGE = 30;
  const WAIT_FOR_ELEMENT = 5;

  /**
   * Class constructor.
   */
  public function __construct(PHPUnit_Extensions_SeleniumTestCase $instance) {
    $this->phpunit_instance = $instance;
  }

  /**
   * Refresh.
   */
  public function refresh() {
    $this->phpunit_instance->open($this->phpunit_instance->getLocation());
    $this->waitForPage();
  }

  /**
   * Login the user into the testing environment. 
   *
   * @param string $user
   *   User name.
   * @param string $pass
   *   User password.
   */
  public function userLogin($user, $pass) {
    $this->phpunit_instance->click('css=.topbar-menu a.topbar-link-user');
    $this->phpunit_instance->type('css=#edit-name', $user);
    $this->phpunit_instance->type('css=#edit-pass', $pass);
    $this->phpunit_instance->click('css=#edit-submit--2');
    // @todo
    // Assert that user has actually logged in.
    $this->waitForPage();
  }

  /**
   * UserMakeSearch.
   */
  public function userMakeSearch($query) {
    $this->phpunit_instance->type('css=#search-block-form input[type="text"]', $query);
    $this->phpunit_instance->click('css=#search-block-form input[type="submit"]');
    $this->waitForPage();
  }

  /**
   * UserBookmark.
   */
  public function userBookmark($locator) {
    $this->phpunit_instance->click('css=' . $locator);
  }

  /**
   * UserReserve.
   */
  public function userReserve($locator) {
    $this->phpunit_instance->click('css=' . $locator);
  }

  /**
   * Fill DingPopupLogin.
   */
  public function fillDingPopupLogin($user, $pass) {
    // Authenticate via popup with credentials provided.
    $this->waitForElement('css=.ding-popup-content', 10);
    $this->phpunit_instance->type('css=.ding-popup-content form#user-login input[name="name"]', $user);
    $this->phpunit_instance->type('css=.ding-popup-content form#user-login input[name="pass"]', $pass);
    // Use mousedown, since Drupal ajax is binded to mousedown by default.
    $this->phpunit_instance->mouseDownAt('css=.ding-popup-content form#user-login input[name="op"]');
  }

  /**
   * Wait for element.
   *
   * @return bool
   *   Boolean.
   */
  public function waitForElement($selector, $time = self::WAIT_FOR_ELEMENT, $force = TRUE) {
    for ($second = 0;; $second++) {
      if ($second >= $time) {
        if ($force) {
          $this->phpunit_instance->fail('Element ' . $selector . ' not found.');
        }
        return FALSE;
      }
      try {
        if ($this->phpunit_instance->isElementPresent($selector)) {
          return TRUE;
        }
      }
      catch (Exception $e) {}
      sleep(1);
    }
  }

  /**
   * Wait for page.
   */
  public function waitForPage($time = self::WAIT_FOR_PAGE) {
    $this->phpunit_instance->waitForPageToLoad($time * 1000);
  }
}
