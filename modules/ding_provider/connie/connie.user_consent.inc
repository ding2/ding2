<?php
/**
 * @file
 * Implements the connie user consent interface.
 */

/**
 * Retrieve an array of user consent options.
 *
 * @return array
 *   An array of consent options, containing a title and a description of the
 *   option.
 */
function connie_user_consent_info() {
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
function connie_user_consent_add($account, $consent) {
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
function connie_user_consent_remove($account, $consent) {
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
function connie_user_consent_get_consent($account) {
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
function connie_user_consent_get_category_change($category) {
  $consent_categories = array(
    'loan_history_store' => 'keepLoan',
  );
  return $consent_categories[$category];
}
