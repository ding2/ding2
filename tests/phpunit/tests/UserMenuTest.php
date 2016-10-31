<?php

require_once 'Ding2TestBase.php';

class UserMenuTest extends Ding2TestBase {
  protected function setUp() {
    parent::setUp();
    resetState($this->config->getLms());
    $this->config->resetLms();
  }

  /**
   * Check loan link and loan page in user profile.
   */
  public function testUserMenu() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Expect user page link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for the user menu.
    //if ($this->config->getServer() == 'localhost') {
      $this->assertElementPresent('link=User status');
      $this->click('link=User status');
      $this->abstractedPage->waitForPage();
    //}
   /*else if ($this->config->getServer() == 'CircleCI') {
      $this->assertElementPresent('link=Lån, reserveringer og mellemværende');
      $this->click('link=Lån, reserveringer og mellemværende');
      $this->abstractedPage->waitForPage();
    }*/

    // Check for menu items.
    $this->assertElementPresent('link=Mine bøder');
    $this->assertElementPresent('link=Mine reserveringer');
    $this->assertElementPresent('link=Mine hjemlån');

    // Check debts page.
    $this->click('link=Mine bøder');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=.pane-debts .pane-title', 'My debts');

    // Check reservations page.
    $this->click('link=Mine reserveringer');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=.pane-reservations .pane-title', 'My reservations');

    // Check loans page.
    $this->click('link=Mine hjemlån');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=.pane-loans .pane-title', 'Loan list');
  }
}
