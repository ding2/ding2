<?php
/**
 * @file
 * Implements the user consent interface.
 *
 * When a user gives permission to store his or her loan history for longer
 * than 30 days the user category is changed to reflect the new status. If the
 * permission is revoked then the user category is changed back to the
 * original.
 */

/**
 * Retrieve an array of user concent options.
 *
 * The return value is an array of consent options, containing a title and a
 * description of the option.
 *
 * @return array
 *   Array of name => consent.
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
 * Retrieve any consent record which the user has saved.
 *
 * The return value is an array of consent arrays sorted by the date they were
 * accepted.
 *
 * @param object $account
 *   User to get consent for.
 *
 * @return array
 *   Array of consent => value.
 */
function connie_user_consent_get_consent($account) {
  if (isset($account->data['connie_consent'])) {
    return $account->data['connie_consent'];
  }

  return array();
}

/**
 * Update the user consent.
 *
 * The return value is TRUE or FALSE depending on the success of the request.
 *
 * @param object $account
 *   User account to add consent for.
 * @param string $consent
 *   Consent name.
 * @param bool $previous_consents
 *   Previous consent value.
 *
 * @return bool
 *   Whether the consent was set successfully.
 */
function connie_user_consent_add($account, $consent, $previous_consents) {
  $account->data['connie_consent'][$consent] = TRUE;
  return (bool) user_save($account);
}

/**
 * Delete the users consent.
 *
 * The return value is TRUE or FALSE depending on the success of the request.
 *
 * @param object $account
 *   User to remove consent for.
 * @param string $consent
 *   Consent name.
 * @param bool $previous_consents
 *   Previous consent value.
 *
 * @return bool
 *   Whether the consent was removed successfully.
 */
function connie_user_consent_remove($account, $consent, $previous_consents) {
  unset($account->data['connie_consent'][$consent]);
  return (bool) user_save($account);
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
