<?php

/**
 * @todo
 * Where do the user enter the interest periode and preferred branch
 * information. (THIS IS NOT IMPLEMENTED YET, SO DEFAULT IS USED)
 */
 

/**
 * Get list of pickup branches.
 */
function alma_reservation_pickup_branches($account) {
  // Throw exception if we're not logged in.
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }

  return alma_client_invoke('get_reservation_branches');
}

/**
 * Set preferred pickup branch
 */
function alma_reservation_set_preferred_branch($account, $branch) {
  // Throws an exception if we are not logged in.
  $creds = ding_user_get_creds($account, TRUE);

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
   $creds = ding_user_get_creds($account, TRUE);
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
function alma_reservation_create($account, $id, $branch, $expiry) {
  $creds = ding_user_get_creds($account, TRUE);

  // Check if the users has this reservation and throw exception.
  if (alma_reservation_exists($creds, $id)) {
    throw new DingProviderReservationExists();
  }

  // Build the reservation parameters to send.
  $params = array(
    'id' => $id,
    'valid_from' => date('Y-m-d'),
    'valid_to' => alma_reservation_format_date($expiry),
    'pickup_branch' => $branch,
  );

  // Try to make the reservation.
  $result = alma_client_invoke('add_reservation', $creds['name'], $creds['pass'], $params);

  if ($result === ALMA_AUTH_BLOCKED) {
    /**
     * @todo return better exception that informs the user about the block
     * status.
     */
    throw new DingProviderReservationNotAllowed();
  }

  if ($result) {
    // Reset session cache
    alma_reservation_clear_cache();
    return array($id => TRUE);
  }
  else {
    throw new DingProviderReservationNotAvailable();
  }
}

/**
 * Update order, by defining new expiry date or pickup branch.
 */
function alma_reservation_update_order($account, $id, $pickup_branch, $expiry_date) {
  $creds = ding_user_get_creds($account, TRUE);
  $reservations = alma_reservation_get_reservations($account);
  if (isset($reservations[$id])) {
    $changes = array(
      'valid_to' => alma_reservation_format_date($expiry_date),
      'pickup_branch' => $pickup_branch,
    );
    // Alma do not return a status.
    alma_client_invoke('change_reservation', $creds['name'], $creds['pass'], $reservations[$id], $changes);
    alma_reservation_clear_cache();
    return TRUE;
  }

  return FALSE;
}

/**
 * Delete a reservation for a given account.
 */
function alma_reservation_delete($account, $id) {
  $creds = ding_user_get_creds($account, TRUE);
  $reservations = alma_reservation_get_reservations($account);
  alma_reservation_clear_cache();
  //return alma_client_invoke('remove_reservation', $creds['name'], $creds['pass'], $reservations[$id]);
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
  $creds = ding_user_get_creds($account, TRUE);

  // Try to look in the session for reservation information.
  if (!isset($_SESSION['alam_reservations']) || !is_array($_SESSION['alam_reservations']) || $reset) {
    $_SESSION['alam_reservations'] = alma_client_invoke('get_reservations', $creds['name'], $creds['pass']);
  }
  
  return $_SESSION['alam_reservations'];
}

function alma_reservation_clear_cache() {
  unset($_SESSION['alam_reservations']);
}

function alma_reservation_exists($creds, $item_id) {
  $reservations = alma_client_invoke('get_reservations', $creds['name'], $creds['pass']);
  foreach ($reservations as $res) {
    if ($res['record_id'] == $item_id) {
      return TRUE;
    }
  }
  return FALSE;
}

function alma_reservation_format_date($datetime) {
  $timestamp = (!is_int($datetime)) ? strtotime($datetime) : $datetime;
  return date('Y-m-d', $timestamp);
}