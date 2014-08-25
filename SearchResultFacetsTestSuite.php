<?php

require_once(dirname(__FILE__) . '/config.inc');

class SearchResultFacets extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  public function testFacetBrowserAnonymous() {
    $this->open("/en");
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

  public function testFacetBrowserLoggedIn() {
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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
  }

  public function testSearchResultFacetsAnonymous() {
    $this->open("/en");
    $this->type("id=edit-search-block-form--2", "dune messiah");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-type']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-creator']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-subject']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-language']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-category']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-date']/div/div[2]/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2002', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-acsource']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2002', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
  }

  public function testSearchResultFacetsLoggedIn() {
    $this->open("/en");
    $this->click("link=Login");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "dune messiah");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-type']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-creator']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-subject']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-language']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-category']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-date']/div/div[2]/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2002', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-acsource']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune messiah', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2002', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
  }
}
