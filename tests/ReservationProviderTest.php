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
 * DingProviderLoan::__construct() calls this, mock it.
 */
// function t($str) {
//   return $str;
// }

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
            'pickupBranch' => '113',
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
            'pickupBranch' => '113',
            'expiryDate' => '2015-10-30',
            'reservationId' => 48,
            'pickupDeadline' => '',
            'dateOfReservation' => '2015-01-10',
            'state' => 'reserved',
            'numberInQueue' => 2,
          ),
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:05197074',
            'pickupBranch' => '113',
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
      DING_RESERVATION_READY => array(
        45 => array(
          'ding_entity_id' => '870970-basis:42355089',
          'id' => 45,
          'pickup_date' => '2015-04-30',
          'pickup_branch_id' => 113,
          'created' => '2015-01-30',
        ),
      ),
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
      DING_RESERVATION_INTERLIBRARY_LOANS => array(),

    );
    $this->assertEquals($expected, $res);


  }
}
