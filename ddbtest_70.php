<?php
class UserProfile extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testChangePin()
  {
    $this->open("/en");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("Edit user profile", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//*[@id=\"user-profile-form\"]"));
    $this->assertTrue($this->isElementPresent("//*[@id=\"edit-pass--2\"]"));
    $this->type("id=edit-pincode-pass1", "6666");
    $this->type("id=edit-pincode-pass2", "6666");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Status message The changes have been saved.", $this->getText("//div[@id='page']/div/div/div/div/div"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Login", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", "1111110022");
    $this->type("id=edit-pass", "6666");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Edit user profile", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->type("id=edit-pincode-pass1", "5555");
    $this->type("id=edit-pincode-pass2", "5555");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("Status message The changes have been saved.", $this->getText("//div[@id='page']/div/div/div/div/div"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }
}
