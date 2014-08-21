<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testCovers()
  {
    $this->open("/");
    $this->open("/search/ting/harry potter?page=2");
    $this->assertFalse($this->isElementPresent("css=.search-results .search-result:nth-child(1) img"));
    $this->assertTrue($this->isElementPresent("css=.search-results .search-result:nth-child(5) img"));
  }

  public function testCovertAuth()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->open("/search/ting/harry potter?page=2");
    $this->assertFalse($this->isElementPresent("css=.search-results .search-result:nth-child(1) img"));
    $this->assertTrue($this->isElementPresent("css=.search-results .search-result:nth-child(5) img"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>
