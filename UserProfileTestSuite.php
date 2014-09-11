<?php

require_once(dirname(__FILE__) . '/config.inc');

class UserProfile extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->setBrowser(TARGET_BROWSER);
    $this->setBrowserUrl(TARGET_URL);
  }

  /**
   * Check full name on my profile page.
   */
  public function testFullName()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("link=Login");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/h2"));
    $this->assertTrue($this->isElementPresent("css=div.field-label"));
    $this->assertTrue($this->isElementPresent("css=div.field-item.even"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check preferred branch on my profile page.
   */
  public function testPickLibrary()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My Account", $this->getText("//div[@id='page']/header/section/div/ul/li[3]/a/span"));
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertEquals("My account", $this->getText("//div[@id='page']/div/div/div/div/div/div/aside/div/h2/a"));
    $this->assertEquals("Preferred branch:", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/div/div[7]/div"));
    $this->assertEquals("Sindal", $this->getText("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/div/div[7]/div[2]/div"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check reservation pause on my profile page.
   */
  public function testReservationPause()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/h2"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/div/div[8]/div"));
    $this->assertTrue($this->isElementPresent("css=span.date-display-start"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check interest period on my profile page.
   */
  public function testInterestPeriod()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("link=Login");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/h2"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/div/div[9]/div"));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/div/div[2]/div/div/div/div[9]/div[2]/div"));
    $this->click("//div[@id='page']/header/section/div/ul/li[5]/a/span");
    $this->waitForPageToLoad("30000");
  }

  /**
   * Check if is editable default interest period on profile edit.
   */
  public function testEditDefaultInterestPeriod()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("css=i.icon-user");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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

  /**
   * Check if is editable default preferred branch.
   */
  public function testPreferedBranch()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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

  /**
   * Check if user pin could be changed.
   */
  public function testChangePin()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
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

  /**
   * Check if reservation could be paused.
   */
  public function testReservationAtPause()
  {
    $this->open("/" . TARGET_URL_LANG);
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->type("id=edit-name", TARGET_URL_USER);
    $this->type("id=edit-pass", TARGET_URL_USER_PASS);
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->click("//div[@id='page']/header/section/div/ul/li[3]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user$/',$this->getLocation()));
    $this->assertTrue($this->isElementPresent("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a"));
    $this->click("//div[@id='page']/div/div/div/div/div/div/aside/div/ul/li[2]/a/span");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/user\/\d+\/edit$/',$this->getLocation()));
    $this->assertTrue($this->isElementPresent("css=fieldset.form-wrapper"));
    $this->assertTrue($this->isElementPresent("//div[@id='edit-profile-provider-alma-field-alma-reservation-pause-und-0-value']"));
    $this->assertTrue($this->isElementPresent("//div[@id='edit-profile-provider-alma-field-alma-reservation-pause-und-0-value2']"));
    $this->click("id=edit-profile-provider-alma-field-alma-reservation-pause-und-0-value-datepicker-popup-0");
    $this->assertTrue($this->isElementPresent("//div[@id='ui-datepicker-div']"));
    $this->assertTrue($this->isElementPresent("css=select.ui-datepicker-month"));
    $this->assertTrue($this->isElementPresent("css=select.ui-datepicker-year"));
    $this->select("css=select.ui-datepicker-month", "value=8");
    $this->select("css=select.ui-datepicker-year", "value=2014");
    $this->click("link=4");
    try {
      $this->assertEquals("04/09/2014", $this->getValue("id=edit-profile-provider-alma-field-alma-reservation-pause-und-0-value-datepicker-popup-0"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
    $this->click("id=edit-profile-provider-alma-field-alma-reservation-pause-und-0-value2-datepicker-popup-0");
    $this->assertTrue($this->isElementPresent("css=select.ui-datepicker-month"));
    $this->assertTrue($this->isElementPresent("css=select.ui-datepicker-year"));
    $this->assertTrue($this->isElementPresent("//div[@id='ui-datepicker-div']"));
    $this->select("css=select.ui-datepicker-month", "value=8");
    $this->select("css=select.ui-datepicker-year", "value=2014");
    $this->click("link=12");
    try {
      $this->assertEquals("12/09/2014", $this->getValue("id=edit-profile-provider-alma-field-alma-reservation-pause-und-0-value2-datepicker-popup-0"));
    } catch (PHPUnit_Framework_AssertionFailedError $e) {
      array_push($this->verificationErrors, $e->toString());
    }
    $this->click("css=div.layout-wrapper");
    $this->click("id=edit-submit--2");
    $this->waitForPageToLoad("30000");
    $this->assertTrue((bool)preg_match('/^[\s\S]*\/users\/[a-z\-0-9]+$/',$this->getLocation()));
    $this->assertEquals("Status message The changes have been saved.", $this->getText("css=div.messages.status"));
    $this->assertEquals("Thursday, 4. September, 2014", $this->getText("css=span.date-display-start"));
    $this->assertEquals("Friday, 12. September, 2014", $this->getText("css=span.date-display-end"));
  }
}
