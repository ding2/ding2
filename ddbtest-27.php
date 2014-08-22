<?php
class itemPage extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testitemPageLoggedFromStart()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('Rom : i Vilhelm Bergsøes', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=bookmark-870970-basis:50676927"));
    $this->assertTrue($this->isElementPresent("id=reservation-870970-basis:50676927"));
    $this->click("id=bookmark-870970-basis:50676927");
    sleep(4);
    $msgs = array(
      "Added to bookmarks",
      "This item is in bookmarks already.",
    );
    $this->assertTrue(in_array($this->getText("css=div.ding-bookmark-message"), $msgs));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=bookmark-870970-basis:50676927");
    sleep(4);
    $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=reservation-870970-basis:50676927");
    sleep(4);
    $msgs = array(
      "\"Rom\" reserved and will be available for pickup at Hjørring.",
      "Error message \"You have already reserved \"Rom\".",
      "Error message \"Rom\" is not available for reservation.",
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[4]/div/button");
    $this->click("id=reservation-870970-basis:50676927");
    sleep(4);
    $msgs = array(
      "Error message \"You have already reserved \"Rom\".",
      "Error message \"Rom\" is not available for reservation.",
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[5]/div/button");
  }

  public function testitemPageAnonFromStart()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "Rom : i Vilhelm Bergsøes");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('Rom : i Vilhelm Bergsøes', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("link=Rom : i Vilhelm Bergsøes fodspor fra Piazza del Popolo");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("id=bookmark-870970-basis:50676927"));
    $this->assertTrue($this->isElementPresent("id=reservation-870970-basis:50676927"));
    $this->click("id=bookmark-870970-basis:50676927");
    sleep(4);
    $this->type("//form[@id='user-login']/div/div[1]/input", "1111110022");
    $this->type("//form[@id='user-login']/div/div[2]/input", "5555");
    $this->mouseDownAt("//form[@id='user-login']/div/div[3]/input");
    sleep(4);
    $msgs = array(
      "Added to bookmarks",
      "This item is in bookmarks already.",
    );
    $this->assertTrue(in_array($this->getText("css=div.ding-bookmark-message"), $msgs));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=bookmark-870970-basis:50676927");
    sleep(4);
    $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=reservation-870970-basis:50676927");
    sleep(4);
    $msgs = array(
      "\"Rom\" reserved and will be available for pickup at Hjørring.",
      "Error message \"You have already reserved \"Rom\".",
      "Error message \"Rom\" is not available for reservation.",
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[5]/div/button");
    $this->click("id=reservation-870970-basis:50676927");
    sleep(4);
    $msgs = array(
      "Error message \"You have already reserved \"Rom\".",
      "Error message \"Rom\" is not available for reservation.",
    );
    $this->assertTrue(in_array($this->getText("css=div.messages"), $msgs));
    $this->mouseDownAt("//div[6]/div/button");
  }
}
?>
