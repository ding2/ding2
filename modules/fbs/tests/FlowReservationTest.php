<?php

/**
 * @file
 * Test reservation flows.
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

/**
 * Some provider functions uses this.
 */
if (!defined('REQUEST_TIME')) {
  define('REQUEST_TIME', time());
}

/**
 * Test user provider functions.
 */
class FlowReservationTest extends ProviderTestCase {

  /**
   * Test reservation creation flow.
   *
   * Testgroup F1
   * Issue DDBFBS-30.
   *
   * @group flow
   */
  public function testCreation() {
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    // Step 1
    // Login first.
    $json_responses = array(
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1946-03-19',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'København',
              'street' => 'Alhambravej 1',
              'postalCode' => '1826',
            ),
            // ISIL of Vesterbro bibliotek
            'preferredPickupBranch' => '113',
            'onHold' => NULL,
            'patronId' => 234143,
            'recieveEmail' => TRUE,
            'blockStatus' => NULL,
            'recieveSms' => FALSE,
            'emailAddress' => 'onkel@danny.dk',
            'phoneNumber' => '80345210',
            'name' => 'Dan Turrell',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => 30,
            'resident' => TRUE,
          ),
        )
      )
    );

    $this->replies($json_responses);

    $this->provider = 'user';
    $res = $this->providerInvoke('authenticate', '151019463013', '1234');

    $this->assertTrue($res['success']);
    $this->assertTrue(!empty($res['creds']['patronId']));

    $patron_id = $res['creds']['patronId'];
    $user = (object) array('creds' => $res['creds']);

    // Step 2
    // Now, get availability for something.
    // The record we'll try to reserve.
    $record_id = 'REC1';
    $json_responses = array(
      new Reply(
        array(
          array(
            'recordId' => $record_id,
            'available' => FALSE,
            'reservable' => TRUE,
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'availability';
    $res = $this->providerInvoke('items', array($record_id));

    $this->assertCount(1, $res);
    $this->assertArrayHasKey($record_id, $res);
    $this->assertTrue($res[$record_id]['reservable']);

    // Step 3
    // Looking at the material triggers a call to holdings, so we'll call that
    // too.
    $json_responses = array(
      new Reply(
        array(
          array(
            // HoldingsForBibliographicalRecord.
            'recordId' => $record_id,
            'reservable' => TRUE,
            'holdings' => array(
              array(
                // Holding.
                'materials' => array(
                  array(
                    // Material.
                    'itemNumber' => '1',
                    'available' => FALSE,
                    'materialGroupName' => 'Material group',
                  ),
                  array(
                    // Material.
                    'itemNumber' => '2',
                    'available' => TRUE,
                    'materialGroupName' => 'Material group',
                  ),
                  array(
                    // Material.
                    'itemNumber' => '3',
                    'available' => TRUE,
                    'materialGroupName' => 'Material group',
                  ),
                ),
                'branch' => array(
                  // AgencyBranch.
                  'branchId' => 'BRA1',
                  'title' => 'TBRA1',
                ),
                'department' => array(
                  // AgencyDepartment.
                  'departmentId' => 'DEP1',
                  'title' => 'TDEP1',
                ),
                'location' => array(
                  // AgencyLocation.
                  'locationId' => 'LOC1',
                  'title' => 'TLOC1',
                ),
                'sublocation' => array(
                  // AgencySublocation.
                  'sublocationId' => 'SUB1',
                  'title' => 'TSUB1',
                ),
              ),
            ),
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'availability';
    $res = $this->providerInvoke('holdings', array($record_id));

    $this->assertCount(1, $res);
    $this->assertArrayHasKey($record_id, $res);
    $this->assertTrue($res[$record_id]['reservable']);
    // Save total available for later.
    $total_available = 0;
    foreach ($res[$record_id]['holdings'] as $holding) {
      $total_available += $holding['available_count'];
    }

    // Step 4
    // Create reservation.
    $expected_expiry = date('Y-m-d', (REQUEST_TIME + ($user->creds['interest_period'] * 24 * 60 * 60)));
    $expected_reservation_date = date('Y-m-d', REQUEST_TIME);
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails.
            'recordId' => $record_id,
            'pickupBranch' => 123,
            'expiryDate' => $expected_expiry,
            'reservationId' => 123,
            'pickupDeadline' => NULL,
            'dateOfReservation' => $expected_reservation_date,
            'state' => 'reserved',
            'numberInQueue' => 3,
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'reservation';
    $options = array(
      'interest_period' => $user->creds['interest_period'],
      'preferred_branch' => $user->creds['preferred_branch'],
    );
    $this->providerInvoke('create', $user, array($record_id), $options);
    // Create returns no result, so we can't check anything.

    // Step 5
    // Check that the material is on our reservation list.
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails: MAT16
            'recordId' => $record_id,
            'pickupBranch' => $user->creds['preferred_branch'],
            'expiryDate' => $expected_expiry,
            'reservationId' => 16,
            'dateOfReservation' => $expected_reservation_date,
            'numberInQueue' => 1,
            'state' => 'reserved',
          ),
        )
      ),
    );

    $this->replies($json_responses);
    // We assume that our just created reservation wont be ready for pickup.
    $res = $this->providerInvoke('list', $user, DING_RESERVATION_NOT_READY);

    // Must be one..
    $this->assertGreaterThanOrEqual(1, count($res));
    $reservation = NULL;
    foreach ($res as $item) {
      if ($item['ding_entity_id'] == $record_id) {
        $reservation = $item;
        break;
      }
    }
    $this->assertNotNull($reservation);
    $this->assertEquals($expected_reservation_date, $reservation['created']);
    $this->assertEquals($user->creds['preferred_branch'], $reservation['pickup_branch_id']);
    $this->assertEquals($expected_expiry, $reservation['expiry']);

    // Step 6
    // Check that the holdings have updated.
    $json_responses = array(
      new Reply(
        array(
          array(
            // HoldingsForBibliographicalRecord.
            'recordId' => $record_id,
            'reservable' => TRUE,
            'holdings' => array(
              array(
                // Holding.
                'materials' => array(
                  array(
                    // Material.
                    'itemNumber' => '1',
                    'available' => FALSE,
                    'materialGroupName' => 'Material group',
                  ),
                  array(
                    // Material.
                    'itemNumber' => '2',
                    'available' => FALSE,
                    'materialGroupName' => 'Material group',
                  ),
                  array(
                    // Material.
                    'itemNumber' => '3',
                    'available' => TRUE,
                    'materialGroupName' => 'Material group',
                  ),
                ),
                'branch' => array(
                  // AgencyBranch.
                  'branchId' => 'BRA1',
                  'title' => 'TBRA1',
                ),
                'department' => array(
                  // AgencyDepartment.
                  'departmentId' => 'DEP1',
                  'title' => 'TDEP1',
                ),
                'location' => array(
                  // AgencyLocation.
                  'locationId' => 'LOC1',
                  'title' => 'TLOC1',
                ),
                'sublocation' => array(
                  // AgencySublocation.
                  'sublocationId' => 'SUB1',
                  'title' => 'TSUB1',
                ),
              ),
            ),
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'availability';
    $res = $this->providerInvoke('holdings', array($record_id));

    $this->assertCount(1, $res);
    $this->assertArrayHasKey($record_id, $res);
    // Check that available count has decreased.
    $available = 0;
    foreach ($res[$record_id]['holdings'] as $holding) {
      $available += $holding['available_count'];
    }
    $this->assertEquals($total_available - 1, $available);
  }

  /**
   * Test reservation update flow.
   *
   * Testgroup F2
   * Issue DDBFBS-31.
   *
   * @group flow
   */
  public function testUpdate() {
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    // Step 1
    // Login first.
    $json_responses = array(
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1946-03-19',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'København',
              'street' => 'Alhambravej 1',
              'postalCode' => '1826',
            ),
            // ISIL of Vesterbro bibliotek
            'preferredPickupBranch' => '113',
            'onHold' => NULL,
            'patronId' => 234143,
            'recieveEmail' => TRUE,
            'blockStatus' => NULL,
            'recieveSms' => FALSE,
            'emailAddress' => 'onkel@danny.dk',
            'phoneNumber' => '80345210',
            'name' => 'Dan Turrell',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => 30,
            'resident' => TRUE,
          ),
        )
      ),
    );

    $this->replies($json_responses);

    $this->provider = 'user';
    $res = $this->providerInvoke('authenticate', '151019463013', '1234');

    $this->assertTrue($res['success']);
    $this->assertTrue(!empty($res['creds']['patronId']));

    $patron_id = $res['creds']['patronId'];
    $user = (object) array('creds' => $res['creds']);

    // Step 2
    // Check the existing values for an existing reservation.
    $record_id = 'REC1';
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails: MAT16
            'recordId' => $record_id,
            'pickupBranch' => '113',
            'expiryDate' => '2015-03-16',
            'reservationId' => 16,
            'dateOfReservation' => '2015-02-16',
            'numberInQueue' => 1,
            'state' => 'reserved',
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'reservation';
    $res = $this->providerInvoke('list', $user, DING_RESERVATION_NOT_READY);

    // Must be one..
    $this->assertGreaterThanOrEqual(1, count($res));
    $reservation = NULL;
    foreach ($res as $item) {
      if ($item['ding_entity_id'] == $record_id) {
        $reservation = $item;
        break;
      }
    }
    $this->assertNotNull($reservation);

    // Step 3
    // Update reservation.
    $expected_branch = 123;
    $expected_expiry = date('Y-m-d', (REQUEST_TIME + 24 * 60 * 60 * 17));
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails.
            'recordId' => $record_id,
            'pickupBranch' => 123,
            'expiryDate' => $expected_expiry,
            'reservationId' => 16,
            'pickupDeadline' => NULL,
            'dateOfReservation' => '2015-02-16',
            'state' => 'reserved',
            'numberInQueue' => 1,
          ),
        )
      ),
    );
    // Check success.
    $options = array(
      'preferred_branch' => 123,
      'interest_period' => 17,
    );
    $this->replies($json_responses);
    $this->provider = 'reservation';
    $res = $this->providerInvoke('update', $user, array('123'), $options);
    // No response is expected.

    // Step 4
    // Check that the reservation was updated.
    $record_id = 'REC1';
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails: MAT16
            'recordId' => $record_id,
            'pickupBranch' => $expected_branch,
            'expiryDate' => $expected_expiry,
            'reservationId' => 16,
            'dateOfReservation' => '2015-02-16',
            'numberInQueue' => 1,
            'state' => 'reserved',
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'reservation';
    $res = $this->providerInvoke('list', $user, DING_RESERVATION_NOT_READY);

    // Must be one..
    $this->assertGreaterThanOrEqual(1, count($res));
    $reservation = NULL;
    foreach ($res as $item) {
      if ($item['ding_entity_id'] == $record_id) {
        $reservation = $item;
        break;
      }
    }
    $this->assertNotNull($reservation);
    $this->assertEquals($expected_branch, $reservation['pickup_branch_id']);
    $this->assertEquals($expected_expiry, $reservation['expiry']);
  }

  /**
   * Test reservation deletion flow.
   *
   * Testgroup F3
   * Issue DDBFBS-32.
   *
   * @group flow
   */
  public function testDelete() {
    // // Define DING_RESERVATION_* constants..
    $this->requireDing('ding_reservation', 'ding_reservation.module');

    // Step 1
    // Login first.
    $json_responses = array(
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1946-03-19',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'København',
              'street' => 'Alhambravej 1',
              'postalCode' => '1826',
            ),
            // ISIL of Vesterbro bibliotek
            'preferredPickupBranch' => '113',
            'onHold' => NULL,
            'patronId' => 234143,
            'recieveEmail' => TRUE,
            'blockStatus' => NULL,
            'recieveSms' => FALSE,
            'emailAddress' => 'onkel@danny.dk',
            'phoneNumber' => '80345210',
            'name' => 'Dan Turrell',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => 30,
            'resident' => TRUE,
          ),
        )
      ),
    );

    $this->replies($json_responses);

    $this->provider = 'user';
    $res = $this->providerInvoke('authenticate', '151019463013', '1234');

    $this->assertTrue($res['success']);
    $this->assertTrue(!empty($res['creds']['patronId']));

    $patron_id = $res['creds']['patronId'];
    $user = (object) array('creds' => $res['creds']);

    // Step 2
    // Check the existing values for an existing reservation.
    $record_id = 'REC1';
    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // ReservationDetails: MAT16
            'recordId' => $record_id,
            'pickupBranch' => '113',
            'expiryDate' => '2015-03-16',
            'reservationId' => 16,
            'dateOfReservation' => '2015-02-16',
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
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'reservation';
    $res = $this->providerInvoke('list', $user);

    // Create one big array of all reservations.
    $reservations = array_merge($res[DING_RESERVATION_READY], $res[DING_RESERVATION_NOT_READY], $res[DING_RESERVATION_INTERLIBRARY_LOANS]);

    // Must be one..
    $this->assertGreaterThanOrEqual(1, count($res));
    $reservation = NULL;
    foreach ($reservations as $item) {
      if ($item['ding_entity_id'] == $record_id) {
        $reservation = $item;
        break;
      }
    }
    $this->assertNotNull($reservation);

    // Step 3
    // Delete reservation.
    $json_responses = array(
      // Successful deletion returns an empty reply.
      new Reply(
      ),
    );
    $this->replies($json_responses);
    $this->provider = 'reservation';
    $res = $this->providerInvoke('delete', $user, $reservation['id']);
    // No response is expected.

    // Step 4
    // Check that the reservation was updated.
    $record_id = 'REC1';
    $json_responses = array(
      new Reply(
        array(
          // Array of...
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
        )
      ),
    );

    $this->replies($json_responses);
    $this->provider = 'reservation';
    $res = $this->providerInvoke('list', $user);
    // Create one big array of all reservations.
    $reservations = array_merge($res[DING_RESERVATION_READY], $res[DING_RESERVATION_NOT_READY], $res[DING_RESERVATION_INTERLIBRARY_LOANS]);
    // Must be one..
    $this->assertGreaterThanOrEqual(1, count($res));
    $reservation = NULL;
    // Check that none of the reservations match the record_id nor the
    // reservation_id of the deleted reservation.
    foreach ($reservations as $item) {
      $this->assertNotEquals($record_id, $item['ding_entity_id']);
      $this->assertNotEquals($reservation['id'], $item['id']);
    }
  }
}
