<?php

require_once(__DIR__ . '/autoload.php');
require_once(__DIR__ . '/bootstrap.php');

class ReservationReadyToPickup extends PHPUnit_Extensions_SeleniumTestCase {

  protected function setUp() {
    $this->abstractedPage = new DDBTestPageAbstraction($this);
    $this->config = new DDBTestConfig();

    $this->setBrowser($this->config->getBrowser());
    $this->setBrowserUrl($this->config->getUrl());

    resetState();
  }

  /**
   * Check reservation ready for pickup data on my reservation page.
   */
  public function testReadyReservation() {
    $this->open('/' . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for user account link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for reservation ready for pickup quick link.
    $this->assertElementPresent('link=2 Reservations ready for pick-up');
    $this->click('link=2 Reservations ready for pick-up');
    $this->abstractedPage->waitForPage();

    // Check for correct page heading.
    $this->assertElementContainsText('css=h2.pane-title', 'My reservations');

    // Next section roughly checks the markup.
    // This relies on the dummy LMS service, so the data should be pre-defined.
    $ready_for_pickup = array(
      array(
        '255',
        '',
        'Hjørring',
        '2. September 2014',
        'The lady',
      ),
      array(
        '0',
        '15. September 2014',
        'Bogbus',
        '2. September 2014',
        'Angels and demons'
      ),
    );
    for ($i = 3, $j = 0; $i <= count($ready_for_pickup) + 2; $i++, $j++) {
      // Check title field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') h3.item-title', $ready_for_pickup[$j][4]);

      // Check pickup id field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.pickup-id .item-information-label', 'Pickup id:');
      if (!empty($ready_for_pickup[$j][0])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.pickup-id .item-information-data', $ready_for_pickup[$j][0]);
      }

      // Check pickup date field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.pickup-date .item-information-label', 'Pickup date:');
      if (!empty($ready_for_pickup[$j][1])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.pickup-date .item-information-data', $ready_for_pickup[$j][1]);
      }

      // Check pickup branch field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.pickup-branch .item-information-label', 'Pickup branch:');
      if (!empty($ready_for_pickup[$j][2])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.pickup-branch .item-information-data', $ready_for_pickup[$j][2]);
      }

      // Check pickup created field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.created-date .item-information-label', 'Created date:');
      if (!empty($ready_for_pickup[$j][3])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:nth-child(' . $i . ') li.created-date .item-information-data', $ready_for_pickup[$j][3]);
      }
    }

    // Test the ability to delete a reservation ready for pickup.
    // Check if the checkbox for certain item is present, then click it.
    $this->assertElementPresent('css=#ding-reservation-reservations-ready-form .material-item:nth-child(4) #edit-reservations-1414140-1414140');
    $this->click('css=#ding-reservation-reservations-ready-form .material-item:nth-child(4) #edit-reservations-1414140-1414140');

    // A delete button should appear.
    $this->abstractedPage->waitForElement('css=#edit-actions-top-delete');
    $this->mouseDown('css=#edit-actions-top-delete');

    // This should trigger a popup confirmation.
    $this->abstractedPage->waitForElement('css=.ding-popup-content #ding-reservation-delete-reservations-form');
    $this->mouseDown('css=.ding-popup-content #ding-reservation-delete-reservations-form input[type="submit"]');
    // Wait for ajax to finish.
    sleep(5);
    $this->abstractedPage->refresh();
    // Check the item is deleted.
    $this->assertElementNotPresent('css=#ding-reservation-reservations-ready-form .material-item:nth-child(4)');
  }
}
