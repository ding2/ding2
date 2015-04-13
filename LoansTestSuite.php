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

    $url = $this->config->getLms() . '/patron/loans?borrCard=' . $this->config->getUser() . '&pinCode=' . $this->config->getPass();
    $this->mock = new SimpleXMLElement($url, 0, TRUE);

    resetState();
  }

  /**
   * Test material information.
   *
   * Check that each loan has corrent date, due date and number.
   */
  public function testMaterialInformation() {
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

    // Go to loans page.
    $this->assertElementPresent('link=Mine hjemlån');
    $this->click('link=Mine hjemlån');
    $this->abstractedPage->waitForPage();

    // Check for page title.
    $this->assertElementContainsText('css=h2.pane-title', 'Loan list');

    // Tricky part.
    // In order to check the data shown, it's required to have the raw
    // data from the LMS.

    // Start from this number, since nth-child pseuo-selector
    // counts from all children, no the direct css selector result.
    $index = 3;
    foreach ($this->mock->getLoansResponse->loans->children() as $l) {
      // Compare loan date.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:nth-child(' . $index . ') .item-information-list .loan-date .item-information-label', 'Loan date:');
      $loanDate = date('j. F Y', strtotime((string) $l->attributes()->loanDate));
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:nth-child(' . $index . ') .item-information-list .loan-date .item-information-data', $loanDate);

      // Compare due date.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:nth-child(' . $index . ') .item-information-list .expire-date .item-information-label', 'Return date:');
      $dueDate = date('j. F Y', strtotime((string) $l->attributes()->loanDueDate));
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:nth-child(' . $index . ') .item-information-list .expire-date .item-information-data', $dueDate);

      // Compare item id.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:nth-child(' . $index . ') .item-information-list .material-number .item-information-label', 'Material no.:');
      $id = (string) $l->attributes()->id;
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:nth-child(' . $index . ') .item-information-list .material-number .item-information-data', $id);

      $index++;
    }
  }
}
