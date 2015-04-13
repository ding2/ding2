<?php

require_once(__DIR__ . '/autoload.php');
require_once(__DIR__ . '/bootstrap.php');

class CollectionView extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstraction;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test covers as anonymous.
   *
   * Check that certain elements should have an image tag,
   * when others do not.
   */
  public function testCollectionCoversAnonymous() {
    $this->open("/" . $this->config->getLocale() . '/ting/collection/870970-basis:24908941');
    $this->abstractedPage->waitForPage();
    // Implicitly wait 10 seconds, since covers come via ajax.
    // It's not possible to use a more elegant solution to wait.
    // Second assertion expects to a FALSE result, which in other implementation
    // will trigger a FALSE result instantly, which is not correct.
    // So have to be sure that the AJAX call has finished first, to know
    // that the actual cover element is not present.
    sleep(5);
    // The collection item page opened above is expected to have first
    // collection items contain cover images and the second one - no.
    $this->assertTrue($this->isElementPresent("css=.pane-ting-collection .view-mode-full .ting-collection-wrapper:nth-child(1) .ting-cover img"));
    $this->assertFalse($this->isElementPresent("css=.pane-ting-collection .view-mode-full .ting-collection-wrapper:nth-child(2) .ting-cover img"));
  }

  /**
   * Check covers as logged in user.
   *
   * @see testCollectionCoversAnonymous()
   */
  public function testCollectionCoversAuthenticated() {
    $this->open("/" . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testCollectionCoversAnonymous();
  }

  /**
   * Test the collection page as anonymous.
   *
   * Assume the page should contain some links to other material types.
   */
  public function testCollectionViewAnonymous() {
    $this->open("/" . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    // Search for potential collection item.
    $this->abstractedPage->userMakeSearch('dorthe nors');
    // Check the item title.
    $this->assertTrue($this->isElementPresent("link=Stormesteren : roman"));
    // Click on title.
    $this->click("link=Stormesteren : roman");
    $this->abstractedPage->waitForPage();
    // If this is truly a collection item is should have certain
    // information about item types and the quantity of those.
    $this->assertTrue($this->isElementPresent("link=Bog (1)"));
    $this->assertTrue($this->isElementPresent("link=Ebog (1)"));
    // Test the anchor links.
    $this->click("link=Bog (1)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A24908941#Bog$/', $this->getLocation()));
    $this->click("link=Ebog (1)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A24908941#Ebog$/', $this->getLocation()));
  }

  /**
   * Test the collections page as logged in user.
   *
   * @see testCollectionViewAnonymous()
   */
  public function testCollectionViewLoggedIn() {
    $this->open("/" . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testCollectionViewAnonymous();
  }

  /**
   * Test the ability to bookmark/reserve as anonymous
   * on collection page.
   *
   * Anonymous in this context means that user authenticates in a
   * popup, when clicking bookmark/reserve as anonymous.
   *
   * Assume that the test might be run several times for same user,
   * so different responses are checked as valid.
   */
  public function testCollectionViewActionsAnonymous() {
    resetState();
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    // Search for potential collection item.
    $this->abstractedPage->userMakeSearch('dorthe nors');
    // Check the item title.
    $this->assertTrue($this->isElementPresent("link=Stormesteren : roman"));
    // Click on title.
    $this->click("link=Stormesteren : roman");
    $this->abstractedPage->waitForPage();
    // Assume we are on collection page and there is a link to item page.
    $this->assertTrue($this->isElementPresent("link=Stormesteren : roman"));
    // Try to bookmark with logging in, if required.
    $this->abstractedPage->userBookmark('870970-basis:24908941');
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
    $this->abstractedPage->userBookmark('870970-basis:24908941');
    $this->abstractedPage->waitForElement('css=div.ding-bookmark-message');
    $this->assertEquals('This item is in bookmarks already.', $this->getText('css=div.ding-bookmark-message'));

    // Refresh and reserve same item.
    $this->abstractedPage->refresh();
    $this->abstractedPage->userReserve('870970-basis:24908941');
    $this->abstractedPage->waitForElement('css=div.ding-popup-content .messages.status');
    $this->assertTrue($this->isElementPresent('css=div.ding-popup-content .messages.status'));

    // Refresh and try to reserve again, normally this should not be allowed.
    $this->abstractedPage->refresh();
    $this->abstractedPage->userReserve('870970-basis:24908941');
    $this->abstractedPage->waitForElement('css=div.ding-popup-content .messages.error');
    $this->assertTrue($this->isElementPresent('css=div.ding-popup-content .messages.error'));
  }

  /**
   * Test the ability to reserve/bookmark.
   *
   * The use is logged in, goes to collection page and tries to
   * reserve/bookmark.
   *
   * @see testCollectionViewActionsAnonymous()
   */
  public function testCollectionViewActionsLoggedIn() {
    resetState();
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testCollectionViewActionsAnonymous();
  }
}
