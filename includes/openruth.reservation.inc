<?php
/**
 * @file
 * Handels reservations for OpenRuth.
 */

/**
 * Get list of pickup branches.
 *
 * @param type $account
 * @return type
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
 * @param type $account
 * @return \DingProviderReservation
 */
function openruth_reservation_list($account, $type = NULL) {
  $result = &drupal_static(__FUNCTION__, array(
    'ready_for_pickup' => array(),
    'not_ready_for_pickup' => array(),
    'interlibrary_loans' => array(),
  ));

  if (empty($result)) {
    $creds = ding_user_get_creds($account);
    $status = _openruth_user_status($creds);

    if (isset($status->orders->orderReady)) {
      foreach ($status->orders->orderReady as $res) {
        $result['ready_for_pickup'][$res->orderId] = new DingProviderReservation($res->orderId, array(
          'order_id' => $res->orderId,
          'ding_entity_id' => variable_get('ting_agency', '') . ':' . $res->itemId,
          'display_name' => $res->itemDisplayTitle,
          // For some reason, we might not get a pickup date back.
          'pickup_date' => (!empty($res->orderPickUpDate)) ? $res->orderPickUpDate : NULL,
          // Only items that has been set aside for the user has a pickup order ID. Also, not all libraries use it.
          'pickup_order_id' => (!empty($res->orderPickUpId)) ? $res->orderPickUpId : NULL,
          'pickup_branch_id' => $res->agencyCounter,
          'order_arrived' => $res->orderArrived,
          'created' => $res->orderDate,
          'author' => $res->itemAuthor,
          'title' => $res->itemTitle,
          'publication_year' => $res->itemPublicationYear,
          'ready_for_pickup' => 1,
          'notes' => isset($res->itemSerialPartTitle) ? $res->itemSerialPartTitle : '',
        ));
      }
    }
    if (isset($status->orders->orderNotReady)) {
      foreach ($status->orders->orderNotReady as $res) {
        $result['not_ready_for_pickup'][$res->orderId] = new DingProviderReservation($res->orderId, array(
          'order_id' => $res->orderId,
          'ding_entity_id' => variable_get('ting_agency', '') . ':' . $res->itemId,
          'display_name' => $res->itemDisplayTitle,
          'pickup_order_id' => (!empty($res->orderPickUpId)) ? $res->orderPickUpId : NULL,
          'pickup_branch_id' => $res->agencyCounter,
          'expiry' => $res->orderLastInterestDate,
          'created' => $res->orderDate,
          'queue_number' => $res->orderQueuePosition,
          'ready_for_pickup' => 0,
          'author' => isset($res->itemAuthor) ? $res->itemAuthor : '',
          'title' => $res->itemTitle,
          'publication_year' => isset($res->itemPublicationYear) ? $res->itemPublicationYear : '',
          'notes' => isset($res->itemSerialPartTitle) ? $res->itemSerialPartTitle : '',
        ));
      }
    }
    if (isset($status->illOrders->illOrder)) {
      foreach ($status->illOrders->illOrder as $res) {
        $result['interlibrary_loans'][$res->orderId] = new DingProviderReservation($res->orderId, array(
          'order_id' => $res->orderId,
          'ding_entity_id' => variable_get('ting_agency', '') . ':' . $res->itemId,
          'display_name' => $res->itemDisplayTitle,
          'pickup_branch_id' => $res->agencyCounter,
          'expiry' => $res->orderLastInterestDate,
          'created' => $res->orderDate,
          'author' => isset($res->itemAuthor) ? $res->itemAuthor : '',
          'title' => $res->itemTitle,
          'publication_year' => isset($res->itemPublicationYear) ? $res->itemPublicationYear : '',
          'ill_status' => $res->illStatus,
          'notes' => isset($res->itemSerialPartTitle) ? $res->itemSerialPartTitle : '',
        ));
      }
    }
  }

  if (!is_null($type)) {
    if (isset($result[$type])) {
      return $result[$type];
    }
    else {
      watchdog('openruth', 'Unknown reservation type (%type) requested', array('%type' => $type) , WATCHDOG_ERROR);
      return array();
    }
  }

  return $result;
}

/**
 * Provide options for reservation.
 *
 * @param type $account
 * @return type
 * @throws Exception
 */
