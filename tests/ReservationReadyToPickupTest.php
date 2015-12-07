<?php

require_once(__DIR__ . '/../bootstrap.php');

class ReservationReadyToPickupTest extends PHPUnit_Extensions_SeleniumTestCase {
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
    $this->assertElementPresent('link=1 Reservation ready for pick-up');
    $this->click('link=1 Reservation ready for pick-up');
    $this->abstractedPage->waitForPage();

    // Check for correct page heading.
    $this->assertElementContainsText('css=h2.pane-title', 'My reservations');

    // Next section roughly checks the markup.
    // This relies on the dummy LMS service, so the data should be pre-defined.
    $ready_for_pickup = array(
      array(
        'Dandy',
        '365',
        '',
        'Hovedbiblioteket',
        '5. September 2013',
      ),
    );
    for ($i = 0; $i < count($ready_for_pickup); $i++) {
      // Check title field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') h3.item-title', $ready_for_pickup[$i][0]);

      // Check pickup id field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.pickup-id .item-information-label', 'Pickup id:');
      if (!empty($ready_for_pickup[$i][1])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.pickup-id .item-information-data', $ready_for_pickup[$i][1]);
      }

      // Check pickup date field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.pickup-date .item-information-label', 'Pickup date:');
      if (!empty($ready_for_pickup[$i][2])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.pickup-date .item-information-data', $ready_for_pickup[$i][2]);
      }

      // Check pickup branch field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.pickup-branch .item-information-label', 'Pickup branch:');
      if (!empty($ready_for_pickup[$i][3])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.pickup-branch .item-information-data', $ready_for_pickup[$i][3]);
      }

      // Check pickup created field.
      $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.created-date .item-information-label', 'Created date:');
      if (!empty($ready_for_pickup[$i][4])) {
        $this->assertElementContainsText('css=#ding-reservation-reservations-ready-form .material-item:eq(' . $i . ') li.created-date .item-information-data', $ready_for_pickup[$i][4]);
      }
    }

    // Test the ability to delete a reservation ready for pickup.
    // Check if the checkbox for certain item is present, then click it.
    $this->assertElementPresent('css=#ding-reservation-reservations-ready-form .material-item:eq(0) input[type="checkbox"]');
    $this->click('css=#ding-reservation-reservations-ready-form .material-item:eq(0) input[type="checkbox"]');

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
    $this->assertElementNotPresent('css=#ding-reservation-reservations-ready-form .material-item:eq(1)');
  }
}
