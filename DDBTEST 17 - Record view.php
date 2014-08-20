<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testRecordView()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("", $this->getText("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
    $this->assertTrue($this->isElementPresent("link=Samfundet vasker sine hænder med metadon"));
    $this->assertTrue($this->isElementPresent("link=Klit"));
    $this->click("link=Samfundet vasker sine hænder med metadon");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div[2]/h2"));
    $this->assertTrue($this->isElementPresent("link=Samfundet vasker sine hænder med metadon"));
    $this->assertTrue($this->isElementPresent("id=availability-870971-avis71179532"));
    $this->assertTrue($this->isElementPresent("link=Klit"));
    $this->assertTrue($this->isElementPresent("link=Material details"));
    $this->assertTrue($this->isElementPresent("id=bookmark-870971-avis:71179532"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("", $this->getText("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("css=span.search-result--heading-type"));
    $this->assertTrue($this->isElementPresent("link=Samfundet vasker sine hænder med metadon"));
    $this->assertTrue($this->isElementPresent("link=Klit"));
    $this->click("link=Samfundet vasker sine hænder med metadon");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=h2.pane-title"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div[2]/h2"));
    $this->assertTrue($this->isElementPresent("link=Samfundet vasker sine hænder med metadon"));
    $this->assertTrue($this->isElementPresent("id=availability-870971-avis71179532"));
    $this->assertTrue($this->isElementPresent("link=Klit"));
    $this->assertTrue($this->isElementPresent("link=Material details"));
    $this->assertTrue($this->isElementPresent("id=bookmark-870971-avis:71179532"));
  }
}
?>
