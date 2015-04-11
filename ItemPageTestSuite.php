<?php

require_once(__DIR__ . '/autoload.php');

class ItemPage extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstraction;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Test covers for a certain item on item page as anonymous.
   *
   * sleep() is used because covers are fetched via AJAX.
   */
  public function testDefaultCoversAnonymous() {
    $this->open('/' . $this->config->getLocale());
    // Searc for an item.
    $this->abstractedPage->userMakeSearch('Rom : i Vilhelm Bergsøes');
    $this->assertElementContainsText('css=li.list-item.search-result:first .group_ting_right_col_search .heading a', 'Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo');
    // Go to this item landing page.
    $this->click('css=li.list-item.search-result:first .group_ting_right_col_search .heading a');
    $this->abstractedPage->waitForPage();

    // Wait for the cover to show up.
    $is_present = $this->abstractedPage->waitForElement('css=.ting-cover-processed img', 10, FALSE);
    $this->assertTrue($is_present);
  }

  /**
   * Test covers for a certain item as logged in user.
   *
   * @see testDefaultCoversAnonymous()
   */
  public function testDefaultCoversLoggedIn() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());
    $this->testDefaultCoversAnonymous();
  }

//   /**
//    * Test availability markers as anonymous.
//    */
//   public function testAvailabilityAnonymous() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
//     $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
//     $this->assertTrue($this->isElementPresent("link=Bog (1)"));
//     $this->click("link=Bog (1)");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
//     $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
//     $this->assertTrue($this->isElementPresent("link=Bog (1)"));
//   }

//   /**
//    * Test availability markers as logged in user.
//    *
//    * @see testAvailabilityAnonymous()
//    */
//   public function testAvailabilityLoggedIn() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-name", TARGET_URL_USER);
//     $this->type("id=edit-pass", TARGET_URL_USER_PASS);
//     $this->click("id=edit-submit--2");
//     $this->waitForPageToLoad("30000");
//     $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
//     $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
//     $this->assertTrue($this->isElementPresent("link=Bog (1)"));
//     $this->click("link=Bog (1)");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
//     $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
//     $this->assertTrue($this->isElementPresent("link=Bog (1)"));
//   }

//   /**
//    * Test the existence of holdings table for a certain item as anonymous.
//    *
//    * Assume a location to be present.
//    */
//   public function testHoldingsAnonymous() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("", $this->getText("id=edit-search-block-form--2"));
//     $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
//     $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
//     $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div[2]/h2"));
//     $this->assertTrue($this->isElementPresent("link=Holdings available on the shelf"));
//     $this->click("link=Holdings available on the shelf");
//     $this->assertTrue($this->isElementPresent("css=#holdings-870970-basis50676927 > p"));
//     $this->assertTrue($this->isElementPresent("css=th"));
//     $this->assertTrue($this->isElementPresent("//div[@id='holdings-870970-basis50676927']/table/thead/tr/th[2]"));
//     $this->assertTrue($this->isElementPresent("//div[@id='holdings-870970-basis50676927']/table/thead/tr/th[3]"));
//     $this->assertEquals("Hirtshals > Voksensamling > > 47.57 Rom > Rom", $this->getText("css=td"));
//   }

//   /**
//    * Test the existence of holdings table as logged in user.
//    *
//    * @see testHoldingsAnonymous()
//    */
//   public function testHoldingsLoggedIn() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-name", TARGET_URL_USER);
//     $this->type("id=edit-pass", TARGET_URL_USER_PASS);
//     $this->click("id=edit-submit--2");
//     $this->waitForPageToLoad("30000");
//     $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertEquals("", $this->getText("id=edit-search-block-form--2"));
//     $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
//     $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
//     $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
//     $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div[2]/h2"));
//     $this->assertTrue($this->isElementPresent("link=Holdings available on the shelf"));
//     $this->click("link=Holdings available on the shelf");
//     $this->assertTrue($this->isElementPresent("css=#holdings-870970-basis50676927 > p"));
//     $this->assertTrue($this->isElementPresent("css=th"));
//     $this->assertTrue($this->isElementPresent("//div[@id='holdings-870970-basis50676927']/table/thead/tr/th[2]"));
//     $this->assertTrue($this->isElementPresent("//div[@id='holdings-870970-basis50676927']/table/thead/tr/th[3]"));
//     $this->assertEquals("Hirtshals > Voksensamling > > 47.57 Rom > Rom", $this->getText("css=td"));
//   }

