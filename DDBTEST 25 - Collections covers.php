<?php
class CollectionView extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testCollectionCoversAuth()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->open("ting/collection/870970-basis%3A27267912");
    $this->assertTrue($this->isElementPresent("css=.ting-collection-wrapper:nth-child(1) .ting-cover img"));
    $this->assertFalse($this->isElementPresent("css=.ting-collection-wrapper:nth-child(2) .ting-cover img"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  public function testCollectionCovers()
  {
    $this->open("/");
    $this->waitForPageToLoad("30000");
    $this->open("ting/collection/870970-basis%3A27267912");
    $this->assertTrue($this->isElementPresent("css=.ting-collection-wrapper:nth-child(1) .ting-cover img"));
    $this->assertFalse($this->isElementPresent("css=.ting-collection-wrapper:nth-child(2) .ting-cover img"));
  }
}
?>
