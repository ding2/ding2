<?php

/**
 * @file
 * Handles user reservations.
 */

/**
 * Implements provider reservation, list.
 *
 * @param object $account
 *   User to list reservations for.
 * @param string|null $requested_type
 *   Type of reservations to list. Null for all.
 *
 * @return array
 *   Reservation info.
 */
function fbs_reservation_list($account, $requested_type = NULL) {
  $res = array();
  try {
    $res = fbs_service()->Reservations->getReservations(fbs_service()->agencyId, fbs_patron_id($account));
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  $result = array(
    DING_RESERVATION_READY => array(),
    DING_RESERVATION_NOT_READY => array(),
    DING_RESERVATION_INTERLIBRARY_LOANS => array(),
  );
  foreach ($res as $reservation) {
    $type = $reservation->state == 'readyForPickup' ? DING_RESERVATION_READY : DING_RESERVATION_NOT_READY;
    $type = $reservation->state == 'interLibraryReservation' ? DING_RESERVATION_INTERLIBRARY_LOANS : $type;
    $ding_reservation = array(
      'ding_entity_id' => ding_provider_build_entity_id($reservation->recordId),
      'id' => $reservation->reservationId,
      'pickup_branch_id' => $reservation->pickupBranch,
      'created' => $reservation->dateOfReservation,
      'expiry' => $reservation->expiryDate,
      // Required by ding_reservation.
      'reservation_type' => $type,
    );

    if ($type === DING_RESERVATION_READY) {
      $ding_reservation['pickup_date'] = $reservation->pickupDeadline;
      $ding_reservation['pickup_order_id'] = $reservation->pickupNumber;
      $ding_reservation['order_arrived'] = TRUE;
    }
    elseif ($type === DING_RESERVATION_NOT_READY || $type === DING_RESERVATION_INTERLIBRARY_LOANS) {
      if (!empty($reservation->numberInQueue)) {
        $ding_reservation['queue_number'] = $reservation->numberInQueue;
      }
    }

    // Add in periodical information if it is one.
    if ($reservation->periodical) {
      $periodical = $reservation->periodical;
      $vol = $periodical->volume;
      if (!empty($periodical->volumeNumber)) {
        $vol .= '.' . $periodical->volumeNumber;
      }
      if (!empty($periodical->volumeYear)) {
        $ding_reservation['notes'] = t('Issue @vol, @year', array('@vol' => $vol, '@year' => $periodical->volumeYear));
      }
      else {
        $ding_reservation['notes'] = t('Issue @vol', array('@vol' => $vol));
      }
    }

    // Handle inter library loans.
    if (!empty($reservation->ilBibliographicRecord)) {
      $ding_reservation['display_name'] = $reservation->ilBibliographicRecord->title;
    }

    $result[$type][$ding_reservation['id']] = new DingProviderReservation($ding_reservation['id'], $ding_reservation);
  }

  // Filter the result based on the requested type of reservations.
  if ($requested_type) {
    if (isset($result[$requested_type])) {
      return $result[$requested_type];
    }
    else {
      watchdog('fbs', 'Unknown reservation type (%type) requested', array('%type' => $requested_type), WATCHDOG_ERROR);
      return array();
    }
  }

  return $result;
}

/**
 * Implements provider reservation, create.
 *
 * @param object $account
 *   User to reserve for.
 * @param string $record_ids
 *   Id of ting object to reserve.
 * @param array $options
 *   Reservation options.
 *
 */
function fbs_reservation_create($account, $record_id, $options) {
  $batch = new FBS\Model\CreateReservationBatch();
  $batch->reservations = array();

  $reservation = new FBS\Model\CreateReservation();
  // We use our own custom ids prefixed with "fbs-" for periodicals.
  if (preg_match('/^fbs-/', $record_id)) {
    list($record_id, $periodical) = _fbs_periodical_parse_local_id($record_id);
    $reservation->recordId = $record_id;
    $reservation->periodical = $periodical;
  }
  else {
    $reservation->recordId = $record_id;
  }

  $reservation->expiryDate = date('Y-m-d', REQUEST_TIME + ($options['interest_period'] * 24 * 60 * 60));
  $reservation->pickupBranch = $options['fbs_preferred_branch'];
  $batch->reservations[] = $reservation;

  /** @var \FBS\Model\ReservationResponse $response */
  $response = NULL;
  $result = NULL;
  try {
    $response = fbs_service()->Reservations->addReservations(fbs_service()->agencyId, fbs_patron_id($account), $batch);
    /** @var \FBS\Model\ReservationResult $result */
    $result = current($response->reservationResults);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  if (!empty($response->success)) {
    /** @var \FBS\Model\ReservationDetails $res_details */

    $res_details = $result->reservationDetails;
    return array(
      'branch' => $res_details->pickupBranch,
      'queue_number' => $res_details->numberInQueue,
    );
  }
  else {
    switch ($result->result) {
      case 'already_reserved':
        throw new DingProviderReservationExists();

      case 'patron_is_blocked':
      case 'loaning_profile_not_found':
      case 'patron_not_found':
        throw new DingProviderReservationNotAllowed();

      case 'material_not_loanable':
      case 'material_not_reservable':
      case 'material_lost':
      case 'material_not_found':
      case 'material_part_of_collection':
        throw new DingProviderReservationNotAvailable();

      // Success shouldn't happen.
      case 'success':
      default:
        watchdog('fbs', 'Unexpected state "@state" on failed reservaiton', array('@state' => $result->result), WATCHDOG_WARNING);
        throw new DingProviderUserException('Unknown error from library system while attempting to reserve.');
    };
  }
}

/**
 * Implements provider reservation, update.
 *
 * @param object $account
 *   User to update reservations for.
 * @param array $reservation_ids
 *   Reservations to update.
 * @param array $options
 *   Update options.
 */
function fbs_reservation_update($account, $reservation_ids, $options) {
  $batch = new FBS\Model\UpdateReservationBatch();
  $batch->reservations = array();
  foreach ($reservation_ids as $reservation_id) {
    $reservation = new FBS\Model\UpdateReservation();
    $reservation->reservationId = $reservation_id;
    $reservation->expiryDate = date('Y-m-d', REQUEST_TIME + ($options['interest_period'] * 24 * 60 * 60));
    $reservation->pickupBranch = $options['fbs_preferred_branch'];
    $batch->reservations[] = $reservation;
  }

  try {
    fbs_service()->Reservations->updateReservations(fbs_service()->agencyId, fbs_patron_id($account), $batch);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);

    return FALSE;
  }
}

/**
 * Implements provider reservation, delete.
 *
 * @param object $account
 *   User to delete reservations for.
 * @param array $reservation_ids
 *   Reservations to delete.
 */
function fbs_reservation_delete($account, $reservation_id) {
  try {
    fbs_service()->Reservations->deleteReservations(fbs_service()->agencyId, fbs_patron_id($account), $reservation_id);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);

    return FALSE;
  }
}

