<?php

/**
 * @file
 * Handles user reservations.
 */

/**
 * Implements provider reservation, list.
 */
function fbs_reservation_list($account) {
  $result = array(
    DING_RESERVATION_READY => array(),
    DING_RESERVATION_NOT_READY => array(),
    DING_RESERVATION_INTERLIBRARY_LOANS => array(),
  );

  $res = fbs_service()->Reservations->getReservations(fbs_service()->agencyId, fbs_patron_id($account));

  foreach ($res as $reservation) {
    // if $reservation->state == 'other' => DING_RESERVATION_NOT_READY.
    $type = $reservation->state == 'readyForPickup' ? DING_RESERVATION_READY : DING_RESERVATION_NOT_READY;
    $type = $reservation->state == 'interLibraryReservation' ? DING_RESERVATION_INTERLIBRARY_LOANS : $type;
    $ding_reservation = array(
      'ding_entity_id' => $reservation->recordId,
      'id' => $reservation->reservationId,
      'pickup_branch_id' => $reservation->pickupBranch,
      'created' => $reservation->dateOfReservation,
    );

    if ($type === DING_RESERVATION_READY) {
      $ding_reservation['pickup_date'] = $reservation->pickupDeadline;
    }

    else if ($type === DING_RESERVATION_NOT_READY) {
      $ding_reservation['queue_number'] = $reservation->numberInQueue;
    }

    if ($type === DING_RESERVATION_NOT_READY ||
        $type === DING_RESERVATION_INTERLIBRARY_LOANS) {
      $ding_reservation['expiry'] = $reservation->expiryDate;
    }

    $result[$type][$ding_reservation['id']] = $ding_reservation;
  }

  return $result;
}

/**
 * Implements provider reservation, create.
 */
function fbs_reservation_create($account, $record_ids, $options) {
  $batch = new FBS\Model\CreateReservationBatch();
  $batch->reservations = array();
  foreach ($record_ids as $record_id) {
    $reservation = new FBS\Model\CreateReservation();
    $reservation->recordId = $record_id;
    $reservation->expiryDate = date('Y-m-d', REQUEST_TIME + ($options['interest_period'] * 24 * 60 * 60));
    $reservation->pickupBranch = $options['preferred_branch'];
    $batch->reservations[] = $reservation;
  }
  $res = fbs_service()->Reservations->addReservations(fbs_service()->agencyId, fbs_patron_id($account), $batch);
}

/**
 * Implements provider reservation, delete.
 */
function fbs_reservation_update($account, $reservation_ids, $options) {
  $batch = new FBS\Model\UpdateReservationBatch();
  $batch->reservations = array();
  foreach ($reservation_ids as $reservation_id) {
    $reservation = new FBS\Model\UpdateReservation();
    $reservation->reservationId = $reservation_id;
    $reservation->expiryDate = date('Y-m-d', REQUEST_TIME + ($options['interest_period'] * 24 * 60 * 60));
    $reservation->pickupBranch = $options['preferred_branch'];
    $batch->reservations[] = $reservation;
  }
  $res = fbs_service()->Reservations->updateReservations(fbs_service()->agencyId, fbs_patron_id($account), $batch);
}

/**
 * Implements provider reservation, delete.
 */
function fbs_reservation_delete($account, $reservation_id) {
  $res = fbs_service()->Reservations->deleteReservations(fbs_service()->agencyId, fbs_patron_id($account), $reservation_id);
}
