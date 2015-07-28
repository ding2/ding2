<?php

/**
 * @file
 * Ding user provider example.
 */

/**
 *
 */
function connie_user_authenticate($name, $pass) {
  $res = array(
    'success' => FALSE,
  );

  if (drupal_substr($name, -4) == $pass) {
    $res['success'] = TRUE;
    if (preg_match('/blocked/', $name)) {
      $res['success'] = FALSE;
      $res['messages'][] = t("Sorry, you're blocked");
    }

    $res['creds'] = array(
      'name' => $name,
      'pass' => $pass,
    );

    $res['user'] = array(
      'mail' => $name . '@example.com',
      'data' => array(
        'display_name' => drupal_ucfirst($name),
      ),
    );

    // This is how we pass data from here (where the profile2 profile
    // might not yet exist) to the profile_init callback.
    $res['private']['branch'] = 'aby';
  }

  return $res;
}

/**
 * Initialise profile.
 */
function connie_user_profile_init($profile, $auth_res) {
  connie_profile_update($profile, $auth_res['private']);
  // Don't save to Connie in presave hook.
  $profile->connie_init = TRUE;
  $profile->save();
  unset($profile->connie_init);
}

/**
 * Test that credentials is still valid. If this function is not
 * defined, it is assumed that having credentials available is enough.
 */
function connie_user_is_authenticated($creds) {
  return (isset($creds['name']) && isset($creds['pass']));
}

/**
 * Update user account.
 *
 * Update email and/or pincode for user.
 *
 * @param $account User object.
 * @param $changes
 *   An array with 'mail' and/or 'pass' keys.
 * @returns
 *   An array, optionally with new 'creds' which will be cached.
 */
function connie_user_account_update($account, $changes) {
  $result = array();
  $creds = ding_user_get_creds($account);
  $res = connie_client_invoke('update_userinfo', $creds['name'], $creds['pass'], $changes);
  if ($res !== TRUE) {
    // Call failed, throw exception.
    if (is_string($res)) {
      $exception_message = t('Update userinfo failed, message: @message', array('@message' => $res));
    }
    else {
      $exception_message = t('Update userinfo failed.');
    }
    throw new Exception($exception_message);
  }


  if (isset($changes['pass'])) {
    // Set new password.
    $creds['pass'] = $changes['pass'];
    // Update creds.
    $result['creds'] = $creds;

    // Update user status cache.
    _connie_user_status($creds, TRUE);
  }
  return $result;
}

/**
 * Testing function, shouldn't be implemented in provider implementations.
 * @todo: move testing code to use another existing function.
 */
function connie_user_test() {
  ding_user_get_creds(NULL);

  return "Wolla!";
}
