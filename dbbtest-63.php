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

  public function testTotal() {
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
    $total = trim((string)$mock->getDebtsResponse->debts->attributes()->totalDebtAmountFormatted);
    $this->assertEquals("{$total} Kr", $this->getText("css=span.amount"));
  }

}
?>
