<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testSearchBoxAnonymous()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "Dune");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Dúné"));
    $this->assertTrue($this->isElementPresent("link=Gregers Tycho"));
    $this->click("link=Gregers Tycho");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Dúné"));
    $this->assertTrue($this->isElementPresent("link=Gregers Tycho"));
    $this->type("id=edit-search-block-form--2", "star wars");
    $this->click("id=edit-submit--3");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Star Wars : The Essential Guide to the Force"));
    $this->assertTrue($this->isElementPresent("link=Star Wars (Random House Paperback)"));
    $this->click("link=Star Wars (Random House Paperback)");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Star Wars : The Essential Guide to the Force"));
    $this->assertTrue($this->isElementPresent("link=Star Wars (Random House Paperback)"));
  }

  public function testSearchBoxLoggedIn()
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
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Dúné"));
    $this->assertTrue($this->isElementPresent("link=Gregers Tycho"));
    $this->click("link=Gregers Tycho");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Dúné"));
    $this->assertTrue($this->isElementPresent("link=Gregers Tycho"));
    $this->type("id=edit-search-block-form--2", "star wars");
    $this->click("id=edit-submit--3");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Star Wars : The Essential Guide to the Force"));
    $this->assertTrue($this->isElementPresent("link=Star Wars (Random House Paperback)"));
    $this->click("link=Star Wars (Random House Paperback)");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Star Wars : The Essential Guide to the Force"));
    $this->assertTrue($this->isElementPresent("link=Star Wars (Random House Paperback)"));
  }
}
?>
