<?php

/**
 * @todo
 * Where do the user enter the interest periode and preferred branch
 * information. (THIS IS NOT IMPLEMENTED YET, SO DEFAULT IS USED)
 */



function alma_reservation_options($type, $account, $reservables) {
  /*
   * While we use ding_reservation for branch handling, we don't want to
   * depend on the module, as it would mean that ding_reservation can't be
   * disabled. So instead we throw an exception here.
   */

  if (!module_exists('ding_reservation')) {
    throw new Exception('Alma reservation options requires ding_reservation.');
  }  

  $form = array();
  $profile = ding_user_provider_profile($account);

  $branches =  alma_reservation_pickup_branches($account);
  // @todo; use local branches from issue - some migth not be available in all branches

  if(ding_user_is_provider_user($account)) {
    $preferred_branch = $profile->alma_preferred_branch[field_language('profile2', $profile, 'alma_preferred_branch')][0]['value'];
  }
  else {
    $preferred_branch = NULL;
  }
  
  $form += ding_reservation_default_options_branch($type, 'alma_preferred_branch',$preferred_branch, $branches);

  return $form;
}


/**
 * Validate reservations options.
 */
function alma_reservation_options_validate($type, $account, $reservables, $values) {
  $result = array();
  $profile = ding_user_provider_profile($account);
  $field_language = field_language('profile2', $profile);
  $profile_branch = $profile->alma_preferred_branch[$field_language['alma_preferred_branch']][0]['value'];
  return ding_reservation_default_options_branch_validate($type, 'alma_preferred_branch', $profile_branch, $values);
}

/**
 * Submit handler for reservations options.
 */
function alma_reservation_options_submit($type, $account, $reservables, $values) {
  $profile = ding_user_provider_profile($account);
  $field_language = field_language('profile2', $profile);
  $profile_branch = $profile->alma_preferred_branch[$field_language['alma_preferred_branch']][0]['value'];
  $update = ding_reservation_default_options_branch_submit($type, 'alma_preferred_branch', $profile_branch, $values);
  if (!empty($update['alma_preferred_branch'])) {
    $profile->alma_preferred_branch[$field_language['alma_preferred_branch']][0]['value'] = $update['alma_preferred_branch'];
    $profile->save();
  }
}

/**
 * Set preferred pickup branch
 */
function alma_reservation_set_preferred_branch($account, $branch) {
  // Throws an exception if we are not logged in.
  $creds = ding_user_get_creds($account);

  /**
   * @todo Should call alma an update the branch in the library system (not sure
   * if branch has the right format).
   */
  //alma_client_invoke('get_reservations', $creds['name'], $creds['pass'], $branch);
}

/**
 * Get list of reserved items.
 */
function alma_reservation_list($account) {
  $creds = ding_user_get_creds($account);
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
        'pickup_date' => $reservation['pickup_expire_date'],
        'created' => $reservation['create_date'],
        'expiry' => $reservation['valid_to'],
        'queue_number' => $reservation['queue_number'],
        'ready_for_pickup' => 1,
      ));
    }
    else {
      $result[$reservation['id']] = new DingProviderReservation($reservation['id'], array(
        'order_id' => $reservation['id'],
        'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation['record_id'],
        'pickup_branch_id' => $reservation['pickup_branch'],
        'created' => $reservation['create_date'],
        'expiry' => $reservation['valid_to'],
        'queue_number' => $reservation['queue_number'],
        'ready_for_pickup' => 0,
      ));
    }
  }

  return $result;
}

 /**
 * Create a reservation for a given account.
 */
function alma_reservation_create($account, $id, $branch, $expiry=null) {
  $creds = ding_user_get_creds($account);
  // Check if the users has this reservation and throw exception.
  //if (alma_reservation_exists($creds, $id)) {
  if( alma_reservation_exists($account, $id) ){
    throw new DingProviderReservationExists();
  }

  $profile2 = profile2_load_by_user($account,'provider_alma');
  if( !empty($profile2) ) {
    // interest period
    if( !isset($expiry) ) {
      // get interest period from profile2
      $interest_period = alma_get_interest_period($profile2);
      if( $interest_period ){	
	$expiry = REQUEST_TIME + ($interest_period['key'] * 24 * 60 * 60 );
      }       
    }    
    if( !isset($expiry) ) {
      $expiry = REQUEST_TIME + DING_RESERVATION_DEFAULT_INTEREST_PERIOD;
    }

    // preferred branch
    if( empty($branch) ) {
      $pref_branch = alma_get_preferred_branch($profile2);
      if( $pref_branch ){
	$branches = alma_reservation_pickup_branches();
	foreach($branches as $key => $val){
	  if( $val == $pref_branch ) {
	    $branch = $key;
	    break;	    
	  }
	}
      }
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
      'queue_number' => $result,
    );
  }
  else {
    throw new DingProviderReservationNotAvailable();
  }
}

/**
 * Update order, by defining new expiry date or pickup branch.
 */
function alma_reservation_update($account, $ids, $options) {
  $creds = ding_user_get_creds($account);
  $reservations = alma_reservation_get_reservations($account);
  foreach($ids as $id) {
    if (isset($reservations[$id])) {
      $expiry_date = !empty($options['expiry']) ? alma_reservation_format_date($options['expiry']) : $reservations[$id]['valid_to'];
      $pickup_branch = !empty($options['alma_preferred_branch']) ? $options['alma_preferred_branch'] : $reservations[$id]['pickup_branch'];
      $changes = array(
        'valid_to' => $expiry_date,
        'pickup_branch' => $pickup_branch,
      );
      // Alma do not return a status.
      alma_client_invoke('change_reservation', $creds['name'], $creds['pass'], $reservations[$id], $changes);
    }
    alma_reservation_clear_cache();
    return TRUE;
  }

  return FALSE;
}

/**
 * Delete a reservation for a given account.
 */
function alma_reservation_delete($account, $id) {
  $creds = ding_user_get_creds($account);
  $reservations = alma_reservation_get_reservations($account);
  
  alma_reservation_clear_cache();
  if( isset($reservations[$id]) ) {
    return alma_client_invoke('remove_reservation', $creds['name'], $creds['pass'], $reservations[$id]);
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
  if (isset($organisation['branch'][$branch_id])) {
    return $organisation['branch'][$branch_id];
  }
  return NULL;
}

/**********************************
 * Helper functions
 */

function alma_reservation_get_reservations($account, $reset = FALSE) {
  $creds = ding_user_get_creds($account);

  // Try to look in the session for reservation information.
  if (!isset($_SESSION['alma_reservations']) || !is_array($_SESSION['alma_reservations']) || $reset) {
    $_SESSION['alma_reservations'] = alma_client_invoke('get_reservations', $creds['name'], $creds['pass']);
  }

  return $_SESSION['alma_reservations'];
}

function alma_reservation_clear_cache() {
  unset($_SESSION['alma_reservations']);
}

function alma_reservation_exists($account, $item_id) {
  $reservations = alma_reservation_get_reservations( $account );
  foreach ($reservations as $res) {
    if ($res['record_id'] == $item_id) {
      return TRUE;
    }
    return FALSE;
  }
}

function alma_reservation_format_date($datetime) {
  $timestamp = (!is_int($datetime)) ? strtotime($datetime) : $datetime;
  return date('Y-m-d', $timestamp);
}
