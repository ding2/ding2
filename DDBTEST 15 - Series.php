<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testSeries()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "islandica eggert olafsson");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->click("link=Islandica");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
  }
}
?>