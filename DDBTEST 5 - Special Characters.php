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
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "gæ");
    $this->typeKeys("id=edit-search-block-form--2", "gæ");
    for ($second = 0; ; $second++) {
        if ($second >= 60) $this->fail("timeout");
        try {
            if ($this->isTextPresent("gæk, gæk, gæk")) break;
        } catch (Exception $e) {}
        sleep(1);
    }

    $this->mouseOver("//div[@id='autocomplete']/ul/li[2]/div");
    $this->click("css=li.selected > div");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("", $this->getText("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Gæk, gæk -"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-search-block-form--2", "gæ");
    $this->typeKeys("id=edit-search-block-form--2", "gæ");
    for ($second = 0; ; $second++) {
        if ($second >= 60) $this->fail("timeout");
        try {
            if ($this->isTextPresent("gæk, gæk, gæk")) break;
        } catch (Exception $e) {}
        sleep(1);
    }

    $this->mouseOver("//div[@id='autocomplete']/ul/li[2]/div");
    $this->click("css=li.selected > div");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("", $this->getText("id=edit-search-block-form--2"));
    $this->assertTrue($this->isElementPresent("link=Gæk, gæk -"));
  }
}
?>
