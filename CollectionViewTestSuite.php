<?php

require_once(__DIR__ . '/autoload.php');

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
    $this->open("/" . $this->config->getLocale() . '/ting/collection/870970-basis:27267912');
    $this->waitForPageToLoad("30000");
    // Implicitly wait 10 seconds, since covers come via ajax.
    // It's not possible to use a more elegant solution to wait.
    // Second assertion expects to a FALSE result, which in other implementation
    // will trigger a FALSE result instantly, which is not correct.
    // So have to be sure that the AJAX call has finished first, to know
    // that the actual cover element is not present.
    sleep(10);
    // The collection item page opened above is expected to have first
    // collection items contain cover images and the second one - no.
    $this->assertTrue($this->isElementPresent("css=.ting-collection-wrapper:nth-child(1) .ting-cover img"));
    $this->assertFalse($this->isElementPresent("css=.ting-collection-wrapper:nth-child(2) .ting-cover img"));
  }

  /**
   * Check covers as logged in user.
   *
   * @see testCollectionCoversAnonymous()
   */
  public function testCollectionCoversAuthenticated() {
    $this->open("/" . $this->config->getLocale());
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
    // Search for potential collection item.
    $this->abstractedPage->userMakeSearch('frank herbert klit');
    // Check the item title.
    $this->assertElementContainsText('css=li.list-item.search-result:first .group_ting_right_col_search .heading a', 'Klit');
    // Click on title.
    $this->click("css=li.list-item.search-result:first .group_ting_right_col_search .heading a");
    $this->waitForPageToLoad("30000");
    // If this is truly a collection item is should have certain
    // information about item types and the quantity of those.
    $this->assertTrue($this->isElementPresent("link=Bog (8)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net) (1)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (bånd) (5)"));
    // Test the anchor links.
    $this->click("link=Bog (8)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Bog$/', $this->getLocation()));
    $this->click("link=Lydbog (net) (1)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(net\)$/', $this->getLocation()));
    $this->click("link=Lydbog (bånd) (5)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(b%C3%A5nd\)$/', $this->getLocation()));
  }

  /**
   * Test the collections page as logged in user.
   *
   * @see testCollectionViewAnonymous()
   */
  public function testCollectionViewLoggedIn() {
    $this->open("/" . $this->config->getLocale());
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testCollectionViewAnonymous();
  }

//   /**
//    * Test the ability to bookmark/reserve as anonymous
//    * on collection page.
//    *
//    * Anonymous in this context means that user authenticates in a
//    * popup, when clicking bookmark/reserve as anonymous.
//    *
//    * Assume that the test might be run several times for same user,
//    * so different responses are checked as valid.
//    */
//   public function testCollectionViewActionsAnonymous() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-search-block-form--2", "frank herbert klit");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
//     $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
//     $this->waitForPageToLoad("30000");
//     $this->assertContains('klit', $this->getText("css=div.ting-object"), '', true);
//     $this->click("id=bookmark-870970-basis:05306809");
//     sleep(4);
//     $this->type("//form[@id='user-login']/div/div[1]/input", TARGET_URL_USER);
//     $this->type("//form[@id='user-login']/div/div[2]/input", TARGET_URL_USER_PASS);
//     $this->mouseDownAt("//form[@id='user-login']/div/div[3]/input");
//     sleep(4);
//     $msgs = array(
//       "Added to bookmarks",
//       "This item is in bookmarks already.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.ding-bookmark-message"), $msgs));
//     $this->mouseDownAt("//body/div[4]");
//     $this->click("id=bookmark-870970-basis:05306809");
//     sleep(4);
//     $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
//     $this->mouseDownAt("//body/div[4]");
//     $this->click("id=reservation-870970-basis:05306809");
//     sleep(4);
//     $msgs = array(
//       "\"Klit\" reserved and will be available for pickup at Hjørring.",
//       "Error message \"You have already reserved \"Klit\".",
//       "Error message \"Klit\" is not available for reservation.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[5]/div/button");
//     $this->click("id=reservation-870970-basis:05306809");
//     sleep(4);
//     $msgs = array(
//       "Error message \"You have already reserved \"Klit\".",
//       "Error message \"Klit\" is not available for reservation.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[6]/div/button");
//   }

//   /**
//    * Test the ability to reserve/bookmark.
//    *
//    * The use is logged in, goes to collection page and tries to
//    * reserve/bookmark.
//    *
//    * @see testCollectionViewActionsAnonymous()
//    */
//   public function testCollectionViewActionsLoggedIn() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-name", TARGET_URL_USER);
//     $this->type("id=edit-pass", TARGET_URL_USER_PASS);
//     $this->click("id=edit-submit--2");
//     $this->waitForPageToLoad("30000");
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-search-block-form--2", "frank herbert klit");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
//     $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
//     $this->waitForPageToLoad("30000");
//     $this->assertContains('klit', $this->getText("css=div.ting-object"), '', true);
//     $this->click("id=bookmark-870970-basis:05306809");
//     sleep(4);
//     $msgs = array(
//       "Added to bookmarks",
//       "This item is in bookmarks already.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.ding-bookmark-message"), $msgs));
//     $this->mouseDownAt("//body/div[4]");
//     $this->click("id=bookmark-870970-basis:05306809");
//     sleep(4);
//     $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
//     $this->mouseDownAt("//body/div[4]");
//     $this->click("id=reservation-870970-basis:05306809");
//     sleep(4);
//     $msgs = array(
//       "\"Klit\" reserved and will be available for pickup at Hjørring.",
//       "Error message \"You have already reserved \"Klit\".",
//       "Error message \"Klit\" is not available for reservation."
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[4]/div/button");
//     $this->click("id=reservation-870970-basis:05306809");
//     $msgs = array(
//       "Error message \"You have already reserved \"Klit\".",
//       "Error message \"Klit\" is not available for reservation."
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[5]/div/button");
//   }
}
