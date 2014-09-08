<?php
class UserMenu extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testClickOnLoans()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("Loans", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/div/a[3]/span[2]"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/div/div/div/a[3]/span[2]");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Loan list", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/h2"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>