<?php

require_once(__DIR__ . '/../bootstrap.php');

class UserProfileTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    resetState($this->config->getLms());
  }

  /**
   * Check info and interreaction on user profile page.
   */
  public function testUserProfile() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for account page link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for user status link.
    $this->assertElementPresent('link=Edit user profile');
    $this->click('link=Edit user profile');
    $this->abstractedPage->waitForPage();

    // Check for pane title.
    $this->assertElementContainsText('css=.pane-title', 'Profile for Alma');
    // Set new branch and period.
    $this->select('css=#edit-profile-provider-alma-field-alma-preferred-branch-und', 'value=bed');
    $this->select('css=#edit-profile-provider-alma-field-alma-interest-period-und', 'value=360');

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

    // Set new pincode.
    $this->type('css=#edit-pincode-pass1', '6666');
    $this->type('css=#edit-pincode-pass2', '6666');

    // Save the form.
    $this->click('css=#user-profile-form input[type="submit"]');
    $this->abstractedPage->waitForPage();

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

    // Check various fields on profile page for updated information.
    $this->assertElementContainsText('css=.pane-profile2 h2', 'Your information');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-full-name .field-items', 'DDBCMS - testbruger 1');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-street-name .field-items', 'Vestre Ringgade 200');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-postal-code .field-items', '8000');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-city .field-items', 'Århus C.');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-mail .field-items', 'gba@aarhus.dk');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-mobile-phone .field-items', '11223344');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-preferred-branch .field-items', 'Beder-Malling');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-reservation-pause .field-items', 'Friday, 30. June, 2017 to Saturday, 30. June, 2018');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-interest-period .field-items', '12 months');
  }
}
