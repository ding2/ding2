<?php
class Example extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*chrome");
    $this->setBrowserUrl("http://d2t.am.ci.inlead.dk/");
  }

  public function testMyTestCase()
  {
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("link=My account"));
    $this->click("css=a.user-status.user-status-ready-pickup > span.user-status-label");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My reservations", $this->getText("css=h2.pane-title"));
    $this->click("id=edit-reservations-1414248-1414248");
    $this->assertTrue($this->isElementPresent("//*[@id=\"edit-actions-top-delete\"]"));
    $this->mouseDown("//*[@id=\"edit-actions-top-delete\"]");
    sleep(3);
    $this->assertTrue((bool)preg_match('/^Are you sure you want to delete these reservations[\s\S]$/',$this->getText("//*[@id=\"ding-reservation-delete-reservations-form\"]/div/div")));
    $this->mouseDown("//*[@id=\"edit-submit--2\"]");
    sleep(3);
    $this->assertEquals("Your reservations have been deleted.", $this->getText("//*[@id=\"ui-id-1\"]"));
    $this->click("//div[4]/div/button");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>