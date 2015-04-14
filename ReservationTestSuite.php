<?php

require_once(__DIR__ . '/autoload.php');
require_once(__DIR__ . '/bootstrap.php');

class Reservation extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());

    resetState();
  }

  /**
   * Check material information on user reservation page.
   */
  public function testReservation() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for user account link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for reservation ready for pickup quick link.
    $this->assertElementPresent('link=5 Reservations');
    $this->click('link=5 Reservations');
    $this->abstractedPage->waitForPage();

    // Check for correct page heading.
    $this->assertElementContainsText('css=h2.pane-title', 'My reservations');

    // Next section roughly checks the markup.
    // This relies on the dummy LMS service, so the data should be pre-defined.
    $notready_for_pickup = array(
      array(
        'Nøglen til Da Vinci mysteriet',
        '',
        '1',
        '2. December 2014',
        'Sindal',
        '4. September 2014',
        '1415027',
      ),
      array(
        'Alt for damerne',
        '2010, 39',
        '1',
        '30. November 2014',
        'Sindal',
        '2. September 2014',
        '1414204',
      ),
      array(
        'Folkepension og delpension',
        '2014, 130. udgave',
        '1',
        '3. September 2015',
        'Sindal',
        '2. September 2014',
        '1415949',
      ),
    );
    for ($i = 3, $j = 0; $i <= count($notready_for_pickup) + 2; $i++, $j++) {
      // Check title field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') h3.item-title', $notready_for_pickup[$j][0]);

      // Check periodical number field.
      if (!empty($notready_for_pickup[$j][1])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.periodical-number .item-information-label', 'Periodical no.:');
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.periodical-number .item-information-data', $notready_for_pickup[$j][1]);
      }

      // Check queue number field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.queue-number .item-information-label', 'Queue number:');
      if (!empty($notready_for_pickup[$j][2])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.queue-number .item-information-data', $notready_for_pickup[$j][2]);
      }

      // Check expiry date field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.expire-date .item-information-label', 'Expiry date:');
      if (!empty($notready_for_pickup[$j][3])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.expire-date .item-information-data', $notready_for_pickup[$j][3]);
      }

      // Check branch field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.pickup-branch .item-information-label', 'Pickup branch:');
      if (!empty($notready_for_pickup[$j][4])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.pickup-branch .item-information-data', $notready_for_pickup[$j][4]);
      }

      // Check created date field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.created-date .item-information-label', 'Created date:');
      if (!empty($notready_for_pickup[$j][5])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.created-date .item-information-data', $notready_for_pickup[$j][5]);
      }

      // Check order number field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.pickup-id .item-information-label', 'Order nr.:');
      if (!empty($notready_for_pickup[$j][6])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:nth-child(' . $i . ') li.pickup-id .item-information-data', $notready_for_pickup[$j][6]);
      }
    }

    // Test change of reservation period and pickup branch.
    $this->assertElementPresent('css=#ding-reservation-reservations-notready-form .material-item:nth-child(3) input[type="checkbox"]');
    $this->click('css=#ding-reservation-reservations-notready-form .material-item:nth-child(3) input[type="checkbox"]');

    // Wait for the buttons to appear.
    $this->abstractedPage->waitForElement('css=.update-reservations input[type="submit"]');
    $this->mouseDown('css=#ding-reservation-reservations-notready-form .update-reservations input[type="submit"]');

    // This will trigger a popup with selection options.
    $this->abstractedPage->waitForElement('css=.ding-popup-content');
    $this->assertElementPresent('css=#ding-reservation-update-reservations-form #edit-provider-options-alma-preferred-branch');
    $this->assertElementPresent('css=#ding-reservation-update-reservations-form #edit-provider-options-interest-period');
  }

