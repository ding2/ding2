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
    $this->type("id=edit-search-block-form--2", "dune");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=p.js-pending"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis28017499-bog"));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=p.js-online"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net)"));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Klit"));
    $this->assertTrue($this->isElementPresent("link=Frank Herbert"));
    $this->assertTrue($this->isElementPresent("css=p.js-pending"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis28443471-bog"));
  }
}
?>