<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testPagination()
  {
    $this->open("/");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "jazz");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("1", $this->getText("css=li.pager-current"));
    $this->assertTrue($this->isElementPresent("link=next ›"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=2@href")));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=next ›@href")));
    $this->click("link=2");
    $this->waitForPageToLoad("30000");
    $this->click("link=1");
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=‹ previous@href"));
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=1@href"));
    $this->assertEquals("2", $this->getText("css=li.pager-current"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=2$/',$this->getAttribute("link=3@href")));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=2$/',$this->getAttribute("link=next ›@href")));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=« first@href"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=‹ previous@href")));
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=1@href"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=2@href")));
    $this->assertEquals("3", $this->getText("css=li.pager-current"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=3$/',$this->getAttribute("link=4@href")));
    $this->click("link=next ›");
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=3$/',$this->getAttribute("link=next ›@href")));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=4$/',$this->getAttribute("link=5@href")));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "jazz");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("1", $this->getText("css=li.pager-current"));
    $this->assertTrue($this->isElementPresent("link=next ›"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=2@href")));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=next ›@href")));
    $this->click("link=2");
    $this->waitForPageToLoad("30000");
    $this->click("link=1");
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=‹ previous@href"));
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=1@href"));
    $this->assertEquals("2", $this->getText("css=li.pager-current"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=2$/',$this->getAttribute("link=3@href")));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=2$/',$this->getAttribute("link=next ›@href")));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=« first@href"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=‹ previous@href")));
    $this->assertEquals("/search/ting/jazz", $this->getAttribute("link=1@href"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=1$/',$this->getAttribute("link=2@href")));
    $this->assertEquals("3", $this->getText("css=li.pager-current"));
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=3$/',$this->getAttribute("link=4@href")));
    $this->click("link=next ›");
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=3$/',$this->getAttribute("link=next ›@href")));
    $this->click("link=next ›");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^\/search\/ting\/jazz[\s\S]page=4$/',$this->getAttribute("link=5@href")));
  }
}
?>
