<?php
class UserProfile extends PHPUnit_Extensions_SeleniumTestCase
{
  protected function setUp()
  {
    $this->setBrowser("*firefox");
    $this->setBrowserUrl("http://ding2tal.easyting.dk/");
  }

  public function testReservationAtPause()
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
?>
