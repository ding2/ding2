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
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "islandica eggert olafsson");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Eggert Ólafsson"));
    $this->assertTrue($this->isElementPresent("link=Islandica"));
    $this->click("link=Islandica");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Eggert Olafsson : A biographical sketch"));
    $this->assertTrue($this->isElementPresent("link=Islandica"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "islandica eggert olafsson");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Eggert Ólafsson"));
    $this->assertTrue($this->isElementPresent("link=Islandica"));
    $this->click("link=Islandica");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Eggert Olafsson : A biographical sketch"));
    $this->assertTrue($this->isElementPresent("link=Islandica"));
  }
}
?>
