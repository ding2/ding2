<?php
class UserProfile extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testEditDefaultInterestPeriod()
  {
    $this->open("/");
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("Edit user profile", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Profile for Alma", $this->getText("//form[@id='user-profile-form']/div/div/div/div/div/h2"));
    $this->assertTrue($this->isElementPresent("id=edit-profile-provider-alma-field-alma-interest-period-und"));
    $this->select("id=edit-profile-provider-alma-field-alma-interest-period-und", "label=12 months");
    $this->assertEquals("12 months", $this->getText("//*[@id=\"edit-profile-provider-alma-field-alma-interest-period-und\"]/option[6]"));
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div[2]/div/div/div/aside/div/h2/a"));
    $this->assertEquals("Status message The changes have been saved.", $this->getText("css=div.messages.status"));
    $this->assertEquals("12 months", $this->getText("//div[@id='page']/div/div/div[2]/div/div/div/div/div[2]/div/div/div/div[9]/div[2]/div"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
