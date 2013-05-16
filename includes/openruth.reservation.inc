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
 * Set preferred pickup branch.
 *
 * @param type $account
 * @param type $branch
 */
function openruth_reservation_set_preferred_branch($account, $branch) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  // Do nothing, ding_reservation will update local user if we don't throw an
  // exception.
}

/**
 * Get list of reserved items.
 *
 * @param type $account
 * @return \DingProviderReservation
 */
function openruth_reservation_list($account) {
  $result = &drupal_static(__FUNCTION__, array());

  if (empty($result)) {
    $creds = ding_user_get_creds($account);
    $status = _openruth_user_status($creds);

    if (isset($status->orders->orderReady)) {
      foreach ($status->orders->orderReady as $res) {
        $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
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
        $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
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
        $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
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

  return $result;
}

/**
 * Provide options for reservation.
 *
 * @param type $type
 * @param type $account
 * @param type $reservables
 * @return type
 * @throws Exception
 */
function openruth_reservation_options($type, $account, $reservables) {
  /*
   * While we use ding_reservation for branch handling, we don't want to
   * depend on the module, as it would mean that ding_reservation can't be
   * disabled. So instead we throw an exception here.
   */
  if (!module_exists('ding_reservation')) {
    throw new Exception('Openruth reservation options requires ding_reservation.');
  }

  $form = array();
  $profile = ding_user_provider_profile($account);

  if (ding_user_is_provider_user($account)) {
    $preferred_branch = $profile->field_openruth_preferred_branch[field_language('profile2', $profile, 'field_openruth_preferred_branch')][0]['value'];
    $interest_period = $profile->field_openruth_interest_period[field_language('profile2', $profile, 'field_openruth_interest_period')][0]['value'];
  }
  else {
    $preferred_branch = '';
    $interest_period = ''; // @TODO: Get default provider period. ( openruth_get_interest_period($profile2) )?
  }

  $form += ding_reservation_default_options_branch($type, 'field_openruth_preferred_branch', $preferred_branch, openruth_allowed_branches());
  $form += ding_reservation_interest_period_selector($type, 'openruth_interest_period', $interest_period, openruth_get_interest_periods());

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
function openruth_reservation_options_validate($type, $account, $reservables, $values) {
  $profile = ding_user_provider_profile($account);
  $field_language = field_language('profile2', $profile);
  $profile_branch = $profile->field_openruth_preferred_branch[$field_language['field_openruth_preferred_branch']][0]['value'];
  $interest_period = $profile->field_openruth_interest_period[$field_language['field_openruth_interest_period']][0]['value'];
  // Perform a check to whether a show specific select dropdown.
  // Returning NULL means to skip this check, therefore to reserve instantly.
  if (!empty($profile_branch) && !empty($interest_period) && $type == 'create') {
    return array(
      'field_openruth_preferred_branch' => $profile_branch,
      'openruth_interest_period' => $interest_period,
    );
  }
  else {
    $branch_valid = ding_reservation_default_options_branch_validate($type, 'field_openruth_preferred_branch', $profile_branch, $values);
    $period_valid = ding_reservation_default_options_interest_period_validate($type, 'openruth_interest_period', $interest_period, $values);

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
function openruth_reservation_options_submit($type, $account, $reservables, $values) {
  $profile = ding_user_provider_profile($account);
  $field_language = field_language('profile2', $profile);
  $profile_branch = $profile->field_openruth_preferred_branch[$field_language['field_openruth_preferred_branch']][0]['value'];
  $update = ding_reservation_default_options_branch_submit($type, 'field_openruth_preferred_branch', $profile_branch, $values);
  if (!empty($update['field_openruth_preferred_branch'])) {
    $profile->field_openruth_preferred_branch[$field_language['field_openruth_preferred_branch']][0]['value'] = $update['field_openruth_preferred_branch'];
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
function openruth_reservation_create($account, $id, $options) {
  $branch = $options['field_openruth_preferred_branch'];

  // get interest period from profile2
  if ($profile2 = profile2_load_by_user($account, 'provider_openruth')) {
    $langs = field_language('profile2', $profile2);
    if (isset($profile2->field_openruth_interest_period)) {
      $interest_period = $profile2->field_openruth_interest_period[$langs['field_openruth_interest_period']][0]['value'];

      // Change the period from days into secounds.
      $expiry = REQUEST_TIME + ($interest_period * 86400);
    }
  }

  if (!isset($expiry)) {
    // The user don't have a default interest period, so use the system wide
    // one for openruth (which default is 180 days).
    $expiry = REQUEST_TIME + variable_get('openruth_default_interest_period', 180) * 86400;
  }

  $creds = ding_user_get_creds($account);
  $status = _openruth_user_status($creds, TRUE);

  $internal_account = ding_user_get_creds($account);
  $order_res = openruth_client_invoke('order_item', $internal_account['name'], $id, 1, date('c', time()), date('Y-m-d', $expiry), $branch);
  $order = array_shift($order_res);
  if ($order == 1) {
    // order success; refresh cache
    $status = _openruth_user_status($creds, TRUE);
    $order_res['branch'] = $branch;
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
      $expiry = !empty($options['openruth_interest_period']) ? date('Y-m-d', REQUEST_TIME + ($options['openruth_interest_period'] * 24 * 60 * 60)) : $reservations[$res_id]->expiry;
      openruth_client_invoke('update_order', $res_id, $branch, $expiry);
    }
  }
  // Flush cache.
  $creds = ding_user_get_creds($account);
  _openruth_user_status($creds, TRUE);

  return;
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