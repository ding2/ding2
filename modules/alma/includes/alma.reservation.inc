<?php
/**
 * @file
 * Handles reservation with Alma.
 */

/**
 * Creates form which can be used during reservation.
 *
 * It's used to select preferred branch and interest period.
 *
 * @param stdClass $account
 *   Drupal user account object.
 * @param string $default_value
 *   The name of the branch that should be selected as default value.
 *
 * @return array
 *   Form element with the provider reservation options (branch and interest
 *   period).
 */
function alma_reservation_options($account, $default_value = '') {
  $branches = alma_reservation_pickup_branches();
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
    $interest_period = alma_reservation_default_interest_period($profile);
  }

  // Set default value in the selection box if given else use preferred_branch.
  $default = $preferred_branch;
  if (!empty($default_value)) {
    $default = $default_value;
  }

  $form = array();
  $form += ding_reservation_default_options_branch('alma_preferred_branch', $default, $branches);
  $form += ding_reservation_interest_period_selector('interest_period', $interest_period, $periods);

  return $form;
}

/**
 * Validate reservations options.
 *
 * @param stdClass $account
 *   Drupal user account object.
 *
 * @return array
 *   The interest period and default pick-up branch from the provider profile.
 */
function alma_reservation_default_options($account) {
  // Load profile2 profile.
  $profile = ding_user_provider_profile($account);

  // Use a metadata wrapper to access the data.
  $wrapper = entity_metadata_wrapper('profile2', $profile);

  // Get values.
  $preferred_branch = $wrapper->field_alma_preferred_branch->value();;
  $interest_period = $wrapper->field_alma_interest_period->value();

  $result = array(
    'alma_preferred_branch' => $preferred_branch,
    'interest_period' => $interest_period,
  );

  return $result;
}

/**
 * Submit handler for reservations options.
 *
 * @param stdClass $account
 *   Drupal user account object.
 * @param array $values
 *   The values that should be submitted (@todo needs better description).
 */
function alma_reservation_options_submit($account, $values) {
  // Load profile2 profile.
  $profile = ding_user_provider_profile($account);

  // Use a metadata wrapper to access the data.
  $wrapper = entity_metadata_wrapper('profile2', $profile);

  // Get values.
  $preferred_branch = $wrapper->field_alma_preferred_branch->value();

  // If default branch was not found in the profile, update the profile with the
  // one selected.
  if (!$preferred_branch) {
    $wrapper->field_alma_preferred_branch->set($values['alma_preferred_branch']);
    $profile->save();
  }
}

/**
 * Get list of reserved items index by reservation type.
 *
 * @param stdClass $account
 *   Drupal user account object.
 * @param string $type
 *   Reservation type to return. The sting should be one of
 *   'DING_RESERVATION_READY', 'DING_RESERVATION_NOT_READY' or
 *   'DING_RESERVATION_INTERLIBRARY_LOANS'.
 *
 * @return array
 *   An empty array or an array of DingProviderReservation objects.
 */
