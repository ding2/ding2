<?php
/**
 * @file
 * Implements the openruth user consent interface.
 *
 * When a user gives permission to store his or her loan history for longer
 * than 30 days the user category is changed to reflect the new status. If the
 * permission is revoked then the user category is changed back to the
 * original.
 *
 * TODO: Implement this when openruth supports user consent.
 */

/**
 * Retrieve an array of user consent options.
 *
 * @return array
 *   An array of consent options, containing a title and a description of the
 *   option.
 */
function openruth_user_consent_info() {
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
function openruth_user_consent_add($account, $consent) {
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
function openruth_user_consent_remove($account, $consent) {
  return FALSE;
}

/**
 * Retrieve any consent record which the user has saved.
 *
 * @param object $account
 *   The user account.
 *
 * @return array
 *   An array of consent arrays sorted by the date they were accepted.
 */
function openruth_user_consent_get_consent($account) {
  return array();
}

/**
 * Get the category which matches the current when changing.
 *
 * @param string $category
 *   Category.
 *
 * @return string
 *   Category name.
 */
function openruth_user_consent_get_category_change($category) {
  $consent_categories = array(
    'loan_history_store' => 'keepLoan',
  );
  return $consent_categories[$category];
}
