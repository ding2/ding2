<?php
/**
 * @file
 * Handles user authentication and update for OpenRuth.
 */

/**
 * Implements provider user, authenticate.
 *
 * @param string $name
 *   The users name/card number.
 * @param string $pincode
 *   The users pin-code.
 *
 * @return array
 *   User information.
 *
 */
function openruth_user_authenticate($name, $pincode) {
  $return = array(
    'success' => FALSE,
  );
  $res = openruth_client_invoke('user_check', $name, $pincode);

  if (is_string($res)) {
    watchdog('openruth', 'Error in user_check: @error', array('@error' => $res), WATCHDOG_ERROR);
    return $return;
  }
  elseif (!$res || !$res->userFound || !$res->userPinCodeOk) {
    // No reply or not found.
    return $return;
  }

  $return['user']['blocked'] = FALSE;
  if ($res->userBlocked) {
    $return['user']['blocked'] = TRUE;
  }

  $return['success'] = TRUE;
  $return['creds'] = array(
    'name' => $name,
    'pass' => $pincode,
  );

  $status = _openruth_user_status($return['creds'], TRUE);
  if ($status && isset($status->userInfo)) {
    $user_info = $status->userInfo;
    $return['user'] = array(
      'data' => array(
        'display_name' => $user_info->userFirstName . ' ' . $user_info->userLastName,
      ),
    );

    $return['private']['userinfo'] = $user_info;

    if (isset($user_info->userEmail)) {
      $return['user']['mail'] = $user_info->userEmail;
    }
  }

  return $return;
}

/**
 * Clear user cache.
 *
 * @param StdClass $account
 *   Drupal user account object.
 */
function openruth_user_clear_cache($account) {
  $creds = ding_user_get_creds($account);
  // Update user status cache.
  _openruth_user_status($creds, TRUE);
}

/**
 * Update pin code at openruth.
 *
 * @param object $account
 *   User account object or the user provider profile2.
 * @param string $new_pincode
 *   The users new pincode.
 *
 * @return array
 *   Updated credential array.
 */
function openruth_user_update_pincode($account, $new_pincode) {
  $result = array();

  if (isset($new_pincode)) {
    $creds = ding_user_get_creds($account);
    $res = openruth_client_invoke('update_userinfo', $creds['name'], $creds['pass'], array('pass' => $new_pincode));
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

    // Update creds in the return.
    $creds['pass'] = $new_pincode;
    $result['creds'] = $creds;

    // Update user status cache.
    _openruth_user_status($creds, TRUE);
  }

  return $result;
}
