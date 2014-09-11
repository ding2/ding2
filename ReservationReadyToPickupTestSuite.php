<?php

require_once(dirname(__FILE__) . '/config.inc');

class ReservationReadyToPickup extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl('http://d2t.am.ci.inlead.dk/');
  }

  /**
   * Check reservation ready for pickup data on my reservation page.
   */
  public function testMaterialInformation()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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
    $this->assertEquals("Hjørring", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[3]/div[2]/ul/li[3]/div[2]"));
    $this->assertEquals("02-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[3]/div[2]/ul/li[4]/div[2]"));
    $this->assertEquals("0", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li/div[2]"));
    $this->assertEquals("15-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li[2]/div[2]"));
    $this->assertEquals("Bogbus", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li[3]/div[2]"));
    $this->assertEquals("02-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-ready-form']/div/div[4]/div[2]/ul/li[4]/div[2]"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check reservation ready for pickup page and items data on it.
   */
  public function testReservationsReadyForPickupMaterialInformation()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("css=a.user-status.user-status-ready-pickup > span.user-status-label"));
    $this->click("css=a.user-status.user-status-ready-pickup > span.user-status-label");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("css=label.option"));
    $this->assertTrue($this->isElementPresent("link=The lady"));
    $this->assertTrue($this->isElementPresent("link=Angels and demons"));
    $this->click("link=Logout");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check deletion of reservation ready for pickup.
   */
  public function testDeleteReservationReadyForPickUp()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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
