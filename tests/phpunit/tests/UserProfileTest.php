<?php

require_once 'Ding2TestBase.php';

class UserProfileTest extends Ding2TestBase {
  protected function setUp() {
    parent::setUp();
    resetState($this->config->getLms());
    $this->config->resetLms();
  }

  /**
   * Check info on user profile page.
   */
  public function testUserProfile() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for account page link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for user status link.
   // if ($this->config->getServer() == 'localhost') {
      $this->assertElementPresent('link=Edit user profile');
      $this->click('link=Edit user profile');
      $this->abstractedPage->waitForPage();
    //}
    /*else if ($this->config->getServer() == 'CircleCI') {
      $this->assertElementPresent('link=Redigér brugerprofil');
      $this->click('link=Redigér brugerprofil');
      $this->abstractedPage->waitForPage();
    }*/
    
    // Check for pane title.
    $this->assertElementContainsText('css=.panel-pane.pane-profile2-form', 'Profile for Alma');

    // Check various fields on profile page for updated information.
/* Navn, adresse, postnr og by er forsvundet fra brugerprofilen.
    $this->assertElementContainsText('css=.pane-profile2 h2', 'Your information');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-full-name .field-items', 'DDBCMS - testbruger 1');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-street-name .field-items', 'Vestre Ringgade 200');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-postal-code .field-items', '8000');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-city .field-items', 'Århus C.');
*/
    $this->assertElementValueEquals('css=#edit-profile-provider-alma-field-alma-mobile-phone-und-0-value', '11223344');
    $this->assertElementValueEquals('css=#edit-profile-provider-alma-field-alma-mail-und-0-email', 'gba@aarhus.dk');
    $this->assertIsSelected('css=#edit-profile-provider-alma-field-alma-preferred-branch-und', 'hb');
    $this->assertIsSelected('css=#edit-profile-provider-alma-field-alma-interest-period-und', '180');
    $this->assertElementValueEquals('css=#edit-profile-provider-alma-field-alma-reservation-pause-und-0-value-datepicker-popup-0', '05/06/2015');
    $this->assertElementValueEquals('css=#edit-profile-provider-alma-field-alma-reservation-pause-und-0-value2-datepicker-popup-0', '19/06/2015');
  }

  /**
   * Check preferred branch change on user profile page.
   */
  public function testUserProfilePreferredBranchChange() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for account page link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for user status link.
    //if ($this->config->getServer() == 'localhost') {
      $this->assertElementPresent('link=Edit user profile');
      $this->click('link=Edit user profile');
      $this->abstractedPage->waitForPage();
    //}
    /*else if ($this->config->getServer() == 'CircleCI') {
      $this->assertElementPresent('link=Redigér brugerprofil');
      $this->click('link=Redigér brugerprofil');
      $this->abstractedPage->waitForPage();
    }*/
    
   // Set new branch and period.
    $this->select('css=#edit-profile-provider-alma-field-alma-preferred-branch-und', 'value=bed');
    $this->select('css=#edit-profile-provider-alma-field-alma-interest-period-und', 'value=360');

    // Save the form.
/* AlmaClientHTTPError: Request error: 404. Not Found in AlmaClient->request()
    $this->click('css=#user-profile-form input.form-submit');
    $this->abstractedPage->waitForPage();
*/
  }

  /**
   * Check pincode change on user profile page.
   */
  public function testUserProfilePincodeChange() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for account page link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for user status link.
    //if ($this->config->getServer() == 'localhost') {
      $this->assertElementPresent('link=Edit user profile');
      $this->click('link=Edit user profile');
      $this->abstractedPage->waitForPage();
    //}
    /*else if ($this->config->getServer() == 'CircleCI') {
      $this->assertElementPresent('link=Redigér brugerprofil');
      $this->click('link=Redigér brugerprofil');
      $this->abstractedPage->waitForPage();
    }*/
    
    // Set new pincode.
    $this->type('css=#edit-pincode-pass1', '6666');
    $this->type('css=#edit-pincode-pass2', '6666');
    
    // Save the form.
    $this->click('css=#user-profile-form input.form-submit');
    $this->abstractedPage->waitForPage();
    $this->assertElementContainsText('css=div.messages.error', 'The old pincode confirm is empty.');

/* NB: Set new pincode test don't work: ALMA mockup return changeAbsentDateResponse on password change request.
       Also, old pincode needs to be entered, in order to change pin code.
    // Log out, to test new pin code.
    $this->assertElementPresent('link=Logout');
    $this->click('link=Logout');
    $this->abstractedPage->waitForPage();

    // Login with new pincode.
    $this->abstractedPage->userLogin($this->config->getUser(), '6666');

    // Check if logged in succesfuly.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();
*/
  }


  /**
   * Check reservation pause on user profile page.
   */
  public function testUserProfileReservationPause() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for account page link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for user status link.
   //if ($this->config->getServer() == 'localhost') {
      $this->assertElementPresent('link=Edit user profile');
      $this->click('link=Edit user profile');
      $this->abstractedPage->waitForPage();
    //}
    /*else if ($this->config->getServer() == 'CircleCI') {
      $this->assertElementPresent('link=Redigér brugerprofil');
      $this->click('link=Redigér brugerprofil');
      $this->abstractedPage->waitForPage();
    }*/
    
    // Set reservation pause start.
    $this->click('css=#edit-profile-provider-alma-field-alma-reservation-pause-und-0-value-datepicker-popup-0');
    $this->abstractedPage->waitForElement('css=#ui-datepicker-div');
    $this->select('css=.ui-datepicker-year', 'value=2017');
    $this->assertElementPresent('link=30');
    $this->click('link=30');

    // Set reservation pause stop.
    $this->click('css=#edit-profile-provider-alma-field-alma-reservation-pause-und-0-value2-datepicker-popup-0');
    $this->abstractedPage->waitForElement('css=#ui-datepicker-div');
    $this->select('css=.ui-datepicker-year', 'value=2018');
    $this->assertElementPresent('link=30');
    $this->click('link=30');
/* AlmaClientHTTPError: Request error: 404. Not Found in AlmaClient->request()
    // Save the form.
    $this->click('css=#user-profile-form input.form-submit');
    $this->abstractedPage->waitForPage();
*/
  }
  
}
