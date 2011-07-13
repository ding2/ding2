<?php

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
  // Throw exception if we're not logged in.
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }
  // Do nothing, ding_reservation will update local user if we don't throw an exception.

  // @todo Should call alma an update the branch in the library system.

}

/**
 * Get list of reserved items
 */
 function alma_reservation_list($account) {
   $creds = ding_user_get_creds();
   $reservations = alma_client_invoke('get_reservations', $creds['name'], $creds['pass']);
   $result = array();
//   var_dump($reservations);

   // Create DingProviderReservation objects.
   foreach ($reservations as $reservation) {
     if (isset($reservation['pickup_number'])) {
       $result[$reservation['record_id']] = new DingProviderReservation($reservation['record_id'], array(
         'order_id' => $reservation['record_id'],
         'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation['id'],
         'display_name' => 'TEST', // FIXME
         'pickup_date' => $reservation['pickup_expire_date'],
         'pickup_branch_id' => 1, // FIXME
         'created' => $reservation['create_date'],
         'expiry' => $reservation['valid_to'],
         'queue_number' => $reservation['queue_number'],
         'ready_for_pickup' => 1,
       ));
     }
     else {
       $result[$reservation['record_id']] = new DingProviderReservation($reservation['record_id'], array(
         'order_id' => $reservation['record_id'],
         'ding_entity_id' => variable_get('ting_agency', '') . ':' . $reservation['id'],
         'display_name' => 'TEST', // FIXME
         'pickup_date' => $reservation['pickup_expire_date'],
         'pickup_branch_id' => 1, // FIXME
         'created' => $reservation['create_date'],
         'queue_number' => $reservation['queue_number'],
         'ready_for_pickup' => 0,
       ));
     }
   }

   var_dump($result);
   return $result;
 }

 /**
 * Create a reservation for a given account
 */
function alma_reservation_create($account, $id, $branch, $expiry) {

}

/**
 * Update order, by defining new expiry date or pickup branch
 */
function alma_reservation_update_order($account, $order_id, $pickup_branch, $expiry_date) {

}

/**
 * Delete a reservation for a given account
 */
function alma_reservation_delete($account, $id) {

}

/**
 * Return a branch name for a given branch id
 *
 * @param $branch_id String
 * @return String
 */
function alma_reservation_branch_name($branch_id) {

}