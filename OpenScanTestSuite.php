<?php

require_once(dirname(__FILE__) . '/config.inc');

class OpenScan extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  public function testAutosuggestionAnonymous() {
    $this->open("/en");
    $this->type("id=edit-search-block-form--2", "star wa");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    sleep(3);
    $this->assertEquals("star wars", $this->getText("//*[@id=\"autocomplete\"]/ul/li[1]"));
    $this->mouseDown("//div[@id='autocomplete']/ul/li/div");
    try {
      $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    }
    catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->type("id=edit-search-block-form--2", "star wa");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    sleep(3);
    $this->keyDown("id=edit-search-block-form--2", "\\40");
    $this->assertEquals("selected", $this->getAttribute("//*[@id=\"autocomplete\"]/ul/li[1]@class"));
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    try {
      $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    }
    catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->type("id=edit-search-block-form--2", "star wa");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->click("css=#ding-facetbrowser-form > div > #facet-type > #expand_more");
    try {
      $this->assertEquals("star wa", $this->getValue("id=edit-search-block-form--2"));
    }
    catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
  }

  public function testAutosuggestionLoggedIn() {
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->type("id=edit-search-block-form--2", "star wa");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    sleep(3);
    $this->assertEquals("star wars", $this->getText("//*[@id=\"autocomplete\"]/ul/li[1]"));
    $this->mouseDown("//div[@id='autocomplete']/ul/li/div");
    try {
      $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    }
    catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->type("id=edit-search-block-form--2", "star wa");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    sleep(3);
    $this->keyDown("id=edit-search-block-form--2", "\\40");
    $this->assertEquals("selected", $this->getAttribute("//*[@id=\"autocomplete\"]/ul/li[1]@class"));
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    try {
      $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    }
    catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->type("id=edit-search-block-form--2", "star wa");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->click("css=#ding-facetbrowser-form > div > #facet-type > #expand_more");
    try {
      $this->assertEquals("star wa", $this->getValue("id=edit-search-block-form--2"));
    }
    catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  public function testSpecialCharactersAnonymous() {
    $this->open("/en");
    $this->type("id=edit-search-block-form--2", "Afskrivning på maskiner");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Afskrivning på maskiner", $this->getValue("id=edit-search-block-form--2"));
    $this->assertEquals("Afskrivning på maskiner", $this->getText("link=Afskrivning på maskiner"));
    $this->click("css=img[alt=\"Home\"]");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "gæ");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    for ($second = 0;; $second++) {
      if ($second >= 60)
        $this->fail("timeout");
      try {
        if ($this->isElementPresent("//*[@id=\"autocomplete\"]/ul/li"))
          break;
      }
      catch (Exception $e) {

      }
      sleep(1);
    }

    $this->assertEquals("gæk, gæk, gæk", $this->getText("//*[@id=\"autocomplete\"]/ul/li[2]/div"));
  }

  public function testSpecialCharactersLoggedIn() {
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Afskrivning på maskiner");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Afskrivning på maskiner", $this->getValue("id=edit-search-block-form--2"));
    $this->assertEquals("Afskrivning på maskiner", $this->getText("link=Afskrivning på maskiner"));
    $this->click("css=img[alt=\"Home\"]");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "gæ");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    for ($second = 0;; $second++) {
      if ($second >= 60)
        $this->fail("timeout");
      try {
        if ($this->isElementPresent("//*[@id=\"autocomplete\"]/ul/li"))
          break;
      }
      catch (Exception $e) {

      }
      sleep(1);
    }

    $this->assertEquals("gæk, gæk, gæk", $this->getText("//*[@id=\"autocomplete\"]/ul/li[2]/div"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  public function testSubmitAnonymous() {
    $this->open("/en");
    $this->type("id=edit-search-block-form--2", "harry potter");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=li.list-item.search-result"));
    $this->type("id=edit-search-block-form--2", "");
    $this->click("id=edit-submit--3");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=div.messages.error"));
  }

  public function testSubmitLoggedIn() {
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->type("id=edit-search-block-form--2", "inferno dan brown");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Inferno"));
    $this->type("id=edit-search-block-form--2", "");
    $this->click("id=edit-submit--3");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=div.messages.error"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
