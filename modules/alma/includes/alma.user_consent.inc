<?php
/**
 * @file
 * Implements the alma user consent interface. When a user gives permission to store his or her loan history for longer than 30 days
 * the user category is changed to reflect the new status. If the permission is revoked then the user category is changed back to the original.
 */

/**
 * Retrieve an array of user consent options
 * The return value is an array of consent options, containing a title and a description of the option.
 *
 * @return $alma_user_consent_info Array
 */
function alma_user_consent_info() {
  return array(
    'loan_history_store' => array(
      'title' => t('Personalisation'),
      'description' => t('In order to use this function, we request your permission to store your personal information'),
      'required' => TRUE,
    ),
  );
}

/**
 * Update the user consent
 * The return value is TRUE or FALSE depending on the success of the request.
 *
 * @param $account Object
 * @param $consent String
 * @param $previous_consents Boolean
 *
 * @return $status Boolean
 */
function alma_user_consent_add($account, $consent, $previous_consents) {
  switch($consent) {
    case 'loan_history_store':
      $creds = ding_user_get_creds($account);
      $patron = alma_get_patron($creds);
      if (isset($patron->category)) {
        // Changes mapped from the category structure in Axiell.
        $new_category = alma_user_consent_get_category_change($consent);
        // Alma do not return a status.
        $res = alma_client_invoke('add_user_consent', $creds['name'], $creds['pass'], $new_category);
        return ($res == 'ok');
      }
      break;
  }
  return FALSE;
}

/**
 * Delete the users consent.
 * The return value is TRUE or FALSE depending on the success of the request.
 *
 * @param $account Object
 * @param $consent String
 * @param $previous_consents Boolean
 *
 * @return $status Boolean
 */
function alma_user_consent_remove($account, $consent, $previous_consents) {
  switch($consent) {
    case 'loan_history_store':
      $creds = ding_user_get_creds($account);
      $patron = alma_get_patron($creds);
      if (isset($patron->category)) {
        // Changes mapped from the category structure in Axiell.
        $new_category = alma_user_consent_get_category_change($consent);
        // Alma do not return a status.
        $res = alma_client_invoke('remove_user_consent', $creds['name'], $creds['pass'], $new_category);
        return ($res == 'ok');
      }
      break;
  }
  return FALSE;
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
 * @return $alma_user_consent Array
 */
function alma_user_consent_get_consent($account) {
  try{
    $creds = ding_user_get_creds($account);
  }
  catch (DingProviderAuthException $e) {
    return NULL;
  }
  $patron = alma_get_patron($creds, TRUE);
  if(ding_user_is_provider_user($account)) {
    $consents = alma_user_consent_info();
    $return = array();
    foreach($consents as $id => $values) {
      $new_category = alma_user_consent_get_category_change($id);
      if(isset($patron->allows))
        $return[$id] = isset($patron->allows[$new_category]);
      else
        $return[$id] = 0;
    }
    return $return;
  }
}

/**
 * Get the category which matches the current when changing.
 * @alma currently only supports one type of consent.
 *
 * @param $category String
 *
 * @return String
 */
function alma_user_consent_get_category_change($category) {
  $consent_categories = array(
    'loan_history_store' => 'keepLoan',
  );
  return $consent_categories[$category];
}
