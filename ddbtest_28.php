<?php
class ItemPage extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testDefaultCoversAnon()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=img[alt=\": Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo\"]"));
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
  }

  public function testDefaultCoversLoggedIn()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=img[alt=\": Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo\"]"));
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>