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
 * Get dept counts.
 */
function ddbasic_account_count_depts($account = NULL) {
  $sc = &drupal_static(__FUNCTION__, array());

  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  if (!isset($sc[$account->uid])) {
    $sc[$account->uid] = count(ding_provider_invoke('debt', 'list', $account));
  }

  return $sc[$account->uid];
}

/**
 * Get overdue loan counts.
 */
function ddbasic_account_count_loans($account = NULL) {
  $sc = &drupal_static(__FUNCTION__, array());

  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  if (!isset($sc[$account->uid])) {
    $sc[$account->uid] = count(ding_provider_invoke('loan', 'list', $account));
  }

  return $sc[$account->uid];
}

/**
 * Get overdue loan counts.
 */
function ddbasic_account_count_overdue_loans($account = NULL) {
  $sc = &drupal_static(__FUNCTION__, array());

  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  if (!isset($sc[$account->uid])) {
    $loans = ding_provider_invoke('loan', 'list', $account);
    $sc[$account->uid] = 0;
    $today = date('Y-m-d', REQUEST_TIME);

    foreach ($loans as $loan) {
      if ($loan->expiry < $today) {
        $sc[$account->uid]++;
      }
    }
  }

  return $sc[$account->uid];
}

/**
 * Get dept counts.
 */
function ddbasic_account_count_reservation_ready($account = NULL) {
  $sc = &drupal_static(__FUNCTION__, array());

  if (empty($account)) {
    $account = $GLOBALS['user'];
  }

  if (!isset($sc[$account->uid])) {
    $sc[$account->uid] = count(ding_provider_invoke('reservation', 'list', $account, DING_RESERVATION_READY));
  }

  return $sc[$account->uid];
}
