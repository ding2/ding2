<?php

/**
 * Get list of pickup branches
 */
function openruth_reservation_pickup_branches($account) {
  // Throw exception if we're not logged in.
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }

  $branches = openruth_client_invoke('get_agencycounters');
  return $branches;
}

/**
 * Set preferred pickup branch
 */
function openruth_reservation_set_preferred_branch($account, $branch) {
  // Throw exception if we're not logged in.
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }
  // Do nothing, ding_reservation will update local user if we don't throw an exception.
}

/**
 * Get list of reserved items
 */
 function openruth_reservation_list($account) {
   $result = array();
   // Throw exception if we're not logged in.
   if (!ding_user_get_creds()) {
     throw new DingProviderAuthException;
   }
   $internal_account = ding_user_get_creds($account);
   $reservations = openruth_client_invoke('user_status', $internal_account['name'], $internal_account['pass']);
   if (isset($reservations->orders->orderNotReady)) {
     foreach ($reservations->orders->orderNotReady as $res) {
       $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
         'ding_entity_id' => $res->itemId,
         'display_name' => $res->itemDisplayTitle,
         'pickup_branch_id' => $res->agencyCounter,
         'expiry' => $res->orderLastInterestDate,
         'created' => $res->orderDate,
         'queue_number' => $res->orderQueuePosition,
       ));
     }
   }
   return $result;
 }

/**
 * Create a reservation for a given account
 */
function openruth_reservation_create($account, $id, $branch, $expiry) {
  // Throw exception if we're not logged in.
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }
  $internal_account = ding_user_get_creds($account);
  $booking = openruth_client_invoke('order_item', $internal_account['name'], $id, 1, date('c', time()), date('c', $expiry), $branch);
  if ($booking[$id] == 1) {
    return $booking;
  }
  else {
    throw new DingProviderUserException(t('Error: ' . $booking[$id]));
  }
}

/**
 * Delete a reservation for a given account
 */
function openruth_reservation_delete($account, $id) {
  // Throw exception if we're not logged in.
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }
  $res = openruth_client_invoke('cancel_order', $id);
}

/**
 * Return a branch name for a given branch id
 *
 * @param $branch_id String
 * @return String
 */
function openruth_reservation_branch_name($branch_id) {
  // Throw exception if we're not logged in.
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }

  $branches = openruth_client_invoke('get_agencycounters');
  if (isset($branches[$branch_id])) {
    return $branches[$branch_id];
  }
  return NULL;
}

