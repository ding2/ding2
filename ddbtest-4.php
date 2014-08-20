<?php
class OpenScan extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testAutosuggestionAnon()
  {
    $this->open("/");
    $this->sendKeys("id=edit-search-block-form--2", "star wa");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->waitForPopUp("id=autocomplete", "2000");
    $this->assertEquals("star wars", $this->getText("//*[@id=\"autocomplete\"]/ul/li[1]"));
    $this->mouseDown("//div[@id='autocomplete']/ul/li/div");
    try {
        $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->sendKeys("id=edit-search-block-form--2", "star wa");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->waitForPopUp("id=autocomplete", "2000");
    $this->keyDown("id=edit-search-block-form--2", "\\40");
    $this->assertEquals("selected", $this->getAttribute("//*[@id=\"autocomplete\"]/ul/li[1]@class"));
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    try {
        $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->sendKeys("id=edit-search-block-form--2", "star wa");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->click("css=#ding-facetbrowser-form > div > #facet-type > #expand_more");
    try {
        $this->assertEquals("star wa", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
  }

  public function testAutosuggestionLoggedIn()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->sendKeys("id=edit-search-block-form--2", "star wa");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->waitForPopUp("id=autocomplete", "2000");
    $this->assertEquals("star wars", $this->getText("//*[@id=\"autocomplete\"]/ul/li[1]"));
    $this->mouseDown("//div[@id='autocomplete']/ul/li/div");
    try {
        $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->sendKeys("id=edit-search-block-form--2", "star wa");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->waitForPopUp("id=autocomplete", "2000");
    $this->keyDown("id=edit-search-block-form--2", "\\40");
    $this->assertEquals("selected", $this->getAttribute("//*[@id=\"autocomplete\"]/ul/li[1]@class"));
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    try {
        $this->assertEquals("star wars", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
    $this->type("id=edit-search-block-form--2", "");
    $this->sendKeys("id=edit-search-block-form--2", "star wa");
    $this->assertTrue($this->isElementPresent("id=autocomplete"));
    $this->click("css=#ding-facetbrowser-form > div > #facet-type > #expand_more");
    try {
        $this->assertEquals("star wa", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>
