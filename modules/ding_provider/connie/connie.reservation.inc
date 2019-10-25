<?php

/**
 * @file
 * Ding reservation provider example.
 */

/**
 * Provider pickup_branches callback.
 */
function connie_reservation_pickup_branches($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds();
  return array(
    'aby' => 'Andeby bibliotek',
    'grd' => 'Gåserød bibliotek',
  );
}

/**
 * Provider set_preferred_branch callback.
 */
function connie_reservation_set_preferred_branch($account, $branch) {
  // Throw exception if we're not logged in.
  ding_user_get_creds();
  // Do nothing, ding_reservation will update local user if we don't throw an
  // exception.
}

/**
 * Implements provider reservation default branch.
 *
 * @params object $account
 *   The user to get the default branch for.
 *
 * @return array
 *   An empty array mimicking a default branch is not selected.
 */
function connie_reservation_default_options($account) {
  return array();
}

/**
 * Provider list callback.
 */
function connie_reservation_list($account, $type = NULL) {
  // Throw exception if we're not logged in.
  ding_user_get_creds();
  $result = array(
    DING_RESERVATION_READY => array(),
    DING_RESERVATION_NOT_READY => array(),
    DING_RESERVATION_INTERLIBRARY_LOANS => array(),
  );
  if (isset($_SESSION['connie_reservations'])) {
    foreach ($_SESSION['connie_reservations'] as $id => $res) {
      $result[DING_RESERVATION_READY][$id] = new DingProviderReservation($id, array(
        'ding_entity_id' => ding_provider_build_entity_id($res[0]),
        'display_name' => $res[1],
        'pickup_branch_id' => $res[2],
        'expiry' => $res[3],
        'reservation_type' => DING_RESERVATION_READY,
      ));
    }
  }
  // Fake a remote reservation.
  $result[DING_RESERVATION_INTERLIBRARY_LOANS]['ill-123'] = new DingProviderReservation('ill-123', array(
    'display_name' => 'Remote loan: The algebraist',
    'pickup_branch_id' => 'grd',
    'expiry' => date('Y-m-d', REQUEST_TIME + 86400),
    'ready_for_pickup' => TRUE,
    'reservation_type' => DING_RESERVATION_INTERLIBRARY_LOANS,
  ));

  if (!is_null($type)) {
    if (isset($result[$type])) {
      return $result[$type];
    }
    else {
      watchdog('connie', 'Unknown reservation type (%type) requested', array('%type' => $type), WATCHDOG_ERROR);
      return array();
    }
  }

  return $result;
}

/**
 * Provide options for reservation.
 */
function connie_reservation_options($account, $default_branch = NULL) {
  /*
   * While we use ding_reservation for branch handling, we don't want to
   * depend on the module, as it would mean that ding_reservation can't be
   * disabled. So instead we throw an exception here.
   */
  if (!module_exists('ding_reservation')) {
    throw new Exception('Connie reservation options requires ding_reservation.');
  }
  $preferred_branch = NULL;

  if (ding_user_is_provider_user($account)) {
    $profile = ding_user_provider_profile($account);
    if (isset($profile->connie_preferred_branch[LANGUAGE_NONE][0]['value'])) {
      $preferred_branch = $profile->connie_preferred_branch[LANGUAGE_NONE][0]['value'];
    }
    elseif (!empty($default_branch)) {
      $preferred_branch = $default_branch;
    }
  }

  $form = array();
  $form += ding_reservation_default_options_branch(
    'connie_preferred_branch',
    $preferred_branch,
    connie_allowed_branches()
  );

  return $form;
}

/**
 * Validate reservations options.
 */
function connie_reservation_options_validate($type, $account, $reservables, $values) {
  return ding_reservation_default_options_branch_validate($type, 'openruth_preferred_branch', $profile_branch, $values);
}

/**
 * Submit handler for reservations options.
 */
function connie_reservation_options_submit($account, $update) {
  $profile = ding_user_provider_profile($account);
  $field_language = field_language('profile2', $profile);

  if (!empty($update['connie_preferred_branch'])) {
    $profile->connie_preferred_branch[$field_language['connie_preferred_branch']][0]['value'] = $update['connie_preferred_branch'];
    $profile->save();
  }
}

/**
 * Provider create callback.
 */
function connie_reservation_create($account, $id, $options) {
  $branch = $options['connie_preferred_branch'];
  $expiry = REQUEST_TIME + 180;
  // Throw exception if we're not logged in.
  ding_user_get_creds();
  // Fake it.
  if (!isset($_SESSION['connie_reservations'])) {
    $_SESSION['connie_reservations'] = array();
  }
  foreach ($_SESSION['connie_reservations'] as $res) {
    if ($id == $res[0]) {
      //throw new DingProviderReservationExists();
    }
  }
  $_SESSION['connie_reservations'][uniqid()] = array($id, 'Reservation #' . (sizeof($_SESSION['connie_reservations']) + 1), $branch, date('Y-m-d', $expiry));
  return array('branch' => $branch);
}

/**
 * Provider delete callback.
 */
function connie_reservation_delete($account, $id) {
  // Throw exception if we're not logged in.
  ding_user_get_creds();
  if (isset($_SESSION['connie_reservations']) && isset($_SESSION['connie_reservations'][$id])) {
    unset($_SESSION['connie_reservations'][$id]);
  }
}

/**
 * Provider branch_name callback.
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

/**
 * Implements provider reservation, is_reservable.
 */
function connie_reservation_is_reservable($provider_ids) {
  // Make everything reservable.
  return array_fill_keys($provider_ids, TRUE);
}
