<?php

/**
 * @file
 * Ding reservation provider example.
 */

/**
 *
 */
function connie_reservation_pickup_branches($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  return array(
    'aby' => 'Andeby bibliotek',
    'grd' => 'Gåserød bibliotek',
  );
  }

/**
 *
 */
function connie_reservation_set_preferred_branch($account, $branch) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  // Do nothing, ding_reservation will update local user if we don't throw an
  // exception.
}

/**
 *
 */
function connie_reservation_list($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  $result = array();
  if (isset($_SESSION['connie_reservations'])) {
    foreach ($_SESSION['connie_reservations'] as $id => $res) {
      $result[$id] = new DingProviderReservation($id, array(
                       'ding_entity_id' => variable_get('ting_agency', '') . ':' . $res[0],
                       'display_name' => $res[1],
                       'pickup_branch_id' => $res[2],
                       'expiry' => $res[3],
                     ));
    }
  }
  return $result;
}

/**
 *
 */
function connie_reservation_create($account, $id, $branch, $expiry) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  // Fake it.
  if (!isset($_SESSION['connie_reservations'])) {
    $_SESSION['connie_reservations'] = array();
  }
  foreach ($_SESSION['connie_reservations'] as $res) {
    if ($id == $res[0]) {
      throw new DingProviderReservationExists();
    }
  }
  $_SESSION['connie_reservations'][uniqid()] = array($id, 'Reservation #' . (sizeof($_SESSION['connie_reservations']) + 1), $branch, $expiry);
  return;
}

/**
 *
 */
function connie_reservation_delete($account, $id) {
  // Throw exception if we're not logged in.
  ding_user_get_creds($account);
  if (isset($_SESSION['connie_reservations']) && isset($_SESSION['connie_reservations'][$id])) {
    unset($_SESSION['connie_reservations'][$id]);
  }
}

/**
 *
 * Should cache the result of external requests internally, as it
 * might be called multiple times with the same parameters in the same
 * request.
 */
function connie_reservation_branch_name($branch_id) {
  $branches = array(
    'aby' => 'Andeby bibliotek',
    'grd' => 'Gåserød bibliotek',
  );
  if (isset($branches[$branch_id])) {
    return $branches[$branch_id];
  }
  return NULL;
}
