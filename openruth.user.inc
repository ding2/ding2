<?php

/**
 * Implements provider user, authenticate.
 */
function openruth_user_authenticate($name, $pass) {
  $return = array(
    'success' => FALSE,
  );
  $res = openruth_client_invoke('user_check', $name, $pass);

  if (is_string($res)) {
    watchdog('openruth', 'Error in user_check: @error', array('@error' => $res), WATCHDOG_ERROR);
    throw new DingProviderAuthException();
    // return $return;
  }
  elseif (!$res || !$res->userFound || !$res->userPinCodeOk) {
    // No reply or not found.
    throw new DingProviderAuthException();
    //return $return;
  }

  if ($res->userBlocked) {
    // @todo Tell the user...
  }

  $return['success'] = TRUE;
  $return['creds'] = array(
    'name' => $name,
    'pass' => $pass,
  );

  $userStatus = _openruth_user_status($return['creds'], TRUE);
  if ($userStatus && isset($userStatus->userInfo)) {
    $userInfo = $userStatus->userInfo;
    $return['user'] = array(
      'data' => array(
        'display_name' => $userInfo->userFirstName . ' ' . $userInfo->userLastName,
      ),
    );

    $return['private']['userinfo'] = $userInfo;

    if (isset($userInfo->userEmail)) {
      $return['user']['mail'] = $userInfo->userEmail;
    }
  }

  return $return;
}

/**
 *
 */
function openruth_user_profile_init($profile, $auth_res) {
  openruth_profile_update($profile, $auth_res['private']['userinfo']);
  // Don't save to Openruth in presave hook.
  $profile->openruth_init = TRUE;
  $profile->save();
  unset($profile->openruth_init);
}

/**
 * Update user account.
 */
function openruth_user_account_update($account, $changes) {
  $result = array();
  $creds = ding_user_get_creds($account);
  $res = openruth_client_invoke('update_userinfo', $creds['name'], $creds['pass'], $changes);
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
    _openruth_user_status($creds, TRUE);
  }
  return $result;
}