<?php

/**
 * @file
 * Test reservation provider functions.
 */

require_once "ProviderTestCase.php";
require_once 'includes/classes/FBS.php';
require_once dirname(__DIR__) . '/vendor/autoload.php';

if (!function_exists('ding_provider_build_entity_id')) {
  /**
   * Loan list calls this, mock it.
   */
  function ding_provider_build_entity_id($id, $agency = '') {
    return $id . ($agency ? ":" . $agency : '');
  }
}

/**
 * Some provider functions uses this.
 */
define('REQUEST_TIME', time());

/**
 * Test user provider functions.
 */
class ReservationProviderTest extends ProviderTestCase {

  /**
   * Test reservation list.
   */
  public function testList() {
    $this->provider = 'reservation';
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    // State can be:
    //      - reserved
    //      - readyForPickup
    //      - interLibraryReservation
    //      - other
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:42355089',
            'pickupBranch' => 113,
            'expiryDate' => '2015-10-30',
            'reservationId' => 45,
            'pickupDeadline' => '2015-04-30',
            'dateOfReservation' => '2015-01-30',
            'state' => 'readyForPickup',
            // Don't expect to see this one..
            'numberInQueue' => 2,
          ),
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:40317805',
            'pickupBranch' => 113,
            'expiryDate' => '2015-10-30',
            'reservationId' => 48,
            'pickupDeadline' => '',
            'dateOfReservation' => '2015-01-10',
            'state' => 'reserved',
            'numberInQueue' => 2,
          ),
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:50717437',
            'pickupBranch' => 113,
            'expiryDate' => '2015-12-30',
            'reservationId' => 248,
            'pickupDeadline' => '',
            'dateOfReservation' => '2014-01-30',
            'state' => 'interLibraryReservation',
            'numberInQueue' => 5,
          ),
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:05197074',
            'pickupBranch' => 113,
            'expiryDate' => '2015-11-30',
            'reservationId' => 241,
            'pickupDeadline' => '',
            'dateOfReservation' => '2014-01-30',
            'state' => 'other',
            'numberInQueue' => 4,
          ),
        )
      ),

    );
    $httpclient = $this->getHttpClient($json_responses);

    // Run through tests.
    $fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);

    $user = (object) array(
      'fbs_patron_id' => '123',
    );

    // Check success.
    $res = $this->providerInvoke('list', $user);
    $expected = array(
      // Ready for pickup
      DING_RESERVATION_READY => array(
        45 => array(
          'ding_entity_id' => '870970-basis:42355089',
          'id' => 45,
          'pickup_date' => '2015-04-30',
          'pickup_branch_id' => 113,
          'created' => '2015-01-30',
        ),
      ),
      // Reserved
      DING_RESERVATION_NOT_READY => array(
        48 => array(
          'ding_entity_id' => '870970-basis:40317805',
          'id' => 48,
          'pickup_branch_id' => 113,
          'created' => '2015-01-10',
          'queue_number' => 2,
          'expiry' => '2015-10-30',
        ),
        241 => array(
          'ding_entity_id' => '870970-basis:05197074',
          'id' => 241,
          'pickup_branch_id' => 113,
          'created' => '2014-01-30',
          'queue_number' => 4,
          'expiry' => '2015-11-30',
        ),
      ),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(
        248 => array(
          'ding_entity_id' => '870970-basis:50717437',
          'id' => 248,
          'pickup_branch_id' => 113,
          'created' => '2014-01-30',
          'expiry' => '2015-12-30',
        )
      ),
    );
    $this->assertEquals($expected, $res);
  }

  /**
   * Test reservation create.
   */
  public function testCreate() {
    $this->provider = 'reservation';
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    $expected_expiry = date('Y-m-d', (REQUEST_TIME + 24 * 60 * 60));
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:50717437',
            'pickupBranch' => 123,
            'expiryDate' => $expected_expiry,
            'reservationId' => 123,
            'pickupDeadline' => NULL,
            'dateOfReservation' => '2015-03-09',
            'state' => 'reserved',
            'numberInQueue' => 3,
          ),
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:42355089',
            'pickupBranch' => 123,
            'expiryDate' => $expected_expiry,
            'reservationId' => 124,
            'pickupDeadline' => NULL,
            'dateOfReservation' => '2015-03-09',
            'state' => 'reserved',
            'numberInQueue' => 2,
          ),
        )
      ),
    );
    $httpclient = $this->getHttpClient($json_responses);

    // Run through tests.
    $fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);

    $user = (object) array(
      'fbs_patron_id' => '123',
    );

    // Check success.

    $reservation_ids = array(
      '870970-basis:50717437',
      '870970-basis:42355089',
    );
    $options = array(
      'preferred_branch' => 123,
      'interest_period' => 30,
    );
    $res = $this->providerInvoke('create', $user, $reservation_ids, $options);
    // No response is expected.
  }

  /**
   * Test reservation update.
   */
  public function testUpdate() {
    $this->provider = 'reservation';
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    $expected_expiry = date('Y-m-d', (REQUEST_TIME + 24 * 60 * 60));
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:50717437',
            'pickupBranch' => 123,
            'expiryDate' => $expected_expiry,
            'reservationId' => 123,
            'pickupDeadline' => NULL,
            'dateOfReservation' => '2015-03-09',
            'state' => 'reserved',
            'numberInQueue' => 3,
          ),
        )
      ),
    );
    $httpclient = $this->getHttpClient($json_responses);

    // Run through tests.
    $fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);

    $user = (object) array(
      'fbs_patron_id' => '123',
    );

    // Check success.
    $options = array(
      'preferred_branch' => 123,
      'interest_period' => 30,
    );
    $res = $this->providerInvoke('update', $user, array('123'), $options);
    // No response is expected.
  }

  /**
   * Test reservation delete.
   */
  public function testDelete() {
    $this->provider = 'reservation';
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    $json_responses = array(
      // Don't expect anything other than an empty success reply.
      new Reply(),
    );
    $httpclient = $this->getHttpClient($json_responses);

    // Run through tests.
    $fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);

    $user = (object) array(
      'fbs_patron_id' => '123',
    );

    // Check success.
    $res = $this->providerInvoke('delete', $user, '123');
    // No response is expected. Which is good, as the service doesn't define
    // any error reponses either (apart from the catchal RestExecption).
  }
}