//   /**
//    * Check change of interest period on user reservation page.
//    */
//   public function testChangeInterestPeriodOnReservation() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-name", TARGET_URL_USER);
//     $this->type("id=edit-pass", TARGET_URL_USER_PASS);
//     $this->click("id=edit-submit--2");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
//     $this->assertEquals("User status", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("Mine bøder", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
//     $this->assertEquals("Mine reserveringer", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
//     $this->assertEquals("Mine hjemlån", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("My reservations", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div/h2"));
//     $this->click("id=edit-reservations-1415027-1415027");
//     $this->assertTrue($this->isElementPresent("//*[@id=\"edit-actions-top-delete--2\"]"));
//     $this->assertTrue($this->isElementPresent("//*[@id=\"edit-actions-top-update\"]"));
//     $this->mouseDown("//*[@id=\"edit-actions-top-update\"]");
//     sleep(5);
//     $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-update-reservations-form\"]/div/div[1]"));
//     $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-update-reservations-form\"]/div/div[2]"));
//     $this->assertTrue($this->isElementPresent("//*[@id=\"edit-submit--2\"]"));
//     $this->select("//*[@id=\"edit-provider-options-interest-period\"]", "2 months");
//     $this->mouseDown("//*[@id=\"edit-submit--2\"]");
//     sleep(5);
//     $this->assertEquals("Your reservations has been updated.", $this->getText("id=ui-id-1"));
//     $this->click("//div[4]/div/button");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("02-11-2014 00:00", $this->getText("css=li.item-information.expire-date > div.item-information-data"));
//     $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
//     $this->waitForPageToLoad("30000");
//   }

//   /**
//    * Check change of pickup branch on user reservation page.
//    */
//   public function testChangePickupBranchOnReservation() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-name", TARGET_URL_USER);
//     $this->type("id=edit-pass", TARGET_URL_USER_PASS);
//     $this->click("id=edit-submit--2");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("My account", $this->getText("link=My account"));
//     $this->assertEquals("User status", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("Mine bøder", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
//     $this->assertEquals("Mine reserveringer", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
//     $this->assertEquals("Mine hjemlån", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("My reservations", $this->getText("css=h2.pane-title"));
//     $this->click("id=edit-reservations-1415027-1415027");
//     $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-reservations-notready-form\"]/div/div[1]/div[1]"));
//     $this->assertTrue($this->isElementPresent("//*[@id=\"ding-reservation-reservations-notready-form\"]/div/div[1]/div[2]"));
//     $this->mouseDown("//*[@id=\"edit-actions-top-update\"]");
//     sleep(5);
//     $this->assertTrue($this->isElementPresent("id=ui-id-2"));
//     $this->assertTrue($this->isElementPresent("id=edit-provider-options-alma-preferred-branch"));
//     $this->assertTrue($this->isElementPresent("id=edit-provider-options-interest-period"));
//     $this->select("//*[@id=\"edit-provider-options-alma-preferred-branch\"]", "Bogbus");
//     $this->mouseDown("//*[@id=\"edit-submit--2\"]");
//     sleep(5);
//     $this->assertTrue($this->isElementPresent("id=ui-id-1"));
//     $this->click("//div[4]/div/button");
//     sleep(5);
//     $this->assertEquals("Bogbus", $this->getText('//*[@id="ding-reservation-reservations-notready-form"]/div/div[3]/div[2]/ul/li[3]/div[2]'));
//     $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
//     $this->waitForPageToLoad("30000");
//   }

//   /**
//    * Check material deletion on user reservation page.
//    */
//   public function testDeleteReservation() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-name", TARGET_URL_USER);
//     $this->type("id=edit-pass", TARGET_URL_USER_PASS);
//     $this->click("id=edit-submit--2");
//     $this->waitForPageToLoad("30000");
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("link=My account"));
//     $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li/a/span"));
//     $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span"));
//     $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[3]/a/span"));
//     $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[3]/ul/li[2]/a/span");
//     $this->waitForPageToLoad("30000");
//     $this->click("id=edit-reservations-1415027-1415027");
//     $this->assertTrue($this->isElementPresent("id=edit-actions-top-delete--2"));
//     $this->assertTrue($this->isElementPresent("id=edit-actions-top-update"));
//     $this->clickAt("id=edit-actions-top-delete--2", "");
//     sleep(5);
//     $this->waitForPageToLoad("");
//     $this->clickAt("id=edit-submit--2", "");
//     sleep(5);
//     $this->click("//div[4]/div/button");
//     $this->waitForPageToLoad("");
//     $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
//     $this->waitForPageToLoad("30000");
//   }
}
