<?php
class SearchResult extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testMaterialCollection()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Dune Frank Herbert");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Samhørende: Dune, Dune messiah, Children of Dune; God emperor of Dune, Heretics of Dune, Chapterhouse", $this->getText("css=div.field-item.even"));
    $this->click("link=Dune messiah");
    $this->waitForPageToLoad("30000");
    try {
        $this->assertEquals("\"Dune messiah\"", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Dune Frank Herbert");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Samhørende: Dune, Dune messiah, Children of Dune; God emperor of Dune, Heretics of Dune, Chapterhouse", $this->getText("css=div.field-item.even"));
    $this->click("link=Dune messiah");
    $this->waitForPageToLoad("30000");
    try {
        $this->assertEquals("\"Dune messiah\"", $this->getValue("id=edit-search-block-form--2"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
        array_push($this->verificationErrors, $e->toString());
    }
  }
}
?>
