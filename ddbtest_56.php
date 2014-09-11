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
    $this->assertEquals("User status", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Mine bøder", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertEquals("Mine reserveringer", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertEquals("Mine hjemlån", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My reservations", $this->getText("css=h2.pane-title"));
    $this->click("id=edit-reservations-1415027-1415027");
    $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-reservations-notready-form\"]/div/div[1]/div[1]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-reservations-notready-form\"]/div/div[1]/div[2]"));
    $this->mouseDown("//*[@id=\"edit-actions-top-update\"]");
    // $this->waitForPageToLoad("30000");
    sleep(3);
    $this->assertEquals("Update reservations", $this->getText("id=ui-id-2"));
    $this->assertTrue($this->isElementPresent("id=edit-provider-options-alma-preferred-branch"));
    $this->assertTrue($this->isElementPresent("id=edit-provider-options-interest-period"));
    $this->select("//*[@id=\"edit-provider-options-alma-preferred-branch\"]", "Bogbus");
    $this->mouseDown("//*[@id=\"edit-submit--2\"]");
    sleep(3);
    $this->assertEquals("Your reservations has been updated.", $this->getText("id=ui-id-1"));
    $this->click("//div[4]/div/button");
    // $this->waitForPageToLoad("30000");
    sleep(3);
    $this->assertEquals("Bogbus", $this->getText("css=#ding-reservation-reservations-notready-form > div > div.material-item.even > div.right-column > ul.item-information-list > li.item-information.pickup-branch > div.item-information-data"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>