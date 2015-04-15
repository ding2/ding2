<?php

require_once(__DIR__ . '/../bootstrap.php');

class LoansTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());

    $url = $this->config->getLms() . '/alma/patron/loans?borrCard=' . $this->config->getUser() . '&pinCode=' . $this->config->getPass();
    $this->mock = new SimpleXMLElement($url, 0, TRUE);

    resetState($this->config->getLms());
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
    $this->assertElementPresent('link=Lån, reserveringer og mellemværende');
    $this->click('link=Lån, reserveringer og mellemværende');
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

    // Tricky part.
    // In order to check the data shown, it's required to have the raw
    // data from the LMS.

    // Start from this number, since eq pseuo-selector
    // counts from all children, no the direct css selector result.
    $index = 0;
    foreach ($this->mock->getLoansResponse->loans->children() as $l) {
      // Compare loan date.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .loan-date .item-information-label', 'Loan date:');
      $loanDate = date('j. F Y', strtotime((string) $l->attributes()->loanDate));
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .loan-date .item-information-data', $loanDate);

      // Compare due date.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .expire-date .item-information-label', 'Return date:');
      $dueDate = date('j. F Y', strtotime((string) $l->attributes()->loanDueDate));
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .expire-date .item-information-data', $dueDate);

      // Compare item id.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .material-number .item-information-label', 'Material no.:');
      $id = (string) $l->attributes()->id;
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .material-number .item-information-data', $id);

      $index++;
    }

    // Click on an item title.
    $this->assertElementPresent('link=Det godes pris : roman');
    $this->click('link=Det godes pris : roman');
    $this->abstractedPage->waitForPage();

    // Check the page where link landed.
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A50659275$/', $this->getLocation()));
    $this->assertElementContainsText('css=.pane-ting-object .ting-object.view-mode-full .field-name-ting-title h2', 'Det godes pris : roman');
  }
}
