<?php

require_once(dirname(__FILE__) . '/config.inc');

class Payments extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  /**
   * Test payment information.
   *
   * Check that each payment in account form equal to payment on server side.
   */
  public function testPaymentInfo() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=My account"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span");
    $this->waitForPageToLoad("30000");

    // Get mock object.
    $url = "http://alma.am.ci.inlead.dk/web/alma/patron/debts?borrCard=" . TARGET_URL_USER . "&pinCode=" . TARGET_URL_USER_PASS;
    $mock = new SimpleXMLElement($url, 0, TRUE);
    //Get DOM
    $dom = new DOMDocument();
    // Disable warnings, cause we have wrong html.
    libxml_use_internal_errors(true);
    $dom->loadHTML($this->getHtmlSource());
    $xpath = new DOMXPath($dom);
    foreach ($mock->getDebtsResponse->debts->children() as $d) {

      $debtNote = (string)$d->attributes()->debtNote;
      $debtNote = explode('  ', $debtNote);
      $result = $xpath->query("//form[@id='ding-debt-debts-form']//li[contains(@class, 'material-number')]//div[contains(., '{$debtNote[0]}')]");
      $this->assertTrue($result->length == 1);

      $debtDate = date('d-m-Y H:s', strtotime((string)$d->attributes()->debtDate));
      $result = $xpath->query("//form[@id='ding-debt-debts-form']//li[contains(@class, 'fee-date')]//div[contains(., '{$debtDate}')]");
      $this->assertTrue($result->length == 1);

      $debtAmountFormatted = trim((string)$d->attributes()->debtAmountFormatted);
      $result = $xpath->query("//form[@id='ding-debt-debts-form']//li[contains(@class, 'fee_amount')]//div[contains(., '{$debtAmountFormatted} Kr')]");
      $this->assertTrue($result->length == 1);

      preg_match('/(.*)Debt$/', trim((string)$d->attributes()->debtType), $debtType);
      $result = $xpath->query("//form[@id='ding-debt-debts-form']//li[contains(@class, 'fee-type')]//div[2]")->item(0)->nodeValue;
      $result =  strtolower(str_replace(' ', '', $result));
      $debtType = strtolower($debtType[1]);
      $this->assertTrue($result == $debtType);
    }
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Test click to "Pay all balances" button.
   *
   * Check that after clicking was valid redirect.
   */
  public function testPayAllBalances() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user$/',$this->getLocation()));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user\/\d+\/status\/debts$/',$this->getLocation()));
    $this->click("id=edit-pay-all");
    $this->waitForPageToLoad("30000");
    sleep(4);
    $url = $this->getLocation();
    $this->assertTrue($url == "https://payment.architrade.com/payment/paytype.pml");
  }

  /**
   * Test total amount of payments.
   *
   * Check that total amount on account page was equal to infomation from server.
   */
  public function testTotal() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=My account"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span");
    $this->waitForPageToLoad("30000");
    // Get mock object.
    $url = "http://alma.am.ci.inlead.dk/web/alma/patron/debts?borrCard=" . TARGET_URL_USER . "&pinCode=" . TARGET_URL_USER_PASS;
    $mock = new SimpleXMLElement($url, 0, TRUE);
    $total = trim((string)$mock->getDebtsResponse->debts->attributes()->totalDebtAmountFormatted);
    $this->assertEquals("{$total} Kr", $this->getText("css=span.amount"));
  }

  /**
   * Test click to "Pay selected balances" button.
   *
   * Check that after clicking was valid redirect.
   */
  public function testPaySelectedBalances() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user$/',$this->getLocation()));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user\/\d+\/status\/debts$/',$this->getLocation()));
    $this->click("id=edit-629042");
    sleep(2);
    $this->click("id=edit-pay-selected");
    $this->waitForPageToLoad("30000");
    sleep(4);
    $url = $this->getLocation();
    $this->assertTrue($url == "https://payment.architrade.com/payment/paytype.pml");
  }
}
