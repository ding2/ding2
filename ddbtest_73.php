<?php
class UserMenu extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testClickOnReservation()
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
    $this->assertEquals("My account", $this->getText("link=My account"));
    $this->assertTrue($this->isElementPresent("css=a.user-status.user-status-reservation > span.user-status-label"));
    $this->click("css=a.user-status.user-status-reservation > span.user-status-label");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My reservations", $this->getText("css=h2.pane-title"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
