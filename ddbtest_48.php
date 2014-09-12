<?php
class Loans extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testMaterialInformation()
  {
    $this->open("/en");
    $this->click("link=Login");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("User status", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Loan list", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/h2"));
    // Get mock object.
    $url = "http://alma.am.ci.inlead.dk/web/alma/patron/loans?borrCard=1111110022&pinCode=5555";
    $mock = new SimpleXMLElement($url, 0, TRUE);
    //Get DOM
    $dom = new DOMDocument();
    // Disable warnings, cause we have wrong html.
    libxml_use_internal_errors(true);
    $dom->loadHTML($this->getHtmlSource());
    $xpath = new DOMXPath($dom);
    foreach ($mock->getLoansResponse->loans->children() as $l) {

      $id = (string)$l->attributes()->id;
      $result = $xpath->query("//form[@id='ding-loan-loans-form']//li[contains(@class, 'material-number')]//div[contains(., '{$id}')]");
      $this->assertTrue($result->length == 1);

      $loanDate = date('d-m-Y H:s', strtotime((string)$l->attributes()->loanDate));
      $result = $xpath->query("//form[@id='ding-loan-loans-form'][//li[contains(@class, 'loan-date')]//div[contains(., '{$loanDate}')]
        and //li[contains(@class, 'material-number')]//div[contains(., '{$id}')]]");
      $this->assertTrue($result->length == 1);

      $loanDueDate = date('d-m-Y H:s', strtotime((string)$l->attributes()->loanDueDate));
      $result = $xpath->query("//form[@id='ding-loan-loans-form'][//li[contains(@class, 'expire-date')]//div[contains(., '{$loanDueDate}')]
        and //li[contains(@class, 'material-number')]//div[contains(., '{$id}')]]");
      $this->assertTrue($result->length == 1);
    }
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
