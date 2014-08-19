<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testFacetBrowser()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "45154211 OR 59999397");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Cd (musik):", $this->getText("css=span.search-result--heading-type"));
    $this->assertEquals("Trchnicolour", $this->getText("link=Trchnicolour"));
    $this->assertEquals("Teateropførelse:", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/span"));
    $this->verifyText("link=Inferno", "Inferno");
    $this->assertEquals("Musiktrack (net):", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/span"));
    $this->verifyText("link=Kakadu", "Kakadu");
    $this->click("id=edit-type-cd-musik");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Cd (musik):", $this->getText("css=span.search-result--heading-type"));
    $this->verifyText("link=Trchnicolour", "Trchnicolour");
    $this->click("id=edit-type-cd-musik");
    $this->waitForPageToLoad("30000");
    $this->click("id=edit-type-musiktrack-net");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Musiktrack (net):", $this->getText("css=span.search-result--heading-type"));
    $this->verifyText("link=Kakadu", "Kakadu");
    $this->click("id=edit-type-musiktrack-net");
    $this->waitForPageToLoad("30000");
    $this->click("id=edit-type-teateropfrelse");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Teateropførelse:", $this->getText("css=span.search-result--heading-type"));
    $this->verifyText("link=Inferno", "Inferno");
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "45154211 OR 59999397");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Cd (musik):", $this->getText("css=span.search-result--heading-type"));
    $this->assertEquals("Trchnicolour", $this->getText("link=Trchnicolour"));
    $this->assertEquals("Teateropførelse:", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[2]/div/div/div[2]/div/h2/span"));
    $this->verifyText("link=Inferno", "Inferno");
    $this->assertEquals("Musiktrack (net):", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[7]/div/div/ul/li[3]/div/div/div[2]/div/h2/span"));
    $this->verifyText("link=Kakadu", "Kakadu");
    $this->click("id=edit-type-cd-musik");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Cd (musik):", $this->getText("css=span.search-result--heading-type"));
    $this->verifyText("link=Trchnicolour", "Trchnicolour");
    $this->click("id=edit-type-cd-musik");
    $this->waitForPageToLoad("30000");
    $this->click("id=edit-type-musiktrack-net");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Musiktrack (net):", $this->getText("css=span.search-result--heading-type"));
    $this->verifyText("link=Kakadu", "Kakadu");
    $this->click("id=edit-type-musiktrack-net");
    $this->waitForPageToLoad("30000");
    $this->click("id=edit-type-teateropfrelse");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Teateropførelse:", $this->getText("css=span.search-result--heading-type"));
    $this->verifyText("link=Inferno", "Inferno");
  }
}
?>
