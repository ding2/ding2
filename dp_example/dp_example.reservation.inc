<?php

/**
 * @file
 * Ding reservation provider example.
 */

/**
 *
 */
function dp_example_reservation_pickup_branches($account) {
  return array(
    'aby' => 'Andeby bibliotek',
    'grd' => 'Gåserød bibliotek',
  );
}

/**
 *
 */
function dp_example_reservation_set_preferred_branch($account, $branch) {
  // Do nothing, ding_reservation will update local user if we don't throw an
  // exception.
}

/**
 *
 */
function dp_example_reservation_list($account) {
  $result = array();
  if (isset($_SESSION['dp_example_reservations'])) {
    foreach ($_SESSION['dp_example_reservations'] as $id => $res) {
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
function dp_example_reservation_create($account, $id, $branch, $expiry) {
  // Fake it.
  if (!isset($_SESSION['dp_example_reservations'])) {
    $_SESSION['dp_example_reservations'] = array();
  }
  foreach ($_SESSION['dp_example_reservations'] as $res) {
    if ($id == $res[0]) {
      throw new DingProviderReservationExists();
    }
  }
  $_SESSION['dp_example_reservations'][uniqid()] = array($id, 'Reservation #' . (sizeof($_SESSION['dp_example_reservations']) + 1), $branch, $expiry);
  return;
}

/**
 *
 */
function dp_example_reservation_delete($account, $id) {
  if (isset($_SESSION['dp_example_reservations']) && isset($_SESSION['dp_example_reservations'][$id])) {
    unset($_SESSION['dp_example_reservations'][$id]);
  }
}

/**
 *
 */
function dp_example_reservation_branch_name($branch_id) {
  $branches = array(
    'aby' => 'Andeby bibliotek',
    'grd' => 'Gåserød bibliotek',
  );
  if (isset($branches[$branch_id])) {
    return $branches[$branch_id];
  }
  return NULL;
}
