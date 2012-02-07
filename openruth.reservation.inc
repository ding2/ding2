<?php

/**
 * Get list of pickup branches
 */
function openruth_reservation_pickup_branches($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);

  $branches = openruth_client_invoke('get_agencycounters');
  return $branches;
}

/**
 * Set preferred pickup branch
 */
function openruth_reservation_set_preferred_branch($account, $branch) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  // Do nothing, ding_reservation will update local user if we don't throw an exception.
}

/**
 * Get list of reserved items
 */
function openruth_reservation_list($account) {
  $creds = ding_user_get_creds($account);
  $result = array();
  $status = _openruth_user_status($creds);

  if (isset($status->orders->orderReady)) {
    foreach ($status->orders->orderReady as $res) {
      $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
        'order_id' => $res->orderId,
        'ding_entity_id' => variable_get('openruth_agency_id', '') . ':' . $res->itemId,
        'display_name' => $res->itemDisplayTitle,
        // For some reason, we might not get a pickup date back.
        'pickup_date' => (!empty($res->orderPickUpDate)) ? $res->orderPickUpDate : NULL,
        // Only items that has been set aside for the user has a pickup order ID. Also, not all libraries use it.
        'pickup_order_id' => (!empty($res->orderPickUpId)) ? $res->orderPickUpId : NULL,
        'pickup_branch_id' => $res->agencyCounter,
        'created' => $res->orderDate,
        'ready_for_pickup' => 1,
                               ));
    }
  }
  if (isset($status->orders->orderNotReady)) {
    foreach ($status->orders->orderNotReady as $res) {
      $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
        'order_id' => $res->orderId,
        'ding_entity_id' => variable_get('openruth_agency_id', '') . ':' . $res->itemId,
        'display_name' => $res->itemDisplayTitle,
        'pickup_order_id' => (!empty($res->orderPickUpId)) ? $res->orderPickUpId : NULL,
        'pickup_branch_id' => $res->agencyCounter,
        'expiry' => $res->orderLastInterestDate,
        'created' => $res->orderDate,
        'queue_number' => $res->orderQueuePosition,
        'ready_for_pickup' => 0,
                               ));
    }
  }
  return $result;
}

/**
 * Provide options for reservation.
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

  if(ding_user_is_provider_user($account)) {
    $preferred_branch = $profile->openruth_preferred_branch[field_language('profile2', $profile, 'openruth_preferred_branch')][0]['value'];
    $interest_period = $profile->field_openruth_interest_period[field_language('profile2', $profile, 'field_openruth_interest_period')][0]['value'];
  }
  else {
    $preferred_branch = NULL;
    $interest_period = NULL; // TO DO : get default provider period. ( openruth_get_interest_period($profile2) )?
  }

  $form += ding_reservation_default_options_branch($type, 'openruth_preferred_branch',$preferred_branch, openruth_allowed_branches());
  $form += ding_reservation_interest_period_selector($type, 'expiry', $interest_period, openruth_get_interest_periods());

  return $form;
}

/**
 * Validate reservations options.
 */
function openruth_reservation_options_validate($type, $account, $reservables, $values) {
  $result = array();
  $profile = ding_user_provider_profile($account);
  $field_language = field_language('profile2', $profile);
  $profile_branch = $profile->openruth_preferred_branch[$field_language['openruth_preferred_branch']][0]['value'];
  return ding_reservation_default_options_branch_validate($type, 'openruth_preferred_branch', $profile_branch, $values);
}

/**
 * Submit handler for reservations options.
 */
function openruth_reservation_options_submit($type, $account, $reservables, $values) {
  $profile = ding_user_provider_profile($account);
  $field_language = field_language('profile2', $profile);
  $profile_branch = $profile->openruth_preferred_branch[$field_language['openruth_preferred_branch']][0]['value'];
  $update = ding_reservation_default_options_branch_submit($type, 'openruth_preferred_branch', $profile_branch, $values);
  if (!empty($update['openruth_preferred_branch'])) {
    $profile->openruth_preferred_branch[$field_language['openruth_preferred_branch']][0]['value'] = $update['openruth_preferred_branch'];
    $profile->save();
  }
};

/**
 * Create a reservation for a given account
 */
function openruth_reservation_create($account, $id, $options) {
  $branch = $options['openruth_preferred_branch'];

  // get interest period from profile2
  if(  $profile2 = profile2_load_by_user($account,'provider_openruth') ) {
    $langs = field_language('profile2', $profile2);
    if( isset($profile2->field_openruth_interest_period) ) {
      $interest_period = $profile2->field_openruth_interest_period[$langs['field_openruth_interest_period']][0]['value'];
      $expiry = REQUEST_TIME + ($interest_period * 24 * 60 * 60 );
    }
  }

  if( !isset($expiry) ) {
   $expiry = REQUEST_TIME + DING_RESERVATION_DEFAULT_INTEREST_PERIOD;
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
 */
function openruth_reservation_update($account, $res_ids, $options) {
  $reservations = openruth_reservation_list($account);
  $update = FALSE;
  foreach ($res_ids as $res_id) {
    if ( $res_id ) {
      $branch = !empty($options['openruth_preferred_branch']) ? $options['openruth_preferred_branch'] : $reservations[$res_id]->pickup_branch_id;
      $expiry = !empty($options['expiry']) ? date('Y-m-d',REQUEST_TIME + ($options['expiry'] * 24 * 60 * 60)) : $reservations[$res_id]->expiry;
      $res = openruth_client_invoke('update_order', $res_id, $branch, $expiry);
    }
  }
  // Flush cache.
  $creds = ding_user_get_creds($account);
  _openruth_user_status($creds, TRUE);

  return;
}


/**
 * Delete a reservation for a given account
 */
function openruth_reservation_delete($account, $id) {
  $creds = ding_user_get_creds($account);

  $res = openruth_client_invoke('cancel_order', $id);

  if ($res == TRUE) {
    $status = _openruth_user_status($creds, TRUE);
  }
}

/**
 * Return a branch name for a given branch id
 *
 * @param $branch_id String
 * @return String
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

