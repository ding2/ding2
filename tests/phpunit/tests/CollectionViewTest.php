<?php

require_once 'Ding2TestBase.php';

class CollectionViewTest extends Ding2TestBase {
  protected function setUp() {
    parent::setUp();
    resetState($this->config->getLms());
  }

  /**
   * Test covers as anonymous.
   *
   * Check that certain elements should have an image tag,
   * when others do not.
   */
  public function testCollectionViewAnonymous() {
    resetState($this->config->getLms());
    $this->open($this->config->getUrl() . $this->config->getLocale() . '/ting/collection/870970-basis%3A50761290');
    $this->abstractedPage->waitForPage();

    // Assume we are on collection page and there is a link to item page.
    $this->assertTrue($this->isElementPresent('link=Den islandske hest'));

    /**
     * PJO outcommented test for covers - there are several problems here:
     *
     * First ting_covers_addi is not enabled by default - should it be ??
     * Second the oss service moreinfo doesn't seem to work as expected
     */

    // Implicitly wait 10 seconds, since covers come via ajax.
    // It's not possible to use a more elegant solution to wait.
    // Second assertion expects to a FALSE result, which in other implementation
    // will trigger a FALSE result instantly, which is not correct.
    // So have to be sure that the AJAX call has finished first, to know
    // that the actual cover element is not present.
    //sleep(5);
    // The collection item page opened above is expected to have first
    // collection items contain cover images and the second one - no.
    //$this->assertElementPresent('css=.pane-ting-collection .view-mode-full .ting-collection-wrapper:eq(0) .ting-cover img');
    //$this->assertElementNotPresent('css=.pane-ting-collection .view-mode-full .ting-collection-wrapper:eq(1) .ting-cover img');

    // Try to bookmark with logging in, if required.
    /* Bookmarks require that 'perform bookmark' permissions is set.
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
    sleep(5);
    */

    /**
     * Pjo outcommented reserve test - there are no reservable items in the oss.searchservice
     * there are only ebog, lydbog (net), film (net), musik (net)
     */
    //$this->abstractedPage->userReserve('.action-button.reserve-button:eq(1)');
    //sleep(5);
    //$element = $this->isElementPresent('css=div.ding-popup-content .messages.status');
    //if(($element)==FALSE){
    //  $this->assertTrue($this->isElementPresent('css=div.ding-popup-content .messages.error'));
    //}
    //else {
    //  $this->assertTrue($this->isElementPresent('css=div.ding-popup-content .messages.status'));
    // }

    // Test if this is a collection page.
    // If this is truly a collection item is should have certain
    // information about item types and the quantity of those.
    $this->abstractedPage->refresh();
    $this->assertElementPresent('link=Bog (1)');
    $this->assertElementPresent('link=Ebog (1)');
    // Test the anchor links.

    /**
     * PJO outcommented these . Couldn't find any collection with more than one specific materialtype
     */
    //$this->click('link=Ebog (1)');
    //sleep(5);
    //$this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A51043138#Bog$/', $this->getLocation()));
    //$this->click('link=Ebog (1)');
    //$this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A51043138#Ebog$/', $this->getLocation()));
  }

  /*
   * Check covers as logged in user.
   *
   * @see testCollectionCoversAnonymous()
   */
  public function testCollectionViewAuthenticated() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    /** va */
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testCollectionViewAnonymous();
  }

}
