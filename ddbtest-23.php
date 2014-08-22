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
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div[2]"));
    $this->assertTrue($this->isElementPresent("link=Bog (8)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net) (1)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (bånd) (5)"));
    $this->click("link=Bog (8)");
    $this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Bog$/', $this->getLocation()));
    $this->click("link=Lydbog (net) (1)");
    $this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(net\)$/', $this->getLocation()));
    $this->click("link=Lydbog (bånd) (5)");
    $this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(b%C3%A5nd\)$/', $this->getLocation()));

  }

  public function testcollectionViewAnonFromStart()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-search-block-form--2", "frank herbert klit");
    $this->click("id=edit-submit");
    $this->waitForPageToLoad("30000");
    $this->assertContains('klit', $this->getText("css=li.list-item.search-result"), '', true);
    $this->click("xpath=(//a[contains(text(),'Klit')])[2]");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div/div[2]"));
    $this->assertTrue($this->isElementPresent("link=Bog (8)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (net) (1)"));
    $this->assertTrue($this->isElementPresent("link=Lydbog (bånd) (5)"));
    $this->click("link=Bog (8)");
    $this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Bog$/', $this->getLocation()));
    $this->click("link=Lydbog (net) (1)");
    $this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(net\)$/', $this->getLocation()));
    $this->click("link=Lydbog (bånd) (5)");
    $this->assertTrue((bool)preg_match('/^.*ting\/collection\/870970-basis%3A28443471#Lydbog%20\(b%C3%A5nd\)$/', $this->getLocation()));
  }
}
?>
