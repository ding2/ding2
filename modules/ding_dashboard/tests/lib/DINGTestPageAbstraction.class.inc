<?php
/**
 * @file
 *
 * Page abstractions implementation.
 */

/**
 * Class DINGTestPageAbstraction
 */
class DINGTestPageAbstraction {
  private $phpunitInstance = NULL;
  const WAIT_FOR_PAGE = 30;
  const WAIT_FOR_ELEMENT = 5;

  /**
   * Construct initialize the instace.
   */
  public function __construct(PHPUnit_Extensions_Selenium2TestCase $instance) {
    $this->phpunit_instance = $instance;
  }

  /**
   * Function refresh page.
   */
  public function refresh() {
    $this->phpunit_instance->open($this->phpunit_instance->getLocation());
    $this->waitForPage();
  }

  /**
   * Function user login
   */
  public function userLogin($user, $pass) {
    $this->phpunit_instance->byLinkText("Login")->click();
    $element = $this->phpunit_instance->byId("edit-name");
    $element->click();
    $element->value($user);
    $element = $this->phpunit_instance->byId("edit-pass");
    $element->click();
    $element->value($pass);
    $element = $this->phpunit_instance->byId("edit-submit--2");
    $element->click();
    sleep(5);
  }

  /**
   * Function waitForElement wait until the element is appear.
   */
  public function waitForElement($selector, $time = self::WAIT_FOR_ELEMENT, $force = TRUE) {
    for ($second = 0; $second++) {
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
   * Function waitForPage.
   */
  public function waitForPage($time = self::WAIT_FOR_PAGE) {
    $this->phpunit_instance->waitForPageToLoad($time * 1000);
  }
}
