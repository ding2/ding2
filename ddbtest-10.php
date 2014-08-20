<?php
class SearchResultFacets extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testSearchResultFacetsAnon()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "Dune");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dúné', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-type']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-creator']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-subject']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-language']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-category']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-date']/div/div[2]/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2008', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-acsource']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2008', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
  }

  public function testSearchResultFacetsLogged()
  {
    $this->open("/");
    $this->click("link=Login");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Dune");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('Dúné', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-type']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-creator']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-subject']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("//div[@id='edit-language']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-category']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-date']/div/div[2]/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2008', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
    $this->click("//div[@id='edit-acsource']/div/div/label/a");
    $this->waitForPageToLoad("30000");
    $this->assertContains('dune', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('bog', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('frank herbert', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('science fiction', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertContains('2008', $this->getText("css=li.list-item.search-result"), '', true);
    $this->assertGreaterThan(0, $this->getCssCount("ul.list"));
  }
}
?>
