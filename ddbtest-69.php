<?php
class UserProfile extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testPreferedBranch()
  {
    $this->open("/");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user$/',$this->getLocation()));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user\/\d+\/edit$/',$this->getLocation()));
    $this->assertTrue($this->isElementPresent("id=edit-profile-provider-alma-field-alma-preferred-branch-und"));
    $this->selectWindow("null");
    $this->select("id=edit-profile-provider-alma-field-alma-preferred-branch-und", "label=Sindal");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/users\/fagreferentcs$/',$this->getLocation()));
    $this->assertEquals("Status message The changes have been saved.", $this->getText("css=div.messages.status"));
    $this->assertEquals("Sindal", $this->getText("//div[@id='page']/div/div/div[2]/div/div/div/div/div[2]/div/div/div/div[7]/div[2]/div"));
  }
}
?>