function alma_reservation_list($account, $type = NULL) {
  // Use a static cache to speed up the process of getting reservations from
  // alma, when call more than once in a single HTTP request.
  $result = &drupal_static(__FUNCTION__);
  if (!isset($result)) {
    // Check if ding_session_cache is available.
    if (module_exists('ding_session_cache')) {
      $result = ding_session_cache_get('alma', 'reservations');
    }

    // If both static cache and session cache failed, try reloading information
    // from alma.
    if (empty($result)) {
      // Set default reservation types.
      $result = array(
        DING_RESERVATION_READY => array(),
        DING_RESERVATION_NOT_READY => array(),
        DING_RESERVATION_INTERLIBRARY_LOANS => array(),
      );

      // Get reservations from ALMA for the current account.
      $reservations = alma_reservation_get_reservations($account);

      // Create DingProviderReservation objects into three categories.
      foreach ($reservations as $reservation) {
        // Build standard array which matches all types of reservations.
        $data = array(
          'order_id' => $reservation['id'],
          'ding_entity_id' => ding_provider_build_entity_id($reservation['record_id']),
          'pickup_branch_id' => $reservation['pickup_branch'],
          'order_arrived' => NULL,
          'pickup_order_id' => NULL,
          'pickup_date' => NULL,
          'ready_for_pickup' => FALSE,
          'created' => $reservation['create_date'],
          'expiry' => $reservation['valid_to'],
          'queue_number' => $reservation['queue_number'],
          'ill_status' => FALSE,
          'notes' => isset($reservation['notes']) ? $reservation['notes'] : '',
          'reservation_type' => DING_RESERVATION_NOT_READY,
        );

        // If the reservation is ready for pick-up, we fill in that data.
        if (isset($reservation['pickup_number'])) {
          // Set pick-up information.
          $data['pickup_order_id'] = $reservation['pickup_number'];
          $data['pickup_date'] = $reservation['pickup_expire_date'];
          $data['ready_for_pickup'] = TRUE;
          $data['reservation_type'] = DING_RESERVATION_READY;

          // Ready for pick-up can also be a inter-library loan.
          if ($reservation['id'] < 0) {
            // Inter-library loan reservations have negative IDs (undocumented
            // Axiell "feature").
            $data['ill_status'] = TRUE;
          }

          // Create reservation object.
          $result[DING_RESERVATION_READY][$reservation['id']] = new DingProviderReservation($reservation['id'], $data);
        }
        elseif ($reservation['id'] < 0) {
          // Inter-library loan reservations have negative IDs (undocumented
          // Axiell "feature").
          $data['ill_status'] = $reservation['status'];
          $data['reservation_type'] = DING_RESERVATION_INTERLIBRARY_LOANS;

          // Create reservation object.
          $result[DING_RESERVATION_INTERLIBRARY_LOANS][$reservation['id']] = new DingProviderReservation($reservation['id'], $data);
        }
        else {
          // Default case with, so just create the reservation object.
          $result[DING_RESERVATION_NOT_READY][$reservation['id']] = new DingProviderReservation($reservation['id'], $data);
        }
      }

      // Store the reservations into ding session cache.
      if (module_exists('ding_session_cache')) {
        ding_session_cache_set('alma', 'reservations', $result);
      }
    }
  }

  if (!is_null($type)) {
    if (isset($result[$type])) {
      return $result[$type];
    }
    else {
      watchdog('alma', 'Unknown reservation type (%type) requested', array('%type' => $type), WATCHDOG_ERROR);
      return array();
    }
  }

  return $result;
}

/**
 * Create a new reservation in the library system.
 *
 * @param stdClass $account
 * @param string $id
 * @param array $options
 * @param string $expiry
 *
 * @return array
 *
 * @throws DingProviderReservationExists
 * @throws DingProviderReservationNotAllowed
 * @throws DingProviderReservationNotAvailable
 */
