<?php
class Reservation extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testChangeInterestPeriodOnReservation()
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
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("User status", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Mine bøder", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertEquals("Mine reserveringer", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertEquals("Mine hjemlån", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My reservations", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/h2"));
    $this->click("id=edit-reservations-1415027-1415027");
    $this->assertTrue($this->isElementPresent("//*[@id=\"edit-actions-top-delete--2\"]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"edit-actions-top-update\"]"));
    $this->mouseDown("//*[@id=\"edit-actions-top-update\"]");
    sleep(3);
    $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-update-reservations-form\"]/div/div[1]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-update-reservations-form\"]/div/div[2]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"edit-submit--2\"]"));
    $this->select("//*[@id=\"edit-provider-options-interest-period\"]", "2 months");
    $this->mouseDown("//*[@id=\"edit-submit--2\"]");
    sleep(3);
    $this->assertEquals("Your reservations has been updated.", $this->getText("id=ui-id-1"));
    $this->click("//div[4]/div/button");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("02-11-2014 00:00", $this->getText("css=li.item-information.expire-date > div.item-information-data"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>