//   /**
//    * Test the ability to bookmark/reserve as anonymous on item page.
//    *
//    * Anonymous in current context would mean that user authenticates
//    * in a popup after pressing bookmark/reserve.
//    *
//    * Assume that the test might be run several times for same user,
//    * so different responses are checked as valid.
//    */
//   public function testItemPageActionsAnonymous() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertContains('Rom : i Vilhelm Bergsøes', $this->getText("css=li.list-item.search-result"), '', true);
//     $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("id=bookmark-870970-basis:50676927"));
//     $this->assertTrue($this->isElementPresent("id=reservation-870970-basis:50676927"));
//     $this->click("id=bookmark-870970-basis:50676927");
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
//     $this->click("id=bookmark-870970-basis:50676927");
//     sleep(4);
//     $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
//     $this->mouseDownAt("//body/div[4]");
//     $this->click("id=reservation-870970-basis:50676927");
//     sleep(4);
//     $msgs = array(
//       "\"Rom\" reserved and will be available for pickup at Hjørring.",
//       "Error message \"You have already reserved \"Rom\".",
//       "Error message \"Rom\" is not available for reservation.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[5]/div/button");
//     $this->click("id=reservation-870970-basis:50676927");
//     sleep(4);
//     $msgs = array(
//       "Error message \"You have already reserved \"Rom\".",
//       "Error message \"Rom\" is not available for reservation.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[6]/div/button");
//   }

//   /**
//    * Test the ability to bookmark/reserve as logged in user being on item page.
//    *
//    * @see testItemPageActionsAnonymous()
//    */
//   public function testItemPageActionsLoggedIn() {
//     $this->open("/" . TARGET_URL_LANG);
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-name", TARGET_URL_USER);
//     $this->type("id=edit-pass", TARGET_URL_USER_PASS);
//     $this->click("id=edit-submit--2");
//     $this->waitForPageToLoad("30000");
//     $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
//     $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
//     $this->click("id=edit-submit");
//     $this->waitForPageToLoad("30000");
//     $this->assertContains('Rom : i Vilhelm Bergsøes', $this->getText("css=li.list-item.search-result"), '', true);
//     $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
//     $this->waitForPageToLoad("30000");
//     $this->assertTrue($this->isElementPresent("id=bookmark-870970-basis:50676927"));
//     $this->assertTrue($this->isElementPresent("id=reservation-870970-basis:50676927"));
//     $this->click("id=bookmark-870970-basis:50676927");
//     sleep(4);
//     $msgs = array(
//       "Added to bookmarks",
//       "This item is in bookmarks already.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.ding-bookmark-message"), $msgs));
//     $this->mouseDownAt("//body/div[4]");
//     $this->click("id=bookmark-870970-basis:50676927");
//     sleep(4);
//     $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
//     $this->mouseDownAt("//body/div[4]");
//     $this->click("id=reservation-870970-basis:50676927");
//     sleep(4);
//     $msgs = array(
//       "\"Rom\" reserved and will be available for pickup at Hjørring.",
//       "Error message \"You have already reserved \"Rom\".",
//       "Error message \"Rom\" is not available for reservation.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[4]/div/button");
//     $this->click("id=reservation-870970-basis:50676927");
//     sleep(4);
//     $msgs = array(
//       "Error message \"You have already reserved \"Rom\".",
//       "Error message \"Rom\" is not available for reservation.",
//     );
//     $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
//     $this->mouseDownAt("//div[5]/div/button");
//   }
}
