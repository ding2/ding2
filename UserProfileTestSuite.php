<?php

require_once(__DIR__ . '/autoload.php');

class UserProfile extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstractedPage;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
  }

  /**
   * Check full name on my profile page.
   */
  public function testUserProfile() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    $this->assertElementContainsText('css=.pane-profile2 h2', 'Your information');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-full-name .field-items', 'Fagreferent.CS');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-street-name .field-items', 'Adresse --');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-postal-code .field-items', '9800');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-city .field-items', 'Hjørring');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-mail .field-items', 'claus.just@hjoerring.dk');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-sms .field-items', '40207780(Notice that there is a fee for receiving a SMS)');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-preferred-branch .field-items', 'Sindal');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-reservation-pause .field-items', 'Thursday, 4. September, 2014 to Friday, 12. September, 2014');
    $this->assertElementContainsText('css=.pane-profile2 .field-name-field-alma-interest-period .field-items', '6 months');
  }

//   /**
//    * Check if is editable default interest period on profile edit.
//    */
//   public function testEditDefaultInterestPeriod()
//   {

//   }

//   /**
//    * Check if is editable default preferred branch.
//    */
//   public function testPreferedBranch()
//   {

//   }

//   /**
//    * Check if user pin could be changed.
//    */
//   public function testChangePin()
//   {

//   }

//   /**
//    * Check if reservation could be paused.
//    */
//   public function testReservationAtPause()
//   {

//   }
}
