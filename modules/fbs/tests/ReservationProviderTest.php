<?php

/**
 * @file
 * Test reservation provider functions.
 */

require_once "ProviderTestCase.php";
require_once dirname(__DIR__) . '/vendor/autoload.php';

if (!function_exists('ding_provider_build_entity_id')) {
  /**
   * Loan list calls this, mock it.
   */
  function ding_provider_build_entity_id($id, $agency = '') {
    return $id . ($agency ? ":" . $agency : '');
  }
}

if (!function_exists('t')) {
  /**
   * DingProviderLoan::__construct() calls this, mock it.
   */
  function t($str, $replace = array()) {
    return strtr($str, $replace);
  }
}

/**
 * Some provider functions uses this.
 */
if (!defined('REQUEST_TIME')) {
  define('REQUEST_TIME', time());
}

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

    // Reusable response.
    /**$tcrl7 = new Reply(
      array(
        array(
          // ReservationDetails: MAT16
          'recordId' => 'REC16',
          'pickupBranch' => 'BRA1',
          'expiryDate' => 'EXPDATE16',
          'reservationId' => 16,
          'dateOfReservation' => 'RESDATE16',
          'numberInQueue' => 1,
          'state' => 'reserved',
        ),
        array(
          // ReservationDetails: MAT17
          'recordId' => 'REC17',
          'pickupBranch' => 'BRA1',
          'expiryDate' => 'EXPDATE17',
          'reservationId' => 17,
          'dateOfReservation' => 'RESDATE17',
          'pickupDeadline' => 'PICKUP17',
          'numberInQueue' => 1, // Not expected
          'state' => 'readyForPickup',
        ),
        array(
          // ReservationDetails: MAT18
          'recordId' => 'REC18',
          'pickupBranch' => 'BRA1',
          'expiryDate' => 'EXPDATE18',
          'reservationId' => 18,
          'dateOfReservation' => 'RESDATE18',
          'numberInQueue' => 1,
          'state' => 'interLibraryReservation',
        ),
        array(
          // ReservationDetails: Mat19
          'recordId' => 'REC19',
          'pickupBranch' => 'BRA1',
          'expiryDate' => 'EXPDATE19',
          'reservationId' => 19,
          'dateOfReservation' => 'RESDATE19',
          'numberInQueue' => 0,  // Expected?
          'state' => 'other',
        ),
        array(
          // ReservationDetails: MAT20
          'recordId' => 'REC20',
          'pickupBranch' => 'BRA1',
          'expiryDate' => 'EXPDATE20',
          'reservationId' => 20,
          'dateOfReservation' => 'RESDATE20',
          'numberInQueue' => 1,
          'state' => 'reserved',
        ),
        array(
          // ReservationDetails: MAT21
          'recordId' => 'REC21',
          'pickupBranch' => 'BRA1',
          'expiryDate' => 'EXPDATE21',
          'reservationId' => 21,
          'dateOfReservation' => 'RESDATE21',
          'pickupDeadline' => 'PICKUP21',
          'state' => 'readyForPickup',
        ),
        array(
          // ReservationDetails: MAT22
          'recordId' => 'REC22',
          'pickupBranch' => 'BRA1',
          'expiryDate' => 'EXPDATE22',
          'reservationId' => 22,
          'dateOfReservation' => 'RESDATE22',
          'numberInQueue' => 1,
          'state' => 'interLibraryReservation',
        ),
      )
    ); **/

    $json_responses = array(
      // TCRL1: Return empty result for patron PAT1 without reservations
      new Reply(
        array()
      ),
      // TCRL2: Return single result for patron PAT2 with one reservation (MAT11)
      new Reply(
        array(
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:06338909',
            'pickupBranch' => 'DK-761500',
            'expiryDate' => '2015-09-26',
            'reservationId' => 158,
            'dateOfReservation' => '2015-03-30T13:56:30.334',
            'numberInQueue' => 2,
            'state' => 'reserved',
          ),
        )
      ),
      // TCRL3: Return empty result for patron PAT3 with expired reservation (MAT12)
      /**new Reply(
        array()
      ),**/
      // TCRL4: Return single result for patron PAT4 with interlibrary reservation (MAT13)
      /**new Reply(
        array(
          array(
            // ReservationDetails.
            'recordId' => 'REC13',
            'pickupBranch' => 'BRA1',
            'expiryDate' => 'EXPDATE13',
            'reservationId' => 13,
            'dateOfReservation' => 'RESDATE13',
            'state' => 'interLibraryReservation',
            'numberInQueue' => 1,
          ),
        )
      ),**/
      // TCRL5: Return single result for patron PAT5 with reservation ready for pickup (MAT14)
      new Reply(
        array(
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:26515297',
            'pickupBranch' => 'DK-761500',
            'expiryDate' => '2015-09-26',
            'reservationId' => 160,
            'pickupDeadline' => '2015-04-06',
            'dateOfReservation' => '2015-03-30T14:47:45.711',
            'state' => 'readyForPickup',
            // afhentningsnummer?
          ),
        )
      ),
      // TCRL6: Return single result for patron PAT6 with reservation with status=other (MAT15)
      /**new Reply(
        array(
          array(
            // ReservationDetails.
            'recordId' => 'REC15',
            'pickupBranch' => 'BRA1',
            'expiryDate' => 'EXPDATE15',
            'reservationId' => 15,
            'dateOfReservation' => 'RESDATE15',
            'state' => 'other',
            'numberInQueue' => 0, // Skal ikke være på state=other
          ),
        )
      ),**/
      // TCRL7: Return multiple results for patron PAT7 with reservations with different types
      //        (MAT16, MAT17, MAT18, MAT19, MAT20, MAT21, MAT22)
      //$tcrl7,
      //$tcrl7,
    );

    $this->replies($json_responses);

    // TCRL1: Patron PAT1 without reservations
    $patron1 = (object) array(
      'creds' => array('patronId' => 72)
    );

    $res = $this->providerInvoke('list', $patron1);
    $expected = array(
      DING_RESERVATION_READY => array(),
      DING_RESERVATION_NOT_READY => array(),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(),
    );
    $this->assertEquals($expected, $res);


    // TCRL2: Patron PAT2 with a single reservation
    $patron2 = (object) array(
      'creds' => array('patronId' => 73)
    );

    $res = $this->providerInvoke('list', $patron2);
    $expected = array(
      DING_RESERVATION_READY => array(),
      // Reserved
      DING_RESERVATION_NOT_READY => array(
        158 => array(
          'ding_entity_id' => '870970-basis:06338909',
          'id' => 158,
          'pickup_branch_id' => 'DK-761500',
          'created' => '2015-03-30T13:56:30.334',
          'queue_number' => 2,
          'expiry' => '2015-09-26',
        ),
      ),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(),
    );
    $this->assertEquals($expected, $res);


    // TCRL3: Patron with expired reservation
    /**$patron3 = (object) array(
      'creds' => array('patronId' => 'PATID3')
    );

    $res = $this->providerInvoke('list', $patron3);
    $expected = array(
      DING_RESERVATION_READY => array(),
      DING_RESERVATION_NOT_READY => array(),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(),
    );
    $this->assertEquals($expected, $res);
**/

    // TCRL4: Patron PAT4 with interlibrary reservation
    /**$patron4 = (object) array(
      'creds' => array('patronId' => 75)
    );

    $res = $this->providerInvoke('list', $patron4);
    $expected = array(
      DING_RESERVATION_READY => array(),
      DING_RESERVATION_NOT_READY => array(),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(
        13 => array(
          'ding_entity_id' => 'REC13',
          'id' => 13,
          'pickup_branch_id' => 'BRA1',
          'created' => 'RESDATE13',
          'expiry' => 'EXPDATE13',
          'queue_number' => 1,
        ),
      ),
    );
    $this->assertEquals($expected, $res);
**/

    // TCRL5: Patron PAT5 with reservation ready for pickup
    $patron5 = (object) array(
      'creds' => array('patronId' => 76)
    );

    $res = $this->providerInvoke('list', $patron5);
    $expected = array(
      DING_RESERVATION_READY => array(
        160 => array(
          'ding_entity_id' => '870970-basis:26515297',
          'id' => 160,
          'pickup_branch_id' => 'DK-761500',
          'pickup_date' => '2015-04-06',
          'created' => '2015-03-30T14:47:45.711',
          'expiry' => '2015-09-26',
        ),
      ),
      DING_RESERVATION_NOT_READY => array(),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(),
    );
    $this->assertEquals($expected, $res);


    // TCRL6: Patron with reservation with status=other
    /**$patron6 = (object) array(
      'creds' => array('patronId' => 'PATID6')
    );

    $res = $this->providerInvoke('list', $patron6);
    $expected = array(
      DING_RESERVATION_READY => array(),
      DING_RESERVATION_NOT_READY => array(
        15 => array(
          'ding_entity_id' => 'REC15',
          'id' => 15,
          'pickup_branch_id' => 'BRA1',
          'created' => 'RESDATE15',
          'expiry' => 'EXPDATE15',
          'queue_number' => 0, // kan ikke forvente den er her på en state=other reservering
        ),
      ),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(),
    );
    $this->assertEquals($expected, $res);
**/

    // TCRL7: Patron with muliple reservations with different types
    /**$patron7 = (object) array(
      'creds' => array('patronId' => 'PATID7')
    );

    // Check success.
    $res = $this->providerInvoke('list', $patron7);
    $expected = array(
      DING_RESERVATION_READY => array(
        17 => array(
          'ding_entity_id' => 'REC17',
          'id' => 17,
          'pickup_branch_id' => 'BRA1',
          'pickup_date' => 'PICKUP17',
          'created' => 'RESDATE17',
          'expiry' => 'EXPDATE17',
        ),
        21 => array(
          'ding_entity_id' => 'REC21',
          'id' => 21,
          'pickup_branch_id' => 'BRA1',
          'pickup_date' => 'PICKUP21',
          'created' => 'RESDATE21',
          'expiry' => 'EXPDATE21',
        ),
      ),
      DING_RESERVATION_NOT_READY => array(
        16 => array(
          'ding_entity_id' => 'REC16',
          'id' => 16,
          'pickup_branch_id' => 'BRA1',
          'created' => 'RESDATE16',
          'queue_number' => 1,
          'expiry' => 'EXPDATE16',
        ),
         19=> array(
          'ding_entity_id' => 'REC19',
          'id' => 19,
          'pickup_branch_id' => 'BRA1',
          'created' => 'RESDATE19',
          'expiry' => 'EXPDATE19',
          'queue_number' => 0, // kan ikke forvente den er her på en state=other reservering
        ),
        20 => array(
          'ding_entity_id' => 'REC20',
          'id' => 20,
          'pickup_branch_id' => 'BRA1',
          'created' => 'RESDATE20',
          'queue_number' => 1,
          'expiry' => 'EXPDATE20',
        ),
      ),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(
        18 => array(
          'ding_entity_id' => 'REC18',
          'id' => 18,
          'pickup_branch_id' => 'BRA1',
          'created' => 'RESDATE18',
          'expiry' => 'EXPDATE18',
          'queue_number' => 1,
        ),
        22 => array(
          'ding_entity_id' => 'REC22',
          'id' => 22,
          'pickup_branch_id' => 'BRA1',
          'created' => 'RESDATE22',
          'expiry' => 'EXPDATE22',
          'queue_number' => 1,
        ),
      ),
    );
    $this->assertEquals($expected, $res);
**/
    // Check that requesting a specific list returns just that.
    /**$res = $this->providerInvoke('list', $patron7, DING_RESERVATION_NOT_READY);
    $expected = array(
      16 => array(
        'ding_entity_id' => 'REC16',
        'id' => 16,
        'pickup_branch_id' => 'BRA1',
        'created' => 'RESDATE16',
        'queue_number' => 1,
        'expiry' => 'EXPDATE16',
      ),
      19=> array(
        'ding_entity_id' => 'REC19',
        'id' => 19,
        'pickup_branch_id' => 'BRA1',
        'created' => 'RESDATE19',
        'expiry' => 'EXPDATE19',
        'queue_number' => 0, // kan ikke forvente den er her på en state=other reservering
      ),
      20 => array(
        'ding_entity_id' => 'REC20',
        'id' => 20,
        'pickup_branch_id' => 'BRA1',
        'created' => 'RESDATE20',
        'queue_number' => 1,
        'expiry' => 'EXPDATE20',
      ),
    );
    $this->assertEquals($expected, $res);
    **/

    // Few tests to test periodical rendering.
    $json_responses = array(
      new Reply(
        array(
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:06338909',
            'pickupBranch' => 'DK-761500',
            'expiryDate' => '2015-09-26',
            'reservationId' => 158,
            'dateOfReservation' => '2015-03-30T13:56:30.334',
            'periodical' => array(
              // Periodical.
              'volume' => 2,
              'volumeYear' => 2011,
              'volumeNumber' => 3,

            ),
            'numberInQueue' => 2,
            'state' => 'reserved',
          ),
          array(
            // ReservationDetails.
            'recordId' => '870970-basis:06338910',
            'pickupBranch' => 'DK-761500',
            'expiryDate' => '2015-09-26',
            'reservationId' => 159,
            'dateOfReservation' => '2015-03-30T13:56:30.334',
            'periodical' => array(
              // Periodical.
              'volume' => 4,
              'volumeYear' => NULL,
              'volumeNumber' => NULL,

            ),
            'numberInQueue' => 2,
            'state' => 'reserved',
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $patron = (object) array(
      'creds' => array('patronId' => 73)
    );

    $res = $this->providerInvoke('list', $patron);
    $expected = array(
      DING_RESERVATION_READY => array(),
      // Reserved
      DING_RESERVATION_NOT_READY => array(
        158 => array(
          'ding_entity_id' => '870970-basis:06338909',
          'id' => 158,
          'pickup_branch_id' => 'DK-761500',
          'created' => '2015-03-30T13:56:30.334',
          'queue_number' => 2,
          'expiry' => '2015-09-26',
          'notes' => 'Issue 2.3, 2011',
        ),
        159 => array(
          'ding_entity_id' => '870970-basis:06338910',
          'id' => 159,
          'pickup_branch_id' => 'DK-761500',
          'created' => '2015-03-30T13:56:30.334',
          'queue_number' => 2,
          'expiry' => '2015-09-26',
          'notes' => 'Issue 4',
        ),
      ),
      DING_RESERVATION_INTERLIBRARY_LOANS => array(),
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
    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array('patronId' => 'PATID8')
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
            'periodical' => array(
              // Periodical.
              'volume' => 2,
              'volumeYear' => 2011,
              'volumeNumber' => 3,
            ),
          ),
        )
      ),
    );
    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array('patronId' => 'PATID8')
    );

    // Check success.

    $reservation_ids = array(
      'fbs-2:2011:3:870970-basis::50717437',
    );
    $options = array(
      'preferred_branch' => 123,
      'interest_period' => 30,
    );
    $res = $this->providerInvoke('create', $user, $reservation_ids, $options);
    // No response is expected, but we'll expect things to blow up if it
    // doesn't understand the given id.
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
    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array('patronId' => 'PATID8')
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
    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array('patronId' => 'PATID8')
    );

    // Check success.
    $res = $this->providerInvoke('delete', $user, '123');
    // No response is expected. Which is good, as the service doesn't define
    // any error reponses either (apart from the catchall RestExecption).

  }

  /**
   * Test reservation branch_name.
   */
  public function testBranchName() {
    $this->provider = 'reservation';
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    $standard_reply = new Reply(
        array(
          // Array of...
           array(
            // AgencyBranch.
            'branchId' => 'DK-761500',
            'title' => 'Horsens Bibliotek',
          ),
          array(
            // AgencyBranch.
            'branchId' => 'DK-761501',
            'title' => 'Brædstrup Bibliotek',
          ),
          array(
            // AgencyBranch.
            'branchId' => 'DK-761502',
            'title' => 'Endelave Bibliotek',
          ),
          array(
            // AgencyBranch.
            'branchId' => 'DK-761503',
            'title' => 'Hovedgård Bibliotek',
          ),
          array(
            // AgencyBranch.
            'branchId' => 'DK-761504',
            'title' => 'Gedved Bibliotek',
          ),
          array(
            // AgencyBranch.
            'branchId' => 'DK-761505',
            'title' => 'Østbirk Bibliotek',
          ),
          array(
            // AgencyBranch.
            'branchId' => 'DK-761506',
            'title' => 'Søvind Bibliotek',
          ),
        )
      );

    $json_responses = array(
      $standard_reply,
      $standard_reply,
      $standard_reply,
      $standard_reply,
      $standard_reply,
      $standard_reply,
      $standard_reply,
      $standard_reply
    );
    $this->replies($json_responses);

    // Check success.
    $this->assertEquals('Horsens Bibliotek', $this->providerInvoke('branch_name', 'DK-761500'));
    $this->assertEquals('Brædstrup Bibliotek', $this->providerInvoke('branch_name', 'DK-761501'));
    $this->assertEquals('Endelave Bibliotek', $this->providerInvoke('branch_name', 'DK-761502'));
    $this->assertEquals('Hovedgård Bibliotek', $this->providerInvoke('branch_name', 'DK-761503'));
    $this->assertEquals('Gedved Bibliotek', $this->providerInvoke('branch_name', 'DK-761504'));
    $this->assertEquals('Østbirk Bibliotek', $this->providerInvoke('branch_name', 'DK-761505'));
    $this->assertEquals('Søvind Bibliotek', $this->providerInvoke('branch_name', 'DK-761506'));
    // Check that unknown returns NULL.
    $this->assertNull($this->providerInvoke('branch_name', '152'));
  }

  /**
   * Test reservation branch_name.
   */
  public function testDefaultOptions() {
    $this->provider = 'reservation';
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    // We don't expect any calls to the service.
    $json_responses = array();
    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array(
        'patronId' => 123,
        'name' => 'Dan Turell',
        'phone' => '',
        'mail' => '',
        'phone_notification' => TRUE,
        'mail_notification' => FALSE,
        'preferred_branch' => 113,
        'interest_period' => 30,
      )
    );

    // Check success.
    $expected = array(
      'interest_period' => 30,
      'preferred_branch' => 113,
    );
    $this->assertEquals($expected, $this->providerInvoke('default_options', $user));
  }
}
