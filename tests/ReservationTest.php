<?php

require_once(__DIR__ . '/../bootstrap.php');

class ReservationTest extends PHPUnit_Extensions_SeleniumTestCase {
  protected $abstraction;
  protected $config;

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();
    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());
    resetState($this->config->getLms());
  }

  /**
   * Check material information on user reservation page.
   */
  public function testReservation() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for user account link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for reservation ready for pickup quick link.
    $this->assertElementPresent('link=5 Reservations');
    $this->click('link=5 Reservations');
    $this->abstractedPage->waitForPage();

    // Check for correct page heading.
    $this->assertElementContainsText('css=h2.pane-title', 'My reservations');

    // Next section roughly checks the markup.
    // This relies on the dummy LMS service, so the data should be pre-defined.
    $notready_for_pickup = array(
      array(
        'Nøglen til Da Vinci mysteriet',
        '',
        '1',
        '2. December 2014',
        'Sindal',
        '4. September 2014',
        '1415027',
      ),
      array(
        'Alt for damerne',
        '2010, 39',
        '1',
        '30. November 2014',
        'Sindal',
        '2. September 2014',
        '1414204',
      ),
      array(
        'Folkepension og delpension',
        '2014, 130. udgave',
        '1',
        '3. September 2015',
        'Sindal',
        '2. September 2014',
        '1415949',
      ),
    );
    for ($i = 0; $i < count($notready_for_pickup); $i++) {
      // Check title field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') h3.item-title', $notready_for_pickup[$i][0]);

      // Check periodical number field.
      if (!empty($notready_for_pickup[$i][1])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.periodical-number .item-information-label', 'Periodical no.:');
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.periodical-number .item-information-data', $notready_for_pickup[$i][1]);
      }

      // Check queue number field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.queue-number .item-information-label', 'Queue number:');
      if (!empty($notready_for_pickup[$i][2])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.queue-number .item-information-data', $notready_for_pickup[$i][2]);
      }

      // Check expiry date field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.expire-date .item-information-label', 'Expiry date:');
      if (!empty($notready_for_pickup[$i][3])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.expire-date .item-information-data', $notready_for_pickup[$i][3]);
      }

      // Check branch field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.pickup-branch .item-information-label', 'Pickup branch:');
      if (!empty($notready_for_pickup[$i][4])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.pickup-branch .item-information-data', $notready_for_pickup[$i][4]);
      }

      // Check created date field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.created-date .item-information-label', 'Created date:');
      if (!empty($notready_for_pickup[$i][5])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.created-date .item-information-data', $notready_for_pickup[$i][5]);
      }

      // Check order number field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.pickup-id .item-information-label', 'Order nr.:');
      if (!empty($notready_for_pickup[$i][6])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.pickup-id .item-information-data', $notready_for_pickup[$i][6]);
      }
    }

    // Test change of reservation period and pickup branch.
    $this->assertElementPresent('css=#ding-reservation-reservations-notready-form .select-all input[type="checkbox"]');
    $this->click('css=#ding-reservation-reservations-notready-form .select-all input[type="checkbox"]');

    // Wait for the buttons to appear.
    $this->abstractedPage->waitForElement('css=.update-reservations input[type="submit"]');
    $this->mouseDown('css=#ding-reservation-reservations-notready-form .update-reservations input[type="submit"]');

    // This will trigger a popup with selection options.
    $this->abstractedPage->waitForElement('css=.ding-popup-content');
    $this->assertElementPresent('css=#ding-reservation-update-reservations-form #edit-provider-options-alma-preferred-branch');
    $this->assertElementPresent('css=#ding-reservation-update-reservations-form #edit-provider-options-interest-period');

    // Select a different branch.
    $this->select('css=#ding-reservation-update-reservations-form #edit-provider-options-alma-preferred-branch', 'value=hj~oe');

    // Select a different interest period.
    $this->select('css=#ding-reservation-update-reservations-form #edit-provider-options-interest-period', 'value=360');

    // Submit the changes.
    $this->mouseDown('css=#ding-reservation-update-reservations-form input[type="submit"]');

    // Wait for ajax.
    sleep(5);
    $this->abstractedPage->refresh();

    // Check the results again.
    $notready_for_pickup = array(
      array(
          'Nøglen til Da Vinci mysteriet',
          '30. August 2015',
          'Hjørring',
      ),
      array(
          'Folkepension og delpension',
          '3. September 2015',
          'Hjørring',
      ),
      array(
          'Alt for damerne',
          '28. August 2015',
          'Hjørring',
      ),
    );
    for ($i = 0; $i < count($notready_for_pickup); $i++) {
      // Check title field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') h3.item-title', $notready_for_pickup[$i][0]);
      // Check expiry date.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.expire-date .item-information-data', $notready_for_pickup[$i][1]);
      // Check branch.
      $this->assertElementContainsText('css=#ding-reservation-reservations-notready-form .material-item:eq(' . $i . ') li.pickup-branch .item-information-data', $notready_for_pickup[$i][2]);
    }


    // Test the ability to delete a reservation .
    // Check if the checkbox for certain item is present, then click it.
    $this->assertElementPresent('css=#ding-reservation-reservations-notready-form .material-item:eq(2) input[type="checkbox"]');
    $this->click('css=#ding-reservation-reservations-notready-form .material-item:eq(2) input[type="checkbox"]');

    // A delete button should appear.
    $this->abstractedPage->waitForElement('css=#edit-actions-top-delete--2');
    $this->mouseDown('css=#edit-actions-top-delete--2');

    // This should trigger a popup confirmation.
    $this->abstractedPage->waitForElement('css=.ding-popup-content #ding-reservation-delete-reservations-form');
    $this->mouseDown('css=.ding-popup-content #ding-reservation-delete-reservations-form input[type="submit"]');
    // Wait for ajax to finish.
    sleep(5);
    $this->abstractedPage->refresh();
    // Check the item is deleted.
    $this->assertElementNotPresent('css=#ding-reservation-reservations-notready-form .material-item:eq(2)');
  }
}
