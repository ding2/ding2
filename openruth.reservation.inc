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
   $creds = ding_user_get_creds($account);
   $result = array();
   $status = _openruth_user_status($creds);

   if (isset($status->orders->orderReady)) {
     foreach ($status->orders->orderReady as $res) {
       $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
         'order_id' => $res->orderId,
         'ding_entity_id' => variable_get('ting_agency', '') . ':' . $res->itemId,
         'display_name' => $res->itemDisplayTitle,
         'pickup_date' => $res->orderPickUpDate,
         'pickup_branch_id' => $res->agencyCounter,
         'created' => $res->orderDate,
         'ready_for_pickup' => 1,
       ));
     }
   }
   if (isset($status->orders->orderNotReady)) {
     foreach ($status->orders->orderNotReady as $res) {
       $result[$res->orderId] = new DingProviderReservation($res->orderId, array(
         'ding_entity_id' => variable_get('ting_agency', '') . ':' . $res->itemId,
         'display_name' => $res->itemDisplayTitle,
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
 * Create a reservation for a given account
 */
function openruth_reservation_create($account, $id, $branch, $expiry) {
  $creds = ding_user_get_creds($account);
  $status = _openruth_user_status($creds, TRUE);

  $internal_account = ding_user_get_creds($account);
  $order_res = openruth_client_invoke('order_item', $internal_account['name'], $id, 1, date('c', time()), date('c', $expiry), $branch);
  $order = array_shift($order_res);
  if ($order === 1) {
    $status = _openruth_user_status($creds, TRUE);
    return $order_res;
  }
  else {
    throw new DingProviderUserException(t('Error: ' . $order));
  }
}

/**
 * Update order, by defining new expiry date or pickup branch
 */
function openruth_reservation_update_order($account, $order_id, $pickup_branch, $expiry_date) {
  $creds = ding_user_get_creds($account);

  $res = openruth_client_invoke('update_order', $order_id, $pickup_branch, $expiry_date);

  if ($res == TRUE) {
    $status = _openruth_user_status($creds, TRUE);
  }
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
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }

  $branches = openruth_client_invoke('get_agencycounters');
  if (isset($branches[$branch_id])) {
    return $branches[$branch_id];
  }
  return NULL;
}

