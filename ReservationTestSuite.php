<?php

require_once(dirname(__FILE__) . '/config.inc');

class Reservation extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  /**
   * Check material information on user reservation page.
   */
  public function testReservationMaterialInformation()
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
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("User status", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Mine bøder", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->verifyText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span", "Mine reserveringer");
    $this->assertEquals("Mine hjemlån", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My reservations", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/h2"));
    $this->assertEquals("1", $this->getText("css=li.item-information.queue-number > div.item-information-data"));
    $this->assertEquals("02-12-2014 00:00", $this->getText("css=li.item-information.expire-date > div.item-information-data"));
    $this->assertEquals("Sindal", $this->getText("css=#ding-reservation-reservations-notready-form > div > div.material-item.odd > div.right-column > ul.item-information-list > li.item-information.pickup-branch > div.item-information-data"));
    $this->assertEquals("04-09-2014 00:00", $this->getText("css=#ding-reservation-reservations-notready-form > div > div.material-item.odd > div.right-column > ul.item-information-list > li.item-information.created-date > div.item-information-data"));
    $this->assertEquals("1415027", $this->getText("css=#ding-reservation-reservations-notready-form > div > div.material-item.odd > div.right-column > ul.item-information-list > li.item-information.pickup-id > div.item-information-data"));
    $this->assertEquals("1", $this->getText("css=div.material-item.even > div.right-column > ul.item-information-list > li.item-information.queue-number > div.item-information-data"));
    $this->assertEquals("03-09-2015 00:00", $this->getText("css=div.material-item.even > div.right-column > ul.item-information-list > li.item-information.expire-date > div.item-information-data"));
    $this->assertEquals("Sindal", $this->getText("css=#ding-reservation-reservations-notready-form > div > div.material-item.even > div.right-column > ul.item-information-list > li.item-information.pickup-branch > div.item-information-data"));
    $this->assertEquals("02-09-2014 00:00", $this->getText("css=#ding-reservation-reservations-notready-form > div > div.material-item.even > div.right-column > ul.item-information-list > li.item-information.created-date > div.item-information-data"));
    $this->assertEquals("1415949", $this->getText("css=#ding-reservation-reservations-notready-form > div > div.material-item.even > div.right-column > ul.item-information-list > li.item-information.pickup-id > div.item-information-data"));
    $this->assertEquals("1", $this->getText("//form[@id='ding-reservation-reservations-notready-form']/div/div[5]/div[2]/ul/li[2]/div[2]"));
    $this->assertEquals("30-11-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-notready-form']/div/div[5]/div[2]/ul/li[3]/div[2]"));
    $this->assertEquals("Sindal", $this->getText("//form[@id='ding-reservation-reservations-notready-form']/div/div[5]/div[2]/ul/li[4]/div[2]"));
    $this->assertEquals("02-09-2014 00:00", $this->getText("//form[@id='ding-reservation-reservations-notready-form']/div/div[5]/div[2]/ul/li[5]/div[2]"));
    $this->assertEquals("1414204", $this->getText("//form[@id='ding-reservation-reservations-notready-form']/div/div[5]/div[2]/ul/li[6]/div[2]"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check titles of materials on user reservation page.
   */
  public function testReservationsMaterialTitle()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=My account"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent('//*[@id="ding-reservation-reservations-ready-form"]/div/div[3]/div[2]/h3/a'));
    $this->assertTrue($this->isElementPresent("link=Angels and demons"));
    $this->click("link=Logout");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check change of interest period on user reservation page.
   */
  public function testChangeInterestPeriodOnReservation()
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
    sleep(5);
    $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-update-reservations-form\"]/div/div[1]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-update-reservations-form\"]/div/div[2]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"edit-submit--2\"]"));
    $this->select("//*[@id=\"edit-provider-options-interest-period\"]", "2 months");
    $this->mouseDown("//*[@id=\"edit-submit--2\"]");
    sleep(5);
    $this->assertEquals("Your reservations has been updated.", $this->getText("id=ui-id-1"));
    $this->click("//div[4]/div/button");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("02-11-2014 00:00", $this->getText("css=li.item-information.expire-date > div.item-information-data"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check change of pickup branch on user reservation page.
   */
  public function testChangePickupBranchOnReservation()
  {
    $this->open("/" .TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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
    sleep(5);
    $this->assertTrue($this->isElementPresent("id=ui-id-2"));
    $this->assertTrue($this->isElementPresent("id=edit-provider-options-alma-preferred-branch"));
    $this->assertTrue($this->isElementPresent("id=edit-provider-options-interest-period"));
    $this->select("//*[@id=\"edit-provider-options-alma-preferred-branch\"]", "Bogbus");
    $this->mouseDown("//*[@id=\"edit-submit--2\"]");
    sleep(5);
    $this->assertTrue($this->isElementPresent("id=ui-id-1"));
    $this->click("//div[4]/div/button");
    sleep(5);
    $this->assertEquals("Bogbus", $this->getText('//*[@id="ding-reservation-reservations-notready-form"]/div/div[3]/div[2]/ul/li[3]/div[2]'));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check material deletion on user reservation page.
   */
  public function testDeleteReservation()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=My account"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->click("id=edit-reservations-1415027-1415027");
    $this->assertTrue($this->isElementPresent("id=edit-actions-top-delete--2"));
    $this->assertTrue($this->isElementPresent("id=edit-actions-top-update"));
    $this->clickAt("id=edit-actions-top-delete--2", "");
    sleep(5);
    $this->waitForPageToLoad("");
    $this->clickAt("id=edit-submit--2", "");
    sleep(5);
    $this->click("//div[4]/div/button");
    $this->waitForPageToLoad("");
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
