<?php
class SubmitAnon extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*chrome");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testSubmitAnon()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "harry potter");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("css=li.list-item.search-result"));
    $this->type("id=edit-search-block-form--2", "");
    $this->click("id=edit-submit--3");
    $this->waitForPageToLoad("30000");
    $this->verifyText("css=div.messages.error", "Error message Please enter some keywords.");
  }
}
?>
