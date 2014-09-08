<?php
class ReservationReadyToPickup extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testMaterialInformation()
  {
    $this->open("/en");
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("Reservations ready for pick-up", $this->getText("css=a.user-status.user-status-ready-pickup > span.user-status-label"));
    $this->click("css=a.user-status.user-status-ready-pickup > span.user-status-label");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("255", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[3]/div[2]/ul/li/div[2]"));
    $this->assertEquals("11-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[3]/div[2]/ul/li[2]/div[2]"));
    $this->assertEquals("Hjørring", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[3]/div[2]/ul/li[3]/div[2]"));
    $this->assertEquals("02-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[3]/div[2]/ul/li[4]/div[2]"));
    $this->assertEquals("0", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li/div[2]"));
    $this->assertEquals("15-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li[2]/div[2]"));
    $this->assertEquals("Bogbus", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li[3]/div[2]"));
    $this->assertEquals("02-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li[4]/div[2]"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
