<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Function for adding classes to body element.
 */
function ddbasic_body_class($class = array()) {
  $classes = &drupal_static(__FUNCTION__, array());
  if (!empty($class)) {
    if (!is_array($class)) {
      $class = array($class);
    }
    $classes = array_merge($classes, $class);
  }
  return $classes;
}

/**
 * Get the total amount of depts the user has.
 */
function ddbasic_account_count_depts($account = NULL) {
  // Prepare the static cache.
  $depts = &drupal_static(__FUNCTION__, array());

  // Default the $account to the currently logged in user.
  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  // If the user have no hits in the static cache, count the depts.
  if (!isset($depts[$account->uid])) {
    $depts[$account->uid] = count(ding_provider_invoke('debt', 'list', $account));
  }

  return $depts[$account->uid];
}

/**
 * Get the total amount of loans the user has.
 */
function ddbasic_account_count_loans($account = NULL) {
  // Prepare the static cache.
  $loans = &drupal_static(__FUNCTION__, array());

  // Default the $account to the currently logged in user.
  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  // If the user have no hits in the static cache, count the total loans.
  if (!isset($loans[$account->uid])) {
    $loans[$account->uid] = count(ding_provider_invoke('loan', 'list', $account));
  }

  return $loans[$account->uid];
}

/**
 * Get the total amount of loans the user has.
 */
function ddbasic_account_count_overdue_loans($account = NULL) {
  // Prepare the static cache.
  $overdue_loans = &drupal_static(__FUNCTION__, array());

  // Default the $account to the currently logged in user.
  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  // If the user have no hits in the static cache, count the overdue loans.
  if (!isset($overdue_loans[$account->uid])) {
    $loans = ding_provider_invoke('loan', 'list', $account);
    $overdue_loans[$account->uid] = 0;
    $today = date('Y-m-d', REQUEST_TIME);

    foreach ($loans as $loan) {
      if ($loan->expiry < $today) {
        $overdue_loans[$account->uid]++;
      }
    }
  }

  return $overdue_loans[$account->uid];
}

/**
 * Get the total amount of ready reservations the user has.
 */
function ddbasic_account_count_reservation_ready($account = NULL) {
  // Prepare the static cache.
  $reservations = &drupal_static(__FUNCTION__, array());

  // Default the $account to the currently logged in user.
  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  // If the user have no hits in the static cache, count the ready reservations.
  if (!isset($sc[$account->uid])) {
    $reservations[$account->uid] = count(ding_provider_invoke('reservation', 'list', $account, DING_RESERVATION_READY));
  }

  return $reservations[$account->uid];
}
