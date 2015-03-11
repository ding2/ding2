<?php

/**
 * @file
 * Handles user reservations.
 */

/**
 * Implements provider reservation, list.
 */
function fbs_reservation_list($account, $requested_type = NULL) {
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
      'expiry' => $reservation->expiryDate,
    );

    if ($type === DING_RESERVATION_READY) {
      $ding_reservation['pickup_date'] = $reservation->pickupDeadline;
    }
    elseif ($type === DING_RESERVATION_NOT_READY || $type === DING_RESERVATION_INTERLIBRARY_LOANS) {
      $ding_reservation['queue_number'] = $reservation->numberInQueue;
    }

    $result[$type][$ding_reservation['id']] = $ding_reservation;
  }

  if ($requested_type) {
    if (isset($result[$requested_type])) {
      return $result[$requested_type];
    }
    else {
      watchdog('fbs', 'Unknown reservation type (%type) requested', array('%type' => $type), WATCHDOG_ERROR);
      return array();
    }
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

/**
 * Implements provider reservation, reservation_deletion_enabled.
 *
 * Check where reservation deletion have been enabled in the providers settings.
 */
function fbs_reservation_reservation_deletion_enabled() {
  return variable_get('fbs_enable_reservation_deletion', FALSE);
}

/**
 * Implements provider reservation, branch_name.
 */
function fbs_reservation_branch_name($branch_id) {
  $res = fbs_service()->Placement->getBranches(fbs_service()->agencyId);
  foreach ($res as $branch) {
    if ($branch->branchId == $branch_id) {
      return $branch->title;
    }
  }

  return NULL;
}

/**
 * Implements provider reservation, default_options.
 */
function fbs_reservation_default_options($account) {
  $creds = fbs_get_creds($account);
  return array(
    'preferred_branch' => $creds['preferred_branch'],
    'interest_period' => $creds['interest_period'],
  );
}

/**
 * Implements provider reservation, options.
 */
function fbs_reservation_options($account, $default_branch) {
  $creds = fbs_get_creds($account);

  $interest_period = $creds['interest_period'];
  $preferred_branch = empty($default_branch) ? $creds['preferred_branch'] : $default_branch;

  $form = array();
  $form += ding_reservation_default_options_branch('preferred_branch', $preferred_branch, fbs_branches());
  $form += ding_reservation_interest_period_selector('interest_period', $interest_period, fbs_interest_periods());

  return $form;
}
