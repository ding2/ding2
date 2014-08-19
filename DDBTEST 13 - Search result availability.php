<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testAvailabilityMarkers()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Dune");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Dúné"));
    $this->assertTrue($this->isElementPresent("css=p.js-pending"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis28017499-bog"));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("xpath=(//a[contains(text(),'Dune')])[2]"));
    $this->assertTrue($this->isElementPresent("css=p.js-online"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net)"));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Klit"));
    $this->assertTrue($this->isElementPresent("css=p.js-pending"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis28443471-bog"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Dune");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Dúné"));
    $this->assertTrue($this->isElementPresent("css=p.js-pending"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis28017499-bog"));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("xpath=(//a[contains(text(),'Dune')])[2]"));
    $this->assertTrue($this->isElementPresent("css=p.js-online"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net)"));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Klit"));
    $this->assertTrue($this->isElementPresent("css=p.js-pending"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis28443471-bog"));
  }
}
?>
