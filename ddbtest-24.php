<?php
class collectionView  extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testcollectionViewLoggedFromStart()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "frank herbert klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=div.ting-object"), '', true);
    $this->click("id=bookmark-870970-basis:05306809");
    sleep(2);
    $this->type("//form[@id='user-login']/div/div[1]/input", "1111110022");
    $this->type("//form[@id='user-login']/div/div[2]/input", "5555");
    $this->mouseDownAt("//form[@id='user-login']/div/div[3]/input");
    sleep(2);
    $this->assertEquals("Added to bookmarks", $this->getText("id=ui-id-1"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=bookmark-870970-basis:05306809");
    $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=reservation-870970-basis:05306809");
    $this->assertEquals("css=div.messages.status > ul > li", "\"Klit\" reserved and will be available for pickup at Hjørring.");
    $this->mouseDownAt("//div[5]/div/button");
    $this->click("id=reservation-870970-basis:05306809");
    sleep(2);
    $this->assertEquals("Error message \"You have already reserved \"Klit\".", $this->getText("css=div.messages.error"));
    $this->mouseDownAt("//div[5]/div/button");
  }

  public function testcollectionViewAnonFromStart()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "frank herbert klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=div.ting-object"), '', true);
    $this->click("id=bookmark-870970-basis:05306809");
    sleep(2);
    $this->assertEquals("Added to bookmarks", $this->getText("id=ui-id-1"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=bookmark-870970-basis:05306809");
    $this->assertEquals("This item is in bookmarks already.", $this->getText("css=div.ding-bookmark-message"));
    $this->mouseDownAt("//body/div[4]");
    $this->click("id=reservation-870970-basis:05306809");
    $this->assertEquals("css=div.messages.status > ul > li", "\"Klit\" reserved and will be available for pickup at Hjørring.");
    $this->mouseDownAt("//div[4]/div/button);
    $this->click("id=reservation-870970-basis:05306809");
    sleep(20);
    $this->assertEquals("Error message \"You have already reserved \"Klit\".", $this->getText("css=div.messages.error"));
    $this->click("//div[4]/div/button");
  }
}
?>
