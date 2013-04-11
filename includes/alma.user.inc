<?php
/**
 * @file
 * Handles user authentication with the alma provider.
 */


/**
 * Implements hook_user_authenticate().
 *
 * @param <type> $name
 * @param <type> $pass
 */
function alma_user_authenticate($uid, $pass) {
  $return = array(
    'success' => FALSE,
  );

  try {
    $res = alma_client_invoke('get_patron_info', $uid, $pass, TRUE);
    $return['success'] = TRUE;
  }
  catch (Exception $e) {
    return $return;
  }

  // @todo Check block status.

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
  
  return $return;
}

/**
 * Check if the user creds is set correctly.
 *
 * @param type $creds
 * @return type
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
 * Clear user cache based on creds.
 *
 * @param array $creds
 */
function alma_user_clear_cache($creds = NULL) {
  alma_get_patron($creds);
}

/**
 * Update pin code at alma.
 *
 * @TODO: Rename this function to change hook_alma_change_pincode and in 
 * ding_user line 240.
 *
 * @param type $account
 * @param type $changes
 * @return type
 */
function alma_user_account_update($account, $changes) {
  $creds = ding_user_get_creds($account);

  // Change the users pin code..
  if (isset($changes['pass'])) {
    $res = alma_client_invoke('change_pin', $creds['name'], $creds['pass'], $changes['pass']);
    if ($res) {
      // @see ding_user.module/ding_user_user_presave
      // Set new password.
      $creds['pass'] = $changes['pass'];

      // Update creds.
      $result = array();
      $result['creds'] = $creds;
      return $result;
    }
  }
}
