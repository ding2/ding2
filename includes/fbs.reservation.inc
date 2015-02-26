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
    $type = $reservation->state == 'readyForPickup' ? DING_RESERVATION_READY : DING_RESERVATION_NOT_READY;
    $ding_reservation = array(
      'ding_entity_id' => $reservation->recordId,
      'id' => $reservation->reservationId,
      'pickup_branch_id' => $reservation->pickupBranch,
      'created' => $reservation->dateOfReservation,
    );

    if ($type === DING_RESERVATION_READY) {
      $ding_reservation['pickup_date'] = $reservation->pickupDeadline;
    }

    if ($type === DING_RESERVATION_NOT_READY) {
      $ding_reservation['queue_number'] = $reservation->numberInQueue;
      $ding_reservation['expiry'] = $reservation->expiryDate;
    }

    $result[$type][$ding_reservation['id']] = $ding_reservation;

  }

  return $result;
}