function openruth_reservation_options($account) {
  // While we use ding_reservation for branch handling, we don't want to
  // depend on the module, as it would mean that ding_reservation can't be
  // disabled. So instead we throw an exception here.
  if (!module_exists('ding_reservation')) {
    throw new Exception('Openruth reservation options requires ding_reservation.');
  }

  $form = array();
  $profile = ding_user_provider_profile($account);

  if (ding_user_is_provider_user($account)) {
    $wrapper = entity_metadata_wrapper('profile2', $profile);
    $preferred_branch = $wrapper->field_openruth_preferred_branch->value();
    $interest_period = $wrapper->field_openruth_interest_period->value();
  }

  $form += ding_reservation_default_options_branch('field_openruth_preferred_branch', $preferred_branch, openruth_allowed_branches());
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
  $interest_period = $wrapper->field_openruth_interest_period->value();

  return array(
    'field_openruth_preferred_branch' => $profile_branch,
    'interest_period' => $interest_period,
  );
}

/**
 * Submit handler for reservations options.
 *
 * @param type $account
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
  if ($profile_branch) {
    $wrapper->field_openruth_preferred_branch->set($values['openruth_preferred_branch']);
    $profile->save();
  }
}

/**
 * Create a reservation for a given account.
 *
 * @param type $account
 * @param type $id
 * @param type $options
 * @return type
 * @throws DingProviderReservationExists
 * @throws DingProviderUserException
 */
function openruth_reservation_create($account, $id, $options = array(), $expiry = NULL) {
  $entity = ding_user_provider_profile($account);
  if (!empty($entity)) {
    $wrapper = entity_metadata_wrapper('profile2', $entity);

    // Interest period
    if (!isset($options['interest_period'])) {
      if (!isset($expiry)) {
        // Use a metadata wrapper to access the data.
        $interest_period = $wrapper->field_openruth_interest_period->value();
        if ($interest_period) {
          // Change it to secounds from days.
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

    // Preferred branch
    $branch = $wrapper->field_openruth_preferred_branch->value();
    if (isset($options['field_openruth_preferred_branch'])) {
      $branch = $options['field_openruth_preferred_branch'];
    }
  }

  // Get creds and user status.
  $creds = ding_user_get_creds($account);
  $status = _openruth_user_status($creds, TRUE);

  // Create the reservation at openruth.
  $internal_account = ding_user_get_creds($account);
  $order_res = openruth_client_invoke('order_item', $internal_account['name'], $id, 1, date('c', time()), date('Y-m-d', $expiry), $branch);
  $order = array_shift($order_res);
  if ($order == 1) {
    // order success; refresh cache
    $status = _openruth_user_status($creds, TRUE);
    $order_res['branch'] = $branch;
    /**
     * @todo: It seems like this function returns a response directly from the
     *        OpenRuth client. Is this appropriate?
     */
    return $order_res;
  }
  elseif ($order == 'already reserved by user') {
    throw new DingProviderReservationExists();
  }
  else {
    throw new DingProviderUserException(t('Error: ' . $order));
  }
}


/**
 * Update order.
 *
 * @param type $account
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

  return;
}

/**
 * Implements hook_reservation_deletion_enabled().
 *
 * Check where reservation deletion have been enabled in the providers settings.
 *
 * @return bool
 *  If enabled TRUE else FALSE.
 */
function openruth_reservation_reservation_deletion_enabled() {
  return variable_get('openruth_enable_reservation_deletion', FALSE);
}

/**
 * Delete a reservation for a given account
 *
 * @param type $account
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
 * Return a branch name for a given branch id
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
 * Tries to find the users default interst period based on the users profile2
 * provider profile.
 *
 * @param object $profile
 *  The users profile2 provider profile.
 * @return string
 *  The default interest period selected by the user in his/her profile or the
 * default value selected by the site.
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

  // If no period is seleted, try getting default value.
  if (is_null($value) || empty($value)) {
    $value = variable_get('openruth_default_interest_period', 180);
  }

  return $value;
}

/**
 * Helper function that returns the interest periods from the field options.
 *
 * @return array
 *  Array of interest periods that can be used as default value in form selects.
 */
function openruth_get_interest_periods() {
  $field_info = field_info_field('field_openruth_interest_period');
  $interest_periods = isset($field_info['settings']['allowed_values']) ? $field_info['settings']['allowed_values'] : FALSE;

  return $interest_periods;
}
