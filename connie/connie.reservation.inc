<?php

/**
 * @file
 * Ding reservation provider example.
 */

/**
 *
 */
function connie_reservation_pickup_branches($account) {
  return array(
    'aby' => 'Andeby bibliotek',
    'grd' => 'Gåserød bibliotek',
  );
}

/**
 *
 */
function connie_reservation_set_preferred_branch($account, $branch) {
  // Do nothing, ding_reservation will update local user if we don't throw an
  // exception.
}

/**
 *
 */
function connie_reservation_list($account) {
  $result = array();
  if (isset($_SESSION['connie_reservations'])) {
    foreach ($_SESSION['connie_reservations'] as $id => $res) {
      $result[$id] = array(
        'id' => $id,
        'provider_id' => $res[0],
        'display_title' => $res[1],
        'pickup_branch' => $res[2],
        'expiry' => $res[3],
      );
    }
  }
  return $result;
}

/**
 *
 */
function connie_reservation_create($account, $id, $branch, $expiry) {
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
  if (isset($_SESSION['connie_reservations']) && isset($_SESSION['connie_reservations'][$id])) {
    unset($_SESSION['connie_reservations'][$id]);
  }
}

/**
 *
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
