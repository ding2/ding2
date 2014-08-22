<?php
class OpenScan extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testSubmitAnon()
  {
    $this->open("/en");
    $this->type("id=edit-search-block-form--2", "harry potter");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=li.list-item.search-result"));
    $this->type("id=edit-search-block-form--2", "");
    $this->click("id=edit-submit--3");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=div.messages.error"));
  }

  public function testSubmitLoggedIn()
  {
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->type("id=edit-search-block-form--2", "inferno dan brown");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Inferno"));
    $this->type("id=edit-search-block-form--2", "");
    $this->click("id=edit-submit--3");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=div.messages.error"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>
