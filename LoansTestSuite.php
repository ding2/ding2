<?php

require_once(dirname(__FILE__) . '/config.inc');

class Loans extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  /**
   * Test material information.
   *
   * Check that each loan has corrent date, due date and number.
   */
  public function testMaterialInformation() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("link=Login");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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
      $result = $xpath->query("//form[@id='ding-loan-loans-form']/div[div[//li[contains(@class, 'loan-date')]//div[contains(., '{$loanDate}')]
        and //li[contains(@class, 'material-number')]//div[contains(., '{$id}')]]]");
      $this->assertTrue($result->length == 1);

      $loanDueDate = date('d-m-Y H:s', strtotime((string)$l->attributes()->loanDueDate));
      $result = $xpath->query("//form[@id='ding-loan-loans-form']/div[div[//li[contains(@class, 'expire-date')]//div[contains(., '{$loanDueDate}')]
        and //li[contains(@class, 'material-number')]//div[contains(., '{$id}')]]]");
      $this->assertTrue($result->length == 1);
    }
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Test grouping loans by due date.
   *
   * Check that each loan grouped by due date.
   */
  public function testGroupByDueDate() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("User status", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Mine bøder", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertEquals("Mine reserveringer", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertEquals("Mine hjemlån", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Due in 5 days, 16/09/14", $this->getText("css=label.option"));
    $this->assertEquals("Det godes pris : roman", $this->getText("link=Det godes pris : roman"));
    $this->assertEquals("Due in 1 week, 24/09/14", $this->getText("//form[@id='ding-loan-loans-form']/div/div[4]/div/label"));
    $this->assertEquals("Dukken i spejlet", $this->getText("link=Dukken i spejlet"));
    $this->assertEquals("Misterioso", $this->getText("link=Misterioso"));
    $this->assertEquals("Due in 2 weeks, 30/09/14", $this->getText("//form[@id='ding-loan-loans-form']/div/div[7]/div/label"));
    $this->assertEquals("Farlige drømme : kriminalroman", $this->getText("link=Farlige drømme : kriminalroman"));
    $this->assertEquals("Due in 4 weeks, 10/10/14", $this->getText("//form[@id='ding-loan-loans-form']/div/div[9]/div/label"));
    $this->assertEquals("Det gemmer sig i mørket og andre gys", $this->getText("link=Det gemmer sig i mørket og andre gys"));
    $this->assertEquals("Due in 1 month, 13/10/14", $this->getText("//form[@id='ding-loan-loans-form']/div/div[11]/div/label"));
    $this->assertEquals("Min søster Jodie", $this->getText("link=Min søster Jodie"));
    $this->assertEquals("Due in 1 month, 28/10/14", $this->getText("//form[@id='ding-loan-loans-form']/div/div[13]/div/label"));
    $this->assertEquals("Drengen og gården", $this->getText("link=Drengen og gården"));
    $this->assertEquals("Elsker mig - elsker mig ikke : kærlighedsnoveller fra hele Norden", $this->getText("link=Elsker mig - elsker mig ikke : kærlighedsnoveller fra hele Norden"));
    $this->assertEquals("Helt vild med heste : noveller, facts, tips og quiz om heste", $this->getText("link=Helt vild med heste : noveller, facts, tips og quiz om heste"));
    $this->assertEquals("Kampnat", $this->getText("link=Kampnat"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
