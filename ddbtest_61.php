<?php
class Payments extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testPayBalancesOnAMaterial()
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
    $this->assertEquals("Mine bøder", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertEquals("Mine reserveringer", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertEquals("Mine hjemlån", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My debts", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/h2"));
    $this->click("id=edit-629042");
    $this->click("id=edit-pay-selected");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("https://payment.architrade.com/payment/paytype.pml", $this->getLocation());
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