function alma_reservation_create($account, $id, $options = array(), $expiry = NULL) {
  $creds = ding_user_get_creds($account);

  // Check if the users has this reservation and throw exception.
  if (alma_reservation_exists($account, $id)) {
    throw new DingProviderReservationExists();
  }

  $entity = ding_user_provider_profile($account);;
  if (!empty($entity)) {
    $wrapper = entity_metadata_wrapper('profile2', $entity);

    // Interest period.
    if (!isset($options['interest_period'])) {
      if (!isset($expiry)) {
        // Use a metadata wrapper to access the data.
        $interest_period = $wrapper->field_alma_interest_period->value();
        if ($interest_period) {
          // Change it to seconds from days.
          $expiry = $interest_period * 86400;
        }
      }
      else {
        // The user don't have a default interest period, so use the system wide
        // one for alma (which default is 180 days).
        $expiry = variable_get('alma_default_interest_period', 180) * 86400;
      }
    }
    else {
      $expiry = $options['interest_period'] * 86400;
    }

    // Preferred branch.
    $branch = $wrapper->field_alma_preferred_branch->value();
    if (isset($options['alma_preferred_branch'])) {
      $branch = $options['alma_preferred_branch'];
    }
  }

  // Build the reservation parameters to send.
  $params = array(
    'id' => $id,
    'valid_from' => date(ALMA_DATE),
    'valid_to' => alma_reservation_format_date(time() + $expiry),
    'pickup_branch' => $branch,
  );

  // Clear the local alma cache.
  alma_reservation_clear_cache();

  // Try to make the reservation.
  $result = alma_client_invoke('add_reservation', $creds['name'], $creds['pass'], $params);

  if ($result === ALMA_AUTH_BLOCKED) {
    // @todo return better exception that informs the user about the block
    // status.
    throw new DingProviderReservationNotAllowed();
  }

  if (is_int($result)) {
    // Reset session cache.
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
 * @param stdClass $account
 * @param array $ids
 * @param array $options
 *
 * @return bool
 */
function alma_reservation_update($account, $ids, $options) {
  $creds = ding_user_get_creds($account);
  $reservations = alma_reservation_get_reservations($account);
  $updated = FALSE;

  // Processing IDs. If at least one is updated, return true.
  foreach ($ids as $id) {
    if (isset($reservations[$id])) {
      $expiry_date = !empty($options['interest_period']) ? alma_reservation_format_date(strtotime($reservations[$id]['valid_from']) + $options['interest_period'] * 86400) : $reservations[$id]['valid_to'];
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
 * @param stdClass $account
 * @param string $id
 *
 * @return type
 */
function alma_reservation_delete($account, $id) {
  $creds = ding_user_get_creds($account);
  $reservations = alma_reservation_get_reservations($account);

  alma_reservation_clear_cache();
  if (isset($reservations[(string) $id])) {
    return alma_client_invoke('remove_reservation', $creds['name'], $creds['pass'], $reservations[(string) $id]);
  }
}

/**
 * Implements hook_default_interest_period().
 *
 * Tries to find the users default interest period based on the users profile2
 * provider profile.
 *
 * @param object $profile
 *   The users profile2 provider profile.
 *
 * @return string
 *   The default interest period selected by the user in his/her profile or the
 *   default value selected by the site.
 */
function alma_reservation_default_interest_period($profile = NULL) {
  // If profile is not given, try loading it for the user.
  if (is_null($profile)) {
    global $user;
    $profile = ding_user_provider_profile($user);
  }

  // Get interest period from the profile.
  $wrapper = entity_metadata_wrapper('profile2', $profile);
  $value = $wrapper->field_alma_interest_period->value();

  // If no period is selected, try getting default value.
  if (is_null($value) || empty($value)) {
    $value = variable_get('alma_default_interest_period', 180);
  }

  return $value;
}

/**
 * Implements hook_reservation_deletion_enabled().
 *
 * Check where reservation deletion have been enabled in the providers settings.
 *
 * @return bool
 *   If enabled TRUE else FALSE.
 */
function alma_reservation_reservation_deletion_enabled() {
  return variable_get('alma_enable_reservation_deletion', FALSE);
}

/**
 * Return a branch name for a given branch id.
 *
 * @param string $branch_id
 *   The identifier for a given pick-up branch (e.g. hb)
 *
 * @return string
 *   The human name for the id or NULL if one do not exist.
 */
function alma_reservation_branch_name($branch_id) {
  // Get library organization from alma.
  $organisation = alma_get_organisation();
  $branch = (is_array($branch_id) && isset($branch_id['alma_preferred_branch'])) ? $branch_id['alma_preferred_branch'] : $branch_id;
  if (isset($organisation['branch'][$branch])) {
    return $organisation['branch'][$branch];
  }
  return NULL;
}

/**
 * Get all reservation from Alma and store them in the cache.
 *
 * @param stdClass $account
 *   Drupal user account object.
 *
 * @param bool $reset
 *   If TRUE the cache will be by-passed.
 *
 * @return mixed
 *   Alma reservations.
 */
function alma_reservation_get_reservations($account, $reset = FALSE) {
  $creds = ding_user_get_creds($account);

  $reservations = &drupal_static(__FUNCTION__, FALSE);
  if (!$reservations || $reset) {
    $reservations = alma_client_invoke('get_reservations', $creds['name'], $creds['pass']);
  }

  return $reservations;
}

/**
 * Clear reservations stored in the current session cache.
 */
function alma_reservation_clear_cache() {
  // Check if ding_session_cache is available.
  if (module_exists('ding_session_cache')) {
    ding_session_cache_clear('alma', 'reservations');
  }
}

/**
 * Check if a reservation exists at the provider (ALMA).
 *
 * @param stdClass $account
 *   Drupal user account object.
 * @param string $reservation_id
 *   The id of the reservation to test for.
 *
 * @return bool
 *   TRUE if the reservation exists else FALSE.
 */
function alma_reservation_exists($account, $reservation_id) {
  $reservations = alma_reservation_get_reservations($account);
  foreach ($reservations as $res) {
    if ($res['record_id'] == $reservation_id) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Helper function calculate the date in the feature base on interest period.
 *
 * @param int $expiry
 *   The number of seconds into the feature we need at date.
 *
 * @return string
 *   The date in the feature in the format 'Y-m-d' (ALMA_DATE).
 */
function alma_reservation_format_date($expiry) {
  return date(ALMA_DATE, $expiry);
}
