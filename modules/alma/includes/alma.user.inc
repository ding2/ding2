<?php
/**
 * @file
 * Handles user authentication with the alma provider.
 */

/**
 * Implements hook_user_authenticate().
 */
function alma_user_authenticate($uid, $pass) {
  $return = array(
    'success' => FALSE,
  );

  try {
    $res = alma_client_invoke('get_patron_info', $uid, $pass, TRUE);
    if ($res) {
      $return['success'] = TRUE;
    }
  }
  catch (Exception $e) {
    return $return;
  }

  // Set creds.
  $return['creds'] = array(
    'name' => $uid,
    'pass' => $pass,
  );

  // Set user information.
  $return['user'] = array(
    'data' => array(
      'display_name' => $res['user_name'],
    ),
  );

  // Set e-mail address.
  if (isset($res['mails'][0]) && valid_email_address($res['mails'][0]['mail'])) {
    $return['user']['mail'] = $res['mails'][0]['mail'];
  }

  // Set preferred branch.
  if (isset($res['preferences']['patron_branch'])) {
    $return['user']['data']['preferred_branch'] = $res['preferences']['patron_branch'];
  }

  // Set patron address.
  if (isset($res['addresses'][0])) {
    $return['user']['data']['address'] = array(
      'street' => $res['addresses'][0]['street'],
      'postal_code' => $res['addresses'][0]['postal_code'],
      'city' => $res['addresses'][0]['city'],
      'country' => $res['addresses'][0]['country'],
    );
  }

  // Set the users categories.
  if (!empty($res['category'])) {
    $return['user']['category'] = $res['category'];
  }

  $return['user']['blocked'] = FALSE;
  if (!empty($res['blocks'])) {
    // Send block codes back with the user.
    $return['user']['blocks'] = $res['blocks'];
    $return['user']['blocked'] = TRUE;
  }

  return $return;
}

/**
 * Check if the user creds is set correctly.
 *
 * @param array $creds
 *   Array with the user credentials.
 *
 * @return bool
 *   TRUE if user is authenticated else FALSE
 */
function alma_user_is_authenticated($creds) {
  return (isset($creds['name']) && isset($creds['pass']));
}

/**
 * Provider specific user profile form validate handler.
 */
function alma_user_profile_form_validate($form, $form_state) {

}

/**
 * Update pin code at alma.
 *
 * @param object $account
 *   User account object or the user provider profile2.
 * @param string $new_pincode
 *   The users new pin-code.
 *
 * @return array
 *   Updated credential array.
 */
function alma_user_update_pincode($account, $new_pincode) {
  $creds = ding_user_get_creds($account);

  // Change the users pin code..
  if (isset($new_pincode)) {
    $res = alma_client_invoke('change_pin', $creds['name'], $creds['pass'], $new_pincode);
    if ($res) {
      // @see ding_user.module/ding_user_user_presave
      // Set new password.
      $creds['pass'] = $new_pincode;

      // Update creds.
      $result = array();
      $result['creds'] = $creds;
      return $result;
    }
  }
}

/**
 * Implements clear_cache().
 *
 * This hook is only called from ding_dibs after a payment have been accepted.
 *
 * @param stdClass $account
 *   Drupal user account object.
 */
function alma_user_clear_cache($account) {
  // As the ALMA currently only uses a static cache for debt... do nothing.
}

/**
 * Create new user through self registration.
 *
 * @param string $cpr
 *   The users CPR/borrow id.
 * @param string $pin_code
 *   Selected pin code.
 * @param string $name
 *   The borrowers name.
 * @param string $mail
 *   The borrowers e-mail.
 * @param string $branch_id
 *   The selected default branch's id.
 *
 * @throws \Exception
 *   If the user exists at the provider.
 */
function alma_user_create($cpr, $pin_code, $name, $mail, $branch_id) {
  try {
    alma_client_invoke('self_register', $cpr, $pin_code, $name, $mail, $branch_id);
  }
  catch (AlmaClientUserAlreadyExistsError $exception) {
    // Throw new exception that is not provider dependent.
    throw new DingProviderAuthUserExistsError('User account already exists');
  }
}
