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
function dp_example_reservation_create($account, $id) {
  // Fake it.
  if (!isset($_SESSION['dp_example_reservations'])) {
    $_SESSION['dp_example_reservations'] = array();
  }
  $_SESSION['dp_example_reservations'][] = array('Reservation #' . (sizeof($_SESSION['dp_example_reservations']) + 1), $account->data['preferred_branch']);
  return;
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
