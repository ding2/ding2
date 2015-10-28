<?php
/**
 * @file
 * Handles reservations for OpenRuth.
 */

/**
 * Get list of pickup branches.
 *
 * @param StdClass $account
 *   Drupal user object.
 *
 * @return array
 *   OpenRuth pickup branches.
 */
function openruth_reservation_pickup_branches($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);

  $branches = openruth_client_invoke('get_agencycounters');
  return $branches;
}

/**
 * Get list of reserved items.
 *
 * If type is given only that type of reservations is returned.
 *
 * @param StdClass $account
 *   Drupal user object.
 * @param string $type
 *   The type of reservation.
 *    - DING_RESERVATION_READY
 *    - DING_RESERVATION_NOT_READY
 *    - DING_RESERVATION_INTERLIBRARY_LOANS
 *
 * @return array
 *   Array with DingProviderReservation objects.
 */
function openruth_reservation_list($account, $type = NULL) {
  // Use a static cache to speed up the process of getting reservations from
  // OpenRuth, when call more than once in a single HTTP request.
  $result = &drupal_static(__FUNCTION__);
  if (!isset($result)) {
    // If both static cache and session cache failed, try reloading information
    // from OpenRuth.
    if (empty($result)) {
      // Set default reservation types.
      $result = array(
        DING_RESERVATION_READY => array(),
        DING_RESERVATION_NOT_READY => array(),
        DING_RESERVATION_INTERLIBRARY_LOANS => array(),
      );

      // Get information for OpenRuth.
      $creds = ding_user_get_creds($account);
      $status = _openruth_user_status($creds);

      if (isset($status->orders->orderReady)) {
        foreach ($status->orders->orderReady as $reservation) {
          $result[DING_RESERVATION_READY][$reservation->orderId] = new DingProviderReservation($reservation->orderId, array(
            'order_id' => $reservation->orderId,
            'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation->itemId,
            'display_name' => $reservation->itemDisplayTitle,
            // For some reason, we might not get a pickup date back.
            'pickup_date' => (!empty($reservation->orderPickUpDate)) ? $reservation->orderPickUpDate : NULL,
            // Only items that has been set aside for the user has a pickup order
            // ID. Also, not all libraries use it.
            'pickup_order_id' => (!empty($reservation->orderPickUpId)) ? $reservation->orderPickUpId : NULL,
            'pickup_branch_id' => $reservation->agencyCounter,
            'order_arrived' => $reservation->orderArrived,
            'created' => $reservation->orderDate,
            'author' => $reservation->itemAuthor,
            'title' => $reservation->itemTitle,
            'publication_year' => isset($reservation->itemPublicationYear) ? $reservation->itemPublicationYear : '',
            'ready_for_pickup' => 1,
            'notes' => isset($reservation->itemSerialPartTitle) ? $reservation->itemSerialPartTitle : '',
            'reservation_type' => DING_RESERVATION_READY,
          ));
        }
      }

      if (isset($status->orders->orderNotReady)) {
        foreach ($status->orders->orderNotReady as $reservation) {
          $result[DING_RESERVATION_NOT_READY][$reservation->orderId] = new DingProviderReservation($reservation->orderId, array(
            'order_id' => $reservation->orderId,
            'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation->itemId,
            'display_name' => $reservation->itemDisplayTitle,
            'pickup_order_id' => (!empty($reservation->orderPickUpId)) ? $reservation->orderPickUpId : NULL,
            'pickup_branch_id' => $reservation->agencyCounter,
            'expiry' => $reservation->orderLastInterestDate,
            'created' => $reservation->orderDate,
            'queue_number' => $reservation->orderQueuePosition,
            'ready_for_pickup' => 0,
            'author' => isset($reservation->itemAuthor) ? $reservation->itemAuthor : '',
            'title' => $reservation->itemTitle,
            'publication_year' => isset($reservation->itemPublicationYear) ? $reservation->itemPublicationYear : '',
            'notes' => isset($reservation->itemSerialPartTitle) ? $reservation->itemSerialPartTitle : '',
            'reservation_type' => DING_RESERVATION_NOT_READY,
          ));
        }
      }

      if (isset($status->illOrders->illOrder)) {
        foreach ($status->illOrders->illOrder as $reservation) {
          $result[DING_RESERVATION_INTERLIBRARY_LOANS][$reservation->orderId] = new DingProviderReservation($reservation->orderId, array(
            'order_id' => $reservation->orderId,
            'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation->itemId,
            'display_name' => $reservation->itemDisplayTitle,
            'pickup_branch_id' => $reservation->agencyCounter,
            'expiry' => $reservation->orderLastInterestDate,
            'created' => $reservation->orderDate,
            'author' => isset($reservation->itemAuthor) ? $reservation->itemAuthor : '',
            'title' => $reservation->itemTitle,
            'publication_year' => isset($reservation->itemPublicationYear) ? $reservation->itemPublicationYear : '',
            'ill_status' => $reservation->illStatus,
            'notes' => isset($reservation->itemSerialPartTitle) ? $reservation->itemSerialPartTitle : '',
            'reservation_type' => DING_RESERVATION_INTERLIBRARY_LOANS,
          ));
        }
      }
    }
  }

  if (!is_null($type)) {
    if (isset($result[$type])) {
      return $result[$type];
    }
    else {
      watchdog('openruth', 'Unknown reservation type (%type) requested', array('%type' => $type), WATCHDOG_ERROR);
      return array();
    }
  }

  return $result;
}

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
function openruth_reservation_options($account, $default_value) {
  $preferred_branch = NULL;
  $interest_period = NULL;
  if (ding_user_is_provider_user($account)) {
    // Load profile2 profile.
    $profile = ding_user_provider_profile($account);

    // Use a metadata wrapper to access the data.
    $wrapper = entity_metadata_wrapper('profile2', $profile);

    // Get values.
    $preferred_branch = $wrapper->field_openruth_preferred_branch->value();
    $interest_period = openruth_reservation_default_interest_period($profile);
  }

  // Set default value in the selection box if given else use preferred_branch.
  $default = $preferred_branch;
  if (!empty($default_value)) {
    $default = $default_value;
  }

  $form = array();
  $form += ding_reservation_default_options_branch('field_openruth_preferred_branch', $default, openruth_allowed_branches());
  $form += ding_reservation_interest_period_selector('interest_period', $interest_period, openruth_get_interest_periods());

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
function openruth_reservation_default_options($account) {
  // Load profile2 profile.
  $profile = ding_user_provider_profile($account);

  // Use a metadata wrapper to access the data.
  $wrapper = entity_metadata_wrapper('profile2', $profile);

  // Get values.
  $profile_branch = $wrapper->field_openruth_preferred_branch->value();
  $interest_period = openruth_reservation_default_interest_period($profile);

  return array(
    'field_openruth_preferred_branch' => $profile_branch,
    'interest_period' => $interest_period,
  );
}

/**
 * Submit handler for reservations options.
 *
 * @param StdClass $account
 *   Drupal user account object.
 * @param type $values
 */
function openruth_reservation_options_submit($account, $values) {
  // Load profile2 profile.
  $profile = ding_user_provider_profile($account);

  // Use a metadata wrapper to access the data.
  $wrapper = entity_metadata_wrapper('profile2', $profile);

  // Get values.
  $profile_branch = $wrapper->field_openruth_preferred_branch->value();

  // If default branch was not found in the profile, update the profile with the
  // one selected.
  if (!$profile_branch) {
    $wrapper->field_openruth_preferred_branch->set($values['openruth_preferred_branch']);

    // Save the profile it's field have been updated in the wrapper.
    $profile->save();
  }
}

/**
 * Create a reservation for a given account.
 *
 * @param StdClass $account
 *   Drupal user account object.
 * @param type $id
 * @param type $options
 *
 * @return type
 */
function openruth_reservation_create($account, $id, $options = array(), $expiry = NULL) {
  $profile = ding_user_provider_profile($account);
  if (!empty($profile)) {
    $wrapper = entity_metadata_wrapper('profile2', $profile);
    // Interest period.
    if (!isset($options['interest_period'])) {
      if (!isset($expiry)) {

        $interest_period = openruth_reservation_default_interest_period($profile);
        if ($interest_period) {
          // Change it to seconds from days.
          $expiry = $interest_period * 86400;
        }
      }
      else {
        // The user don't have a default interest period, so use the system wide
        // one for openruth (which default is 180 days).
        $expiry = variable_get('openruth_default_interest_period', 180) * 86400;
      }
    }
    else {
      $expiry = $options['interest_period'] * 86400;
    }

    // Preferred branch.
    $branch = $wrapper->field_openruth_preferred_branch->value();
    if (isset($options['field_openruth_preferred_branch'])) {
      $branch = $options['field_openruth_preferred_branch'];
    }
  }

  // Get creds and user status.
  $creds = ding_user_get_creds($account);

  // Create the reservation at openruth.
  $order_res = openruth_client_invoke('order_item', $creds['name'], $id, 1, date('c', time()), date('Y-m-d', time() + $expiry), $branch);
  $order = array_shift($order_res);
  if ($order == 1) {
    // Order success; refresh cache.
    _openruth_user_status($creds, TRUE);
    $order_res['branch'] = $branch;
    // @todo: It seems like this function returns a response directly from the
    // OpenRuth client. Is this appropriate?
    return $order_res;
  }
  elseif ($order == 'already reserved by user') {
    throw new DingProviderReservationExists();
  }
  else {
    throw new DingProviderUserException(t('Error: %order', array('%order', $order)));
  }
}


/**
 * Update order.
 *
 * @param StdClass $account
 *   Drupal user account object.
 * @param type $res_ids
 * @param type $options
 * @return type
 */
function openruth_reservation_update($account, $res_ids, $options) {
  $reservations = openruth_reservation_list($account);
  foreach ($res_ids as $res_id) {
    if ($res_id) {
      $branch = !empty($options['field_openruth_preferred_branch']) ? $options['field_openruth_preferred_branch'] : $reservations[$res_id]->pickup_branch_id;
      $expiry = !empty($options['interest_period']) ? date('Y-m-d', REQUEST_TIME + ($options['interest_period'] * 24 * 60 * 60)) : $reservations[$res_id]->expiry;
      openruth_client_invoke('update_order', $res_id, $branch, $expiry);
    }
  }
  // Flush cache.
  $creds = ding_user_get_creds($account);
  _openruth_user_status($creds, TRUE);
}

/**
 * Implements hook_reservation_deletion_enabled().
 *
 * Check where reservation deletion have been enabled in the providers settings.
 */
function openruth_reservation_reservation_deletion_enabled() {
  return variable_get('openruth_enable_reservation_deletion', FALSE);
}

/**
 * Delete a reservation for a given account.
 *
 * @param StdClass $account
 *    Drupal user account object.
 * @param type $id
 */
function openruth_reservation_delete($account, $id) {
  $creds = ding_user_get_creds($account);

  $res = openruth_client_invoke('cancel_order', $id);

  if ($res == TRUE) {
    _openruth_user_status($creds, TRUE);
  }
}

/**
 * Return a branch name for a given branch id.
 *
 * @param string $branch_id
 * @return string
 */
function openruth_reservation_branch_name($branch_id) {
  // Throw exception if we're not logged in.
  ding_user_get_creds();

  $branches = openruth_client_invoke('get_agencycounters');
  if (isset($branches[$branch_id])) {
    return $branches[$branch_id];
  }
  return NULL;
}

/**
 * Implements hook_default_interest_period().
 *
 * Tries to find the users default interest period based on the users profile2
 * provider profile.
 */
function openruth_reservation_default_interest_period($profile = NULL) {
  // If profile is not given, try loading it for the user.
  if (is_null($profile)) {
    global $user;
    $profile = ding_user_provider_profile($user);
  }

  // Get interest period from the profile.
  $wrapper = entity_metadata_wrapper('profile2', $profile);
  $value = $wrapper->field_openruth_interest_period->value();

  // If no period is selected, try getting default value.
  if (is_null($value) || empty($value)) {
    $value = variable_get('openruth_default_interest_period', 180);
  }

  return $value;
}
