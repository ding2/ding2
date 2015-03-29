<?php
/**
 * @file
 * Page abstractions implementation.
 */
class DDBTestPageAbstraction {
  private $phpunit_instance = NULL;

  public function __construct(PHPUnit_Extensions_SeleniumTestCase $instance) {
    $this->phpunit_instance = $instance;
  }

  /**
   * Login the user into the testing environment, using the
   * proposed credentials.
   *
   * @param string $user
   *   User name.
   * @param string $pass
   *   User password.
   */
  public function userLogin($user, $pass) {
    $this->phpunit_instance->click("css=.topbar-menu a.topbar-link-user");
    $this->phpunit_instance->type("css=#edit-name", $user);
    $this->phpunit_instance->type("css=#edit-pass", $pass);
    $this->phpunit_instance->click("css=#edit-submit--2");
    $this->phpunit_instance->waitForPageToLoad("30000");
  }
}
