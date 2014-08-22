<?php
class ItemPage extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testAvailabilityAnonymous()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
    $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("link=Bog (1)"));
    $this->click("link=Bog (1)");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("link=Bog (1)"));
  }

  public function testAvailabilityLoggedIn()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
    $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("link=Bog (1)"));
    $this->click("link=Bog (1)");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->assertTrue($this->isElementPresent("id=availability-870970-basis50676927"));
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("link=Bog (1)"));
  }
}
?>