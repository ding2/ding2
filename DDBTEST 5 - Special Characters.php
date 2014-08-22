<?php
class OpenScan extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testSpecialCharacters()
  {
    $this->open("/");
    $this->type("id=edit-search-block-form--2", "Afskrivning på maskiner");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Afskrivning på maskiner", $this->getValue("id=edit-search-block-form--2"));
    $this->assertEquals("Afskrivning på maskiner", $this->getText("link=Afskrivning på maskiner"));
    $this->click("css=img[alt=\"Home\"]");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "da \"plejer\" døde");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    for ($second = 0; ; $second++) {
        if ($second >= 60) $this->fail("timeout");
        try {
            if ($this->isElementPresent("//*[@id=\"autocomplete\"]/ul/li")) break;
        } catch (Exception $e) {}
        sleep(1);
    }

    $this->assertEquals("da \"plejer\" døde", $this->getText("//*[@id=\"autocomplete\"]/ul/li[9]/div"));
  }

  public function testSpecialCharactersAuth()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "Afskrivning på maskiner");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Afskrivning på maskiner", $this->getValue("id=edit-search-block-form--2"));
    $this->assertEquals("Afskrivning på maskiner", $this->getText("link=Afskrivning på maskiner"));
    $this->click("css=img[alt=\"Home\"]");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "da \"plejer\" døde");
    $this->fireEvent("id=edit-search-block-form--2", "keyup");
    for ($second = 0; ; $second++) {
        if ($second >= 60) $this->fail("timeout");
        try {
            if ($this->isElementPresent("//*[@id=\"autocomplete\"]/ul/li")) break;
        } catch (Exception $e) {}
        sleep(1);
    }

    $this->assertEquals("da \"plejer\" døde", $this->getText("//*[@id=\"autocomplete\"]/ul/li[9]/div"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
?>
