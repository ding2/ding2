<?php

require_once(dirname(__FILE__) . '/config.inc');

class CollectionView extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  /**
   * Test covers as anonymous.
   *
   * Check that certain elements should have an image tag,
   * whilst others do not.
   */
  public function testCollectionCoversAnonymous() {
    $this->open("/" . TARGET_URL_LANG);
    $this->waitForPageToLoad("30000");
    $this->open("ting/collection/870970-basis%3A27267912");
    sleep(10);
    $this->assertTrue($this->isElementPresent("css=.ting-collection-wrapper:nth-child(1) .ting-cover img"));
    $this->assertFalse($this->isElementPresent("css=.ting-collection-wrapper:nth-child(2) .ting-cover img"));
  }

  /**
   * Check covers as logged in user.
   *
   * @see testCollectionCoversAnonymous()
   */
  public function testCollectionCoversAuthenticated() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->open("ting/collection/870970-basis%3A27267912");
    sleep(10);
    $this->assertTrue($this->isElementPresent("css=.ting-collection-wrapper:nth-child(1) .ting-cover img"));
    $this->assertFalse($this->isElementPresent("css=.ting-collection-wrapper:nth-child(2) .ting-cover img"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Test the collection page as anonymous.
   *
   * Assume the page should contain some links to other material types.
   */
  public function testCollectionViewAnonymous() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "frank herbert klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div[2]"));
    $this->assertTrue($this->isElementPresent("link=Bog (8)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net) (1)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (bånd) (5)"));
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
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "frank herbert klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div[2]"));
    $this->assertTrue($this->isElementPresent("link=Bog (8)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net) (1)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (bånd) (5)"));
    $this->click("link=Bog (8)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Bog$/', $this->getLocation()));
    $this->click("link=Lydbog (net) (1)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(net\)$/', $this->getLocation()));
    $this->click("link=Lydbog (bånd) (5)");
    $this->assertTrue((bool) preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(b%C3%A5nd\)$/', $this->getLocation()));
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
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "frank herbert klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=div.ting-object"), '', true);
    $this->click("id=bookmark-870970-basis:05306809");
    sleep(4);
    $this->type("//form[@id='user-login']/div/div[1]/input", TARGET_URL_USER);
    $this->type("//form[@id='user-login']/div/div[2]/input", TARGET_URL_USER_PASS);
    $this->mouseDownAt("//form[@id='user-login']/div/div[3]/input");
    sleep(4);
    $msgs = array(
      "Added to bookmarks",
      "This item is in bookmarks already.",
    );
    $this->assertTrue(in_array($this->getText("css=div.ding-bookmark-message"), $msgs));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=bookmark-870970-basis:05306809");
    sleep(4);
    $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=reservation-870970-basis:05306809");
    sleep(4);
    $msgs = array(
      "\"Klit\" reserved and will be available for pickup at Hjørring.",
      "Error message \"You have already reserved \"Klit\".",
      "Error message \"Klit\" is not available for reservation.",
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[5]/div/button");
    $this->click("id=reservation-870970-basis:05306809");
    sleep(4);
    $msgs = array(
      "Error message \"You have already reserved \"Klit\".",
      "Error message \"Klit\" is not available for reservation.",
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[6]/div/button");
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
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "frank herbert klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=div.ting-object"), '', true);
    $this->click("id=bookmark-870970-basis:05306809");
    sleep(4);
    $msgs = array(
      "Added to bookmarks",
      "This item is in bookmarks already.",
    );
    $this->assertTrue(in_array($this->getText("css=div.ding-bookmark-message"), $msgs));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=bookmark-870970-basis:05306809");
    sleep(4);
    $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=reservation-870970-basis:05306809");
    sleep(4);
    $msgs = array(
      "\"Klit\" reserved and will be available for pickup at Hjørring.",
      "Error message \"You have already reserved \"Klit\".",
      "Error message \"Klit\" is not available for reservation."
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[4]/div/button");
    $this->click("id=reservation-870970-basis:05306809");
    $msgs = array(
      "Error message \"You have already reserved \"Klit\".",
      "Error message \"Klit\" is not available for reservation."
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[5]/div/button");
  }
}
