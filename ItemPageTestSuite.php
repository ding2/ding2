<?php

require_once(__DIR__ . '/autoload.php');
require_once(__DIR__ . '/bootstrap.php');

class ItemPage extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test covers for a certain item on item page as anonymous.
   */
  public function testItemPageAnonymous() {
    resetState($this->config->getLms());
    $this->open('/' . $this->config->getLocale());
    // Search for an item.
    $this->abstractedPage->userMakeSearch('dorthe nors');

    // Check the item title on search result page.
    $this->assertTrue($this->isElementPresent('link=Stormesteren : roman'));
    // Click on title. Goes to collection page.
    $this->click('link=Stormesteren : roman');
    $this->abstractedPage->waitForPage();

    // Check the item title on the collection page.
    $this->assertTrue($this->isElementPresent('link=Stormesteren : roman'));
    // Click on title. Goes to item page.
    $this->click('link=Stormesteren : roman');
    $this->abstractedPage->waitForPage();

    // Wait for the cover to show up.
    $is_present = $this->abstractedPage->waitForElement('css=.ting-cover-processed img', 5, FALSE);
    $this->assertTrue($is_present);

    // Test availability marker.
    $this->assertTrue($this->isElementPresent("css=#availability-870970-basis24908941"));

    // Test holdings table.
    // Open availability table.
    $this->assertTrue($this->isElementPresent("link=Holdings available on the shelf"));
    $this->click("link=Holdings available on the shelf");

    // Check copies information.
    //$this->assertTrue($this->isElementPresent("css=#holdings-870970-basis24908941 > p"));
    $this->abstractedPage->waitForElement('css=#holdings-870970-basis24908941 > p');
    $this->assertElementContainsText('css=#holdings-870970-basis24908941 > p', 'We have 1 copy. There are 0 users in queue to loan the material.');

    // Check specific row in the availability table.
    $this->abstractedPage->waitForElement('css=.availability-holdings-table td');
    $this->assertElementContainsText('css=.availability-holdings-table td', 'Hjørring > Voksensamling > > > Nors');

    // Test bookmarking & reserving.
    // Try to bookmark with logging in, if required.
    $this->abstractedPage->userBookmark('.action-button.bookmark-button:eq(0)');

    // Wait for the login popup, if any.
    $is_present = $this->abstractedPage->waitForElement('css=.ding-popup-content form#user-login', 5, FALSE);
    if ($is_present) {
      $this->abstractedPage->fillDingPopupLogin($this->config->getUser(), $this->config->getPass());
    }
    $this->abstractedPage->waitForElement('css=div.ding-bookmark-message');
    $msgs = array(
      'Added to bookmarks',
      'This item is in bookmarks already.',
    );
    $this->assertTrue(in_array($this->getText('css=div.ding-bookmark-message'), $msgs));
    // Since there are issues with selenium by clicking ding popup close button,
    // simply refresh the page.
    $this->abstractedPage->refresh();
    // Bookmark again. Here the use is already logged and the item should
    // exist in bookmarks.
    $this->abstractedPage->userBookmark('.action-button.bookmark-button:eq(0)');
    $this->abstractedPage->waitForElement('css=div.ding-bookmark-message');
    $this->assertEquals('This item is in bookmarks already.', $this->getText('css=div.ding-bookmark-message'));

    // Refresh and reserve same item.
    $this->abstractedPage->refresh();
    $this->abstractedPage->userReserve('.action-button.reserve-button:eq(0)');
    $this->abstractedPage->waitForElement('css=div.ding-popup-content .messages.status');
    $this->assertTrue($this->isElementPresent('css=div.ding-popup-content .messages.status'));

    // Refresh and try to reserve again, normally this should not be allowed.
    $this->abstractedPage->refresh();
    $this->abstractedPage->userReserve('.action-button.reserve-button:eq(0)');
    $this->abstractedPage->waitForElement('css=div.ding-popup-content .messages.error');
    $this->assertTrue($this->isElementPresent('css=div.ding-popup-content .messages.error'));
  }

  /**
   * Test covers for a certain item as logged in user.
   *
   * @see testDefaultCoversAnonymous()
   */
  public function testItemPageLoggedIn() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testItemPageAnonymous();
  }
}
