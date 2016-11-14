<?php

require_once 'Ding2TestBase.php';

class LoansTest extends Ding2TestBase {
  protected function setUp() {
    parent::setUp();
    $url = $this->config->getLms() . 'patron/loans?borrCard=' . $this->config->getUser() . '&pinCode=' . $this->config->getPass();
    $this->mock = new DOMDocument();
    $this->mock->loadXML(@file_get_contents($url));
    resetState($this->config->getLms());
    $this->config->resetLms();
  }

  public function testLoansMaterialInformation() {

    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();

    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for user account link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for material related links.
    $this->assertElementPresent('link=Fines');
    $this->assertElementPresent('link=Loans overdue');
    $this->assertElementPresent('link=Reservations ready for pick-up');
    $this->assertElementPresent('link=Reservations');
    $this->assertElementPresent('link=Loans');

    // Go to loans page.
    $this->click('link=Loans');
    $this->abstractedPage->waitForPage();

    // Check for page title.
    $this->assertElementContainsText('css=div.primary-content h2.pane-title', 'Loan list');

    // Tricky part.
    // In order to check the data shown, it's required to have the raw
    // data from the LMS.

    // Parsing taken from ALMA module, to have same sorted result.
    $loans = array();
    foreach ($this->mock->getElementsByTagName('loan') as $item) {
      $id = $item->getAttribute('id');
      $loan = array(
        'id' => $id,
        'branch' => $item->getAttribute('loanBranch'),
        'loan_date' => $item->getAttribute('loanDate'),
        'due_date' => $item->getAttribute('loanDueDate'),
        'is_renewable' => ($item->getElementsByTagName('loanIsRenewable')->item(0)->getAttribute('value') == 'yes') ? TRUE : FALSE,
        'record_id' => $item->getElementsByTagName('catalogueRecord')->item(0)->getAttribute('id'),
        'record_available' => $item->getElementsByTagName('catalogueRecord')->item(0)->getAttribute('isAvailable'),
      );
      if ($item->getElementsByTagName('note')->length > 0) {
        $loan['notes'] = $item->getElementsByTagName('note')->item(0)->getAttribute('value');
      }
      $loans[$id] = $loan;
    }
    uasort($loans, function($a, $b) {
      return strcmp($a['due_date'], $b['due_date']);
    });

    // Start from this number, since eq pseuo-selector
    // counts from all children, no the direct css selector result.
    $index = 0;
    foreach ($loans as $loan) {
      // Compare loan date.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .loan-date .item-information-label', 'Loan date:');
      $loanDate = date('j. F Y', strtotime($loan['loan_date']));
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .loan-date .item-information-data', $loanDate);

      // Compare due date.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .expire-date .item-information-label', 'Return date:');
      $dueDate = date('j. F Y', strtotime($loan['due_date']));
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .expire-date .item-information-data', $dueDate);

      // Compare item id.
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .material-number .item-information-label', 'Material no.:');
      $id = $loan['id'];
      $this->assertElementContainsText('css=#ding-loan-loans-form .material-item:eq(' . $index . ') .item-information-list .material-number .item-information-data', $id);

      $index++;
    }

    // Click on FIRST item title in the loans list.
    $this->assertElementPresent('link=HSP - det sensitive personlighedstræk : en håndbog med grundlæggende viden');
    $this->click('link=HSP - det sensitive personlighedstræk : en håndbog med grundlæggende viden');
    $this->abstractedPage->waitForPage();

    // Check the page where link landed.
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A29773955$/', $this->getLocation()));
    $this->assertElementContainsText('css=.pane-ting-object .ting-object.view-mode-full .field-name-ting-title h2', 'HSP - det sensitive personlighedstræk : en håndbog med grundlæggende viden');
  }
}
