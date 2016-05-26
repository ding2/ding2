<?php
/**
 * @file
 * Implements the alma user consent interface.
 *
 * When a user gives permission to store his or her loan history for longer
 * than 30 days the user category is changed to reflect the new status. If the
 * permission is revoked then the user category is changed back to the
 * original.
 */

/**
 * Retrieve an array of user consent options.
 *
 * @return array
 *   An array of consent options, containing a title and a description of the
 *   option.
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
 * Update the user consent.
 *
 * @param object $account
 *   User account.
 * @param string $consent
 *   Consent category.
 *
 * @return bool
 *   TRUE or FALSE depending on the success of the request.
 */
function alma_user_consent_add($account, $consent) {
  switch ($consent) {
    case 'loan_history_store':
      $creds = ding_user_get_creds($account);
      $patron = alma_get_patron($creds);
      if (isset($patron->category)) {
        // Changes mapped from the category structure in Axiell.
        $new_category = alma_user_consent_get_category_change($consent);
        return alma_client_invoke('add_user_consent', $creds['name'], $creds['pass'], $new_category);
      }
      break;
  }
  return FALSE;
}

/**
 * Delete the users consent.
 *
 * @param object $account
 *   User account.
 * @param string $consent
 *   Consent category.
 *
 * @return bool
 *   TRUE or FALSE depending on the success of the request
 */
function alma_user_consent_remove($account, $consent) {
  switch ($consent) {
    case 'loan_history_store':
      $creds = ding_user_get_creds($account);
      $patron = alma_get_patron($creds);
      if (isset($patron->category)) {
        // Changes mapped from the category structure in Axiell.
        $new_category = alma_user_consent_get_category_change($consent);
        return alma_client_invoke('remove_user_consent', $creds['name'], $creds['pass'], $new_category);
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
 *
 * @param object $account
 *   The user account.
 *
 * @return array
 *   An array of consent arrays sorted by the date they were accepted.
 */
function alma_user_consent_get_consent($account) {
  try {
    $creds = ding_user_get_creds($account);
  }
  catch (DingProviderAuthException $e) {
    return NULL;
  }
  $patron = alma_get_patron($creds, TRUE);
  if (ding_user_is_provider_user($account)) {
    $consents = alma_user_consent_info();
    $return = array();
    foreach ($consents as $id => $values) {
      $new_category = alma_user_consent_get_category_change($id);
      if (isset($patron->allows)) {
        $return[$id] = isset($patron->allows[$new_category]);
      }
      else {
        $return[$id] = 0;
      }
    }
    return $return;
  }
}

/**
 * Get the category which matches the current when changing.
 *
 * Alma currently only supports one type of consent.
 *
 * @param string $category
 *   Category.
 *
 * @return string
 *   Category name.
 */
function alma_user_consent_get_category_change($category) {
  $consent_categories = array(
    'loan_history_store' => 'keepLoan',
  );
  return $consent_categories[$category];
}
