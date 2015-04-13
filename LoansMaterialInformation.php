<?php

require_once(__DIR__ . '/autoload.php');
require_once(__DIR__ . '/bootstrap.php');

class Loans extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstraction;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  public function testLoansMaterialInformation() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for user account link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for user status link.
    $this->assertElementPresent('link=User status');
    $this->click('link=User status');
    $this->abstractedPage->waitForPage();

    // Check for material related links.
    // Weird, but these are not translated.
    $this->assertElementPresent('link=Mine bøder');
    $this->assertElementPresent('link=Mine reserveringer');
    $this->assertElementPresent('link=Mine hjemlån');

    // Go to loans page.
    $this->click('link=Mine hjemlån');
    $this->abstractedPage->waitForPage();

    // Check for page title.
    $this->assertElementContainsText('css=h2.pane-title', 'Loan list');

    // There should be at least one loan.
    $this->assertElementPresent('css=.material-item:first');

    // ... and it should be "Det godes pris : roman".
    $this->assertElementPresent('link=Det godes pris : roman');

    // Click on it's title.
    $this->click('link=Det godes pris : roman');
    $this->abstractedPage->waitForPage();

    // Check the page where link landed.
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A50659275$/', $this->getLocation()));
    $this->assertElementContainsText('css=.pane-ting-object .ting-object.view-mode-full .field-name-ting-title h2', 'Det godes pris : roman');
  }
}
