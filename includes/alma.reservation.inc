<?php
/**
 * @file
 * Handles reservation with Alma.
 */


/**
 * Creates form with which can be used during reservation to select preferred
 * branch and interest period.
 *
 * @param type $type
 * @param type $account
 * @param type $reservables
 * @return type
 */
function alma_reservation_options($type, $account, $reservables) {
  $branches = alma_reservation_pickup_branches($account);
  $periods = alma_get_interest_periods();

  $preferred_branch = NULL;
  $interest_period = NULL;
  if (ding_user_is_provider_user($account)) {
    // Load profile2 profile.
    $profile = ding_user_provider_profile($account);

    // Use a metadata wrapper to access the data.
    $wrapper = entity_metadata_wrapper('profile2', $profile);

    // Get values.
    $preferred_branch = $wrapper->field_alma_preferred_branch->value();
    $interest_period = $wrapper->field_alma_interest_period->value();
  }

  $form = array();
  $form += ding_reservation_default_options_branch($type, 'alma_preferred_branch', $preferred_branch, $branches);
  $form += ding_reservation_interest_period_selector($type, 'alma_interest_period', $interest_period, $periods);

  return $form;
}

/**
 * Validate reservations options.
 *
 * @param type $type
 * @param type $account
 * @param type $reservables
 * @param type $values
 * @return type
 */
function alma_reservation_options_validate($type, $account, $reservables, $values) {
  // Load profile2 profile.
  $profile = ding_user_provider_profile($account);

  // Use a metadata wrapper to access the data.
  $wrapper = entity_metadata_wrapper('profile2', $profile);

  // Get values.
  $preferred_branch = $wrapper->field_alma_preferred_branch->value();;
  $interest_period =  $wrapper->field_alma_interest_period->value();

  // Perform a check to whether a show specific select dropdown.
  // Returning NULL means to skip this check, therefore to reserve instantly.
  if (!empty($$preferred_branch) && !empty($interest_period) && $type == 'create') {
    return array(
      'alma_preferred_branch' => $$preferred_branch,
      'alma_interest_period' => $interest_period,
    );
  }
  else {
    $branch_valid = ding_reservation_default_options_branch_validate($type, 'alma_preferred_branch', $preferred_branch, $values);
    $period_valid = ding_reservation_default_options_interest_period_validate($type, 'alma_interest_period', $interest_period, $values);
    return array_merge($branch_valid, $period_valid);
  }
}

/**
 * Submit handler for reservations options.
 *
 * @param type $type
 * @param type $account
 * @param type $reservables
 * @param type $values
 */
function alma_reservation_options_submit($type, $account, $reservables, $values) {
  // Load profile2 profile.
  $profile = ding_user_provider_profile($account);

  // Use a metadata wrapper to access the data.
  $wrapper = entity_metadata_wrapper('profile2', $profile);

  // Get values.
  $preferred_branch = $wrapper->field_alma_preferred_branch->value();;

  $update = ding_reservation_default_options_branch_submit($type, 'alma_preferred_branch', $preferred_branch, $values);
  if (!empty($update['alma_preferred_branch'])) {
    $wrapper->field_alma_preferred_branch->set($update['alma_preferred_branch']);
  }
}

/**
 * Set preferred pickup branch.
 *
 * @param type $account
 * @param type $branch
 */
function alma_reservation_set_preferred_branch($account, $branch) {
  // Throws an exception if we are not logged in.
  $creds = ding_user_get_creds($account);

  // Update preferred branch.
  alma_client_invoke('get_reservations', $creds['name'], $creds['pass'], $branch);
}

/**
 * Get list of reserved items.
 *
 * @param type $account
 * @return object DingProviderReservation
 */
function alma_reservation_list($account) {
  $reservations = alma_reservation_get_reservations($account);
  $result = array();

  // Create DingProviderReservation objects into to categories base on pickup
  // status.
  foreach ($reservations as $reservation) {
    if (isset($reservation['pickup_number'])) {
      $result[$reservation['id']] = new DingProviderReservation($reservation['id'], array(
        'order_id' => $reservation['id'],
        'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation['record_id'],
        'pickup_branch_id' => $reservation['pickup_branch'],
        'order_arrived' => NULL,
        'pickup_order_id' => $reservation['pickup_number'],
        'pickup_date' => $reservation['pickup_expire_date'],
        'created' => $reservation['create_date'],
        'expiry' => $reservation['valid_to'],
        'queue_number' => $reservation['queue_number'],
        'ready_for_pickup' => 1,
        'notes' => isset($reservation['notes']) ? $reservation['notes'] : '',
      ));
    }
    else {
      $result[$reservation['id']] = new DingProviderReservation($reservation['id'], array(
        'order_id' => $reservation['id'],
        'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation['record_id'],
        'pickup_branch_id' => $reservation['pickup_branch'],
        'order_arrived' => NULL,
        'pickup_order_id' => NULL,
        'created' => $reservation['create_date'],
        'expiry' => $reservation['valid_to'],
        'queue_number' => $reservation['queue_number'],
        'ready_for_pickup' => 0,
        'notes' => isset($reservation['notes']) ? $reservation['notes'] : '',
      ));
    }
  }

  return $result;
}

/**
 * Create a reservation for a given account.
 *
 * @param type $account
 * @param type $id
 * @param type $branch
 * @param type $expiry
 * @return type
 * @throws DingProviderReservationExists
 * @throws DingProviderReservationNotAllowed
 * @throws DingProviderReservationNotAvailable
 */
