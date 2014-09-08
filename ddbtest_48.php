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
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[3]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[3]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[3]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[3]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[5]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[5]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[5]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[5]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[7]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[7]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[7]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[7]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[8]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[8]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[8]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[8]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[10]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[10]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[10]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[10]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[12]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[12]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[12]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[12]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[14]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[14]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[14]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[14]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[15]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[15]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[15]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[15]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[16]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[16]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[16]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[16]/div[2]/ul/li[3]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[17]/div[2]/h3/a"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[17]/div[2]/ul/li/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[17]/div[2]/ul/li[2]/div[2]"));
    $this->assertTrue($this->isElementPresent("//form[@id='ding-loan-loans-form']/div/div[17]/div[2]/ul/li[3]/div[2]"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
