<?php

class UserMenuTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Check loan link and loan page in user profile.
   */
  public function testUserMenu() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Expect user page link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check the page we are now.
    $this->assertElementContainsText('css=.pane-title', 'Your user loan status');

    // Check for the user menu.
    $this->assertElementPresent('link=Lån, reserveringer og mellemværende');
    $this->click('link=Lån, reserveringer og mellemværende');
    $this->abstractedPage->waitForPage();

    // Check for menu items.
    $this->assertElementPresent('link=Mine bøder');
    $this->assertElementPresent('link=Mine reserveringer');
    $this->assertElementPresent('link=Mine hjemlån');

    // Check debts page.
    $this->click('link=Mine bøder');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=.pane-title', 'My debts');

    // Check reservations page.
    $this->click('link=Mine reserveringer');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=.pane-title', 'My reservations');

    // Check loans page.
    $this->click('link=Mine hjemlån');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=.pane-title', 'Loan list');
  }
}
