<?php
class Payments extends PHPUnit_Extensions_SeleniumTestCase
{

  private $base_url = "http://alma.am.ci.inlead.dk/web/alma/patron/debts";

  private $get_params = array(
    "borrCard" => "1111110022",
    'pinCode' => '5555',
  );


  private function generateXmlUrl() {

    if (empty($this->get_params)) {
      return $this->base_url;
    }

    $p = array();
    foreach ($this->get_params as $param => $val) {
      $p[] = "{$param}={$val}";
    }
    $p = implode('&',$p);

    return "{$this->base_url}?{$p}";
  }

  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal/");
  }

  public function testPaymentInfo()
  {
    $this->open("/en");
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
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
    $url = $this->generateXmlUrl();
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
}
?>
