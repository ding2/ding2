<?php

require_once(dirname(__FILE__) . '/config.inc');

class ItemPageRelations extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  public function testOtherMaterialsAnonymous() {
    $this->open("/" . TARGET_URL_LANG);
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->assertTrue($this->isElementPresent("//div[@id='dbcaddi:hasReview']/div"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[1]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[1]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[2]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[2]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]/div"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[2]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[2]/div/ul/li/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[1]"));
    $this->assertEquals("Bog (1)", $this->getText("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[1]/div/ul/li/a"));
    $this->click("link=Litteratursiden.dk online, 2013-10-15");
    sleep(3);
    $this->selectWindow("Rom. I Vilhelm Bergsøes fodspor fra Piazza del Popolo af Ellen Agerskov og Flemming Larsen. | Litteratursiden");
    $this->assertEquals("Rom. I Vilhelm Bergsøes fodspor fra Piazza del Popolo af Ellen Agerskov og Flemming Larsen.", $this->getText("css=h1.page-title"));
    $this->close();
    $this->selectWindow("null");
    $this->click("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]/a");
    sleep(3);
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div[1]/div/div/div/div/div/div/div/div/div/div/h1"));
    $this->assertEquals("Lektørudtalelse", $this->getText("//div[@id='page']/div[1]/div/div/div/div/div/div/div/div/div/div/h1"));
    $this->open("/ting/object/870970-basis%3A50676927");
    $this->click("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[2]/div/ul/li/a");
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A50676927#dbcaddi:hasReview$/', $this->getLocation()));
  }

  public function testOtherMaterialsLoggedIn() {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo", $this->getText("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo"));
    $this->assertTrue($this->isElementPresent("//div[@id='dbcaddi:hasReview']/div"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[1]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[1]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[2]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[2]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]/div"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[2]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[2]/div/ul/li/a"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[1]"));
    $this->assertEquals("Bog (1)", $this->getText("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[1]/div/ul/li/a"));
    $this->click("link=Litteratursiden.dk online, 2013-10-15");
    sleep(3);
    $this->selectWindow("Rom. I Vilhelm Bergsøes fodspor fra Piazza del Popolo af Ellen Agerskov og Flemming Larsen. | Litteratursiden");
    $this->assertEquals("Rom. I Vilhelm Bergsøes fodspor fra Piazza del Popolo af Ellen Agerskov og Flemming Larsen.", $this->getText("css=h1.page-title"));
    $this->close();
    $this->selectWindow("null");
    $this->click("//*[@id=\"dbcaddi:hasReview\"]/div/div[3]/a");
    sleep(3);
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div[1]/div/div/div/div/div/div/div/div/div/div/h1"));
    $this->assertEquals("Lektørudtalelse", $this->getText("//div[@id='page']/div[1]/div/div/div/div/div/div/div/div/div/div/h1"));
    $this->open("/ting/object/870970-basis%3A50676927");
    $this->click("//*[@id=\"page\"]/div[1]/div/div/div/div/div/aside/div[2]/div/ul/li/a");
    $this->assertTrue((bool) preg_match('/^[\s\S]*ting\/object\/870970-basis%3A50676927#dbcaddi:hasReview$/', $this->getLocation()));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
