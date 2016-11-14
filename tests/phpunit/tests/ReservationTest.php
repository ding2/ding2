<?php

require_once 'Ding2TestBase.php';

class ReservationTest extends Ding2TestBase {
  protected function setUp() {
    parent::setUp();
    resetState($this->config->getLms());
    $this->config->resetLms();
  }

  /**
   * Check material information on user reservation page.
   */
  public function testReservation() {
    $this->open($this->config->getUrl() . $this->config->getLocale());
    $this->abstractedPage->waitForPage();
    $this->abstractedPage->userLogin($this->config->getUser(), $this->config->getPass());

    // Check for user account link.
    $this->assertElementPresent('link=My Account');
    $this->click('link=My Account');
    $this->abstractedPage->waitForPage();

    // Check for reservation quick link.
    $this->assertElementContainsText('css=div.ding-user-lists li.reservations a.signature-label', 'Reservations');
/* counter is not reset on $this->config->resetLms();
    $this->assertElementContainsText('css=div.ding-user-lists li.reservations span.label', '56');
*/
    $this->assertElementPresent('link=Reservations');
    $this->click('link=Reservations');
    $this->abstractedPage->waitForPage();

    // Check for correct page heading.
    $this->assertElementContainsText('css=div.pane-reservations h2.pane-title', 'My reservations');

    // Next section roughly checks the markup.
    // This relies on the dummy LMS service, so the data should be pre-defined.
    $notready_for_pickup = array(
      array(
        'Alt om haven',
        '2012, 15',
        '1',
        '7. September 2015',
        'Hovedbiblioteket',
        '11. March 2015',
        '12846957',
      ),
      array(
        'Mad & venner',
        '2012, December, Nr. 092',
        '1',
        '5. March 2016',
        'Hovedbiblioteket',
        '11. March 2015',
        '12846959',
      ),
      array(
        'Hr. Peters blomster',
        '',
        '1',
        '15. June 2016',
        'Hovedbiblioteket',
        '21. June 2015',
        '12846965',
      ),
      array(
        'Title not available',
        '2012, Januar, 1',
        '1',
        '24. May 2016',
        'Hovedbiblioteket',
        '26. November 2015',
        '12846996',
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
    $this->select('css=#ding-reservation-update-reservations-form #edit-provider-options-alma-preferred-branch', 'value=bed');

    // Select a different interest period.
    $this->select('css=#ding-reservation-update-reservations-form #edit-provider-options-interest-period', 'value=360');

    // Submit the changes.
    $this->mouseDown('css=#ding-reservation-update-reservations-form input[type="submit"]');

    // Wait for ajax.
    sleep(5);
    $this->abstractedPage->refresh();

    // Check the results again.
    $next_year_date = date("j. F Y", strtotime("+360 days", time()));
    $notready_for_pickup = array(
      array(
        'Title not available',
        $next_year_date,
        'Beder-Malling',
      ),
      array(
        'Hr. Peters blomster',
        $next_year_date,
        'Beder-Malling',
      ),
      array(
        'Mad & venner',
        $next_year_date,
        'Beder-Malling',
      ),
      array(
        'Alt om haven',
        $next_year_date,
        'Beder-Malling',
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


    // Test the ability to delete a reservation.
    // Check if the checkbox for FIRST item is present, then click it.
    $this->assertElementPresent('css=#ding-reservation-reservations-notready-form .material-item:eq(3) input[type="checkbox"]');
    $this->click('css=#ding-reservation-reservations-notready-form .material-item:eq(3) input[type="checkbox"]');

    // A delete button should appear.
    $this->abstractedPage->waitForElement('css=#edit-actions-top-delete--2');
    $this->mouseDown('css=#edit-actions-top-delete--2');

    // This should trigger a popup confirmation.
    $this->abstractedPage->waitForElement('css=.ding-popup-content #ding-reservation-delete-reservations-form');
    $this->click('css=.ding-popup-content #ding-reservation-delete-reservations-form a#edit-delete');
    // Wait for ajax to finish.
    sleep(5);
    $this->abstractedPage->refresh();
    // Check the item is no more present.
    $this->assertElementNotPresent('link=Title not available');
  }
}
