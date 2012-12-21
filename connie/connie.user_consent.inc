<?php

function connie_user_consent_info() {
 return array(
   'loan_history_store' => array(
     'title' => t('Allow saving the loan history for more than 30 days'),
     'description' => t('Your loan history will be saved lorem ipsum dolor...'),
     'options' => array(1 => t('Store loan history')),
   ),
 );
}

// Example of hook_user_consent_update() that store consent in connie.
function connie_user_consent_update($account, $consent_id, $value) {
  //$creds = ding_user_get_creds($account);
  $_SESSION['connie_user_consent'][$account->uid][$consent_id] = $value;
  return $_SESSION['connie_user_consent'][$account->uid][$consent_id];
}

/**
 * Helper functions
 */

/**
 * Retrieve any consent record which the user has saved.
 * The return value is an array of consent arrays sorted by the date they were accepted.
 *
 * @param $account Object
 * @param $reset Boolean
 *
 * @return $connie_user_consent Array
 */
function connie_user_consent_get_consent($account, $reset = FALSE) {
  //$creds = ding_user_get_creds($account);
  
  // Try to look in the session for reservation information.
  if (!isset($_SESSION['connie_user_consent'][$account->uid]) || !is_array($_SESSION['connie_user_consent']) || $reset) {
    $_SESSION['connie_user_consent'] = array();
    $_SESSION['connie_user_consent'][$account->uid] = array(); //'loan_history_store' => 0, 'record_id' => $account->uid
  }
  
  return $_SESSION['connie_user_consent'][$account->uid];
}