function alma_reservation_create($account, $id, $branch, $expiry = NULL) {
  $creds = ding_user_get_creds($account);

  // Check if the users has this reservation and throw exception.
  if (alma_reservation_exists($account, $id)) {
    throw new DingProviderReservationExists();
  }

  $entity = profile2_load_by_user($account, 'provider_alma');
  if (!empty($entity)) {
    $wrapper = entity_metadata_wrapper('profile2', $entity);
    // interest period
    if (!isset($expiry)) {

      // Use a metadata wrapper to access the data.
      $interest_period = $wrapper->field_alma_interest_period->value();
      if ($interest_period) {
        $expiry = REQUEST_TIME + ($interest_period['key'] * 24 * 60 * 60);
      }
    }
    if (!isset($expiry)) {
      $expiry = REQUEST_TIME + DING_RESERVATION_DEFAULT_INTEREST_PERIOD;
    }

    // preferred branch
    if (empty($branch)) {
      $branch = $wrapper->field_alma_preferred_branch->value();
    }
  }

  // Build the reservation parameters to send.
  $params = array(
    'id' => $id,
    'valid_from' => date('Y-m-d'),
    'valid_to' => alma_reservation_format_date($expiry),
    'pickup_branch' => $branch,
  );

  alma_reservation_clear_cache();

  // Try to make the reservation.
  $result = alma_client_invoke('add_reservation', $creds['name'], $creds['pass'], $params);

  if ($result === ALMA_AUTH_BLOCKED) {
    /**
     * @todo return better exception that informs the user about the block
     * status.
     */
    throw new DingProviderReservationNotAllowed();
  }

  if (is_int($result)) {
    // Reset session cache
    alma_reservation_clear_cache();
    return array(
      'branch' => $branch,
      'queue_number' => $result,
    );
  }
  else {
    throw new DingProviderReservationNotAvailable();
  }
}

/**
 * Update order, by defining new expiry date or pickup branch.
 *
 * @param type $account
 * @param type $ids
 * @param type $options
 * @return boolean
 */
function alma_reservation_update($account, $ids, $options) {
  $creds = ding_user_get_creds($account);
  $reservations = alma_reservation_get_reservations($account);
  $updated = FALSE;

  // Processing IDs. If at least one is updated, return true.
  foreach ($ids as $id) {
    if (isset($reservations[$id])) {
      $expiry_date = !empty($options['alma_interest_period']) ? alma_reservation_format_date(strtotime($reservations[$id]['valid_from']) + $options['alma_interest_period'] * 86400) : $reservations[$id]['valid_to'];
      $pickup_branch = !empty($options['alma_preferred_branch']) ? $options['alma_preferred_branch'] : $reservations[$id]['pickup_branch'];
      $changes = array(
        'valid_to' => $expiry_date,
        'pickup_branch' => $pickup_branch,
      );
      // Alma do not return a status.
      alma_client_invoke('change_reservation', $creds['name'], $creds['pass'], $reservations[$id], $changes);
      $updated = TRUE;
    }
  }

  // Clear cache after all reservations have been updated.
  if ($updated) {
    alma_reservation_clear_cache();
  }

  return $updated;
}

/**
 * Delete a reservation for a given account.
 *
 * @param type $account
 * @param type $id
 * @return type
 */
function alma_reservation_delete($account, $id) {
  $creds = ding_user_get_creds($account);
  $reservations = alma_reservation_get_reservations($account);

  alma_reservation_clear_cache();
  if (isset($reservations[(string)$id])) {
    return alma_client_invoke('remove_reservation', $creds['name'], $creds['pass'], $reservations[(string)$id]);
  }
}

/**
 * Return a branch name for a given branch id.
 *
 * @param $branch_id String
 * @return String
 */
function alma_reservation_branch_name($branch_id) {
  // Get library organistation from alma.
  $organisation = alma_get_organisation();
  $branch = (is_array($branch_id) && isset($branch_id['alma_preferred_branch'])) ? $branch_id['alma_preferred_branch'] : $branch_id;
  if (isset($organisation['branch'][$branch])) {
    return $organisation['branch'][$branch];
  }
  return NULL;
}

/**
 * @TODO: add description.
 *
 * @param type $account
 * @param type $reset
 * @return type
 */
function alma_reservation_get_reservations($account, $reset = FALSE) {
  $creds = ding_user_get_creds($account);

  // Try to look in the session for reservation information.
  if (!isset($_SESSION['alma_reservations']) || !is_array($_SESSION['alma_reservations']) || $reset) {
    $_SESSION['alma_reservations'] = alma_client_invoke('get_reservations', $creds['name'], $creds['pass']);
  }

  return $_SESSION['alma_reservations'];
}

/**
 * @TODO: add description.
 */
function alma_reservation_clear_cache() {
  unset($_SESSION['alma_reservations']);
}

/**
 * @TODO: add description.
 *
 * @param type $account
 * @param type $item_id
 * @return boolean
 */
function alma_reservation_exists($account, $item_id) {
  $reservations = alma_reservation_get_reservations($account);
  foreach ($reservations as $res) {
    if ($res['record_id'] == $item_id) {
      return TRUE;
    }
    return FALSE;
  }
}

/**
 * @TODO: add description.
 *
 * @param type $datetime
 * @return type
 */
function alma_reservation_format_date($datetime) {
  $timestamp = (!is_int($datetime)) ? strtotime($datetime) : $datetime;
  return date('Y-m-d', $timestamp);
}
