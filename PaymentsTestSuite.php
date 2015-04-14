<?php

require_once(__DIR__ . '/autoload.php');
require_once(__DIR__ . '/bootstrap.php');

class Payments extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstraction;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());

    $url = $this->config->getLms() . '/alma/patron/debts?borrCard=' . $this->config->getUser() . '&pinCode=' . $this->config->getPass();
    $this->mock = new SimpleXMLElement($url, 0, TRUE);

    resetState($this->config->getLms());
  }

  /**
   * Test payment information.
   *
   * Check that each payment in account form equal to payment on server side.
   */
  public function testPayments() {
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

    // Go to debts page.
    $this->assertElementPresent('link=Mine bøder');
    $this->click('link=Mine bøder');
    $this->abstractedPage->waitForPage();

    // Check for page title.
    $this->assertElementContainsText('css=h2.pane-title', 'My debts');

    // Tricky part.
    // In order to check the data shown, it's required to have the raw
    // data from the LMS.
    $index = 1;
    foreach ($this->mock->getDebtsResponse->debts->children() as $d) {
      $note = array_values(array_filter(explode(' ', (string) $d->attributes()->debtNote)));
      // Compare debt title.
      $this->assertElementContainsText('css=#ding-debt-debts-form .material-item:nth-child(' . $index . ') .item-title', $note[1]);
      // Compare material id.
      $this->assertElementContainsText('css=#ding-debt-debts-form .material-item:nth-child(' . $index . ') .item-information-list .material-number .item-information-label', 'Material no.:');
      $this->assertElementContainsText('css=#ding-debt-debts-form .material-item:nth-child(' . $index . ') .item-information-list .material-number .item-information-data', $note[0]);

      // Compare created date.
      $this->assertElementContainsText('css=#ding-debt-debts-form .material-item:nth-child(' . $index . ') .item-information-list .fee-date .item-information-label', 'Created date:');
      $debtDate = date('j. F Y', strtotime((string) $d->attributes()->debtDate));
      $this->assertElementContainsText('css=#ding-debt-debts-form .material-item:nth-child(' . $index . ') .item-information-list .fee-date .item-information-data', $debtDate);

      // Compare amount.
      $this->assertElementContainsText('css=#ding-debt-debts-form .material-item:nth-child(' . $index . ') .item-information-list .fee_amount .item-information-label', 'Amount:');
      $debtAmount = trim((string) $d->attributes()->debtAmountFormatted);
      $this->assertElementContainsText('css=#ding-debt-debts-form .material-item:nth-child(' . $index . ') .item-information-list .fee_amount .item-information-data', $debtAmount . ' Kr');

      $index++;
    }

    // Test total amount.
    $total = trim((string) $this->mock->getDebtsResponse->debts->attributes()->totalDebtAmountFormatted);
    $this->assertElementContainsText('css=#edit-total .amount', $total . ' Kr');

    // @todo
    // Test payment procedure.
  }
}