/**
 * Implements provider reservation, reservation_deletion_enabled.
 *
 * Check where reservation deletion have been enabled in the providers settings.
 *
 * @return bool
 *   Whether deletion is enabled.
 */
function fbs_reservation_reservation_deletion_enabled() {
  return variable_get('fbs_enable_reservation_deletion', FALSE);
}

/**
 * Implements provider reservation, branch_name.
 *
 * @param string $branch_id
 *   The branch id to look up.
 *
 * @return string|null
 *   The branch name or null if not found.
 */
function fbs_reservation_branch_name($branch_id) {
  $res = array();
  try {
    $res = fbs_service()->Placement->getBranches(fbs_service()->agencyId);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  foreach ($res as $branch) {
    if ($branch->branchId == $branch_id) {
      return $branch->title;
    }
  }

  return NULL;
}

/**
 * Implements provider reservation, default_options.
 *
 * @param object $account
 *   The user to get default options for.
 *
 * @return array
 *   The default options.
 */
function fbs_reservation_default_options($account) {
  $patron_info = fbs_get_patron_info($account);
  return array(
    'fbs_preferred_branch' => $patron_info['preferred_branch'],
    'interest_period' => variable_get('fbs_default_interest_period', 180),
  );
}

/**
 * Implements provider reservation, options.
 *
 * @param object $account
 *   The user to get reservation options for.
 * @param string $default_branch
 *   Default branch to select.
 *
 * @return array
 *   The reservation options.
 */
function fbs_reservation_options($account, $default_branch = NULL) {
  $preferred_branch = NULL;

  if (ding_user_is_provider_user($account)) {
    $patron_info = fbs_get_patron_info($account);

    $preferred_branch = empty($default_branch) ? $patron_info['preferred_branch'] : $default_branch;
  }

  if ((!empty($default_branch))) {
    $preferred_branch = $default_branch;
  }

  $form = array();
  $form += ding_reservation_default_options_branch('fbs_preferred_branch', $preferred_branch, fbs_branches());
  $form += ding_reservation_interest_period_selector('interest_period', variable_get('fbs_default_interest_period', 180), fbs_interest_periods());

  return $form;
}

/**
 * Implements provider reservation, options_submit.
 *
 * @param object $account
 *   The user to get update preferred branch for.
 * @param array $values
 *   Form values.
 */
function fbs_reservation_options_submit($account, $values) {
  fbs_update_preferred_branch($account, $values['fbs_preferred_branch']);
}

/**
 * Implements provider reservation, default_interst_period.
 *
 * @return int
 *   Default interest period for user.
 */
function fbs_reservation_default_interest_period() {
  return variable_get('fbs_default_interest_period', 180);
}
