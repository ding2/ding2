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

    if (isset($userInfo->agencyCounter)) {
      $return['user']['data']['preferred_branch'] = $userInfo->agencyCounter;
    }

    if (isset($userInfo->userEmail)) {
      $return['user']['mail'] = $userInfo->userEmail;
    }
  }

  return $return;
}

/**
 * Callback function to get OpenRuth user information
 */
function openruth_user_info($creds = NULL) {
  $info = array();
  $user_status = _openruth_user_status($creds);

  $branches = openruth_client_invoke('get_agencycounters');

  $info = array(
    'firstname' => isset($user_status->userInfo->userFirstName) ? $user_status->userInfo->userFirstName : NULL,
    'lastname' => isset($user_status->userInfo->userLastName) ? $user_status->userInfo->userLastName : NULL,
    'email' => isset($user_status->userInfo->userEmail) ? $user_status->userInfo->userEmail : NULL,
    'address' => isset($user_status->userInfo->userAddress) ? $user_status->userInfo->userAddress : NULL,
    'postal' => isset($user_status->userInfo->userPostCode) ? $user_status->userInfo->userPostCode : NULL,
    'city' => isset($user_status->userInfo->userCity) ? $user_status->userInfo->userCity : NULL,
    'village' => isset($user_status->userInfo->userVillage) ? $user_status->userInfo->userVillage : NULL,
    'phone' => isset($user_status->userInfo->userTelephone) ? $user_status->userInfo->userTelephone : NULL,
    'mobile' => isset($user_status->userInfo->userMobilePhone) ? $user_status->userInfo->userMobilePhone : NULL,
    'agency' => $branches[$user_status->userInfo->agencyCounter],
  );

  return (object) $info;
}

function openruth_user_profile_form($form, $form_state) {
  global $user;
  $creds = ding_user_get_creds($user);
  $status = _openruth_user_status($creds);
  $agency_info = openruth_client_invoke('get_agency_info');
  $preferred_branch = FALSE;

  if (isset($user->data['preferred_branch'])) {
    $preferred_branch = $user->data['preferred_branch'];
  }

  $form['openruth_library'] = array(
    '#type' => 'fieldset',
    '#title' => t('My library'),
  );

  $form['openruth_library']['email'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

  $form['openruth_library']['password'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

  $form['openruth_library']['mobile_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile phone'),
    '#value' => isset($status->userInfo->userMobilePhone) ? $status->userInfo->userMobilePhone : NULL,
    '#description' => t('Submit your mobile number to recieve SMS notifications'),
  );

  $form['openruth_library']['preferred_branch'] = array(
    '#type' => 'select',
    '#title' => t('My pickup branch'),
    '#options' => ding_provider_invoke('reservation', 'pickup_branches', $user),
    '#default_value' => $preferred_branch,
    '#description' => t('Choose the librarybranch where you want to pick up reserved materials'),
  );

  // Since we dont know the users internal password, we will remove the form fields
  // And the validate check.
  unset($form['#validate'][array_search('user_validate_current_pass', $form['#validate'])]);
  unset($form['account']['current_pass']);
  unset($form['account']['current_pass_required_values']);

  return $form;
}

/**
 * Provider specific user profile form validate handler.
 */
function openruth_user_profile_form_validate($form, $form_state) {
  // Validate the phonenumber
  if (strlen($form_state['input']['mobile_phone']) != 0 && strlen((int)$form_state['input']['mobile_phone']) != 8) {
    form_set_error('mobile_phone', t('The mobile number should only contain 8 digits'));
  }
}

/**
 * Provider specific user profile form submit handler.
 */
function openruth_user_profile_form_submit($form, $form_state) {
  global $user;

  $args = array();
  $changed_settings = $form_state['input'];
  $orig_settings = $form['openruth_library'];
  if ($orig_settings['email'] == TRUE && ($form['account']['mail']['#default_value'] !== $changed_settings['mail'])) {
    $args['mail'] = $changed_settings['mail'];
  }

  if ($orig_settings['password'] == TRUE && ($changed_settings['pass']['pass1'])) {
    $args['pass'] = $changed_settings['pass']['pass1'];
  }

  if ($changed_settings['mobile_phone'] !== $orig_settings['mobile_phone']['#value']) {
    $args['mobile_phone'] = $changed_settings['mobile_phone'];
  }

  if ($changed_settings['preferred_branch'] !== $orig_settings['preferred_branch']['#default_value']) {
    $args['preferred_branch'] = $changed_settings['preferred_branch'];
  }

  if (count($args) == TRUE) {
    $creds = ding_user_get_creds($user);
    openruth_client_invoke('update_userinfo', $creds['name'], $creds['pass'], $args);
    if (isset($args['pass'])) {
      ding_user_save_creds(array('creds' => array('name' => $creds['name'], 'pass' => $args['pass'])), $user);
    }
    $creds = ding_user_get_creds($user);

    if (isset($args['pass'])) {
      $creds['pass'] = $args['pass'];
    }
    _openruth_user_status($creds, TRUE);
  }

}

