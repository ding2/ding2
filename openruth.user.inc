<?php

/**
 * Callback function to get OpenRuth user information
 */
function openruth_user_info($creds = NULL) {
  $info = array();
  $user_status = _openruth_user_status($creds);

  $branches = openruth_client_invoke('get_agencycounters');

  $info = array(
    'firstname' => $user_status->userInfo->userFirstName,
    'lastname' => $user_status->userInfo->userLastName,
    'email' => $user_status->userInfo->userEmail,
    'address' => $user_status->userInfo->userAddress,
    'postal' => $user_status->userInfo->userPostCode,
    'city' => $user_status->userInfo->userCity,
    'village' => $user_status->userInfo->userVillage,
    'phone' => $user_status->userInfo->userTelephone,
    'mobile' => $user_status->userInfo->userMobilePhone,
    'agency' => $branches[$user_status->userInfo->agencyCounter],
  );

  return (object) $info;
}

function openruth_user_profile_form($form, $form_state) {

  global $user;
  $creds            = ding_user_get_creds($user);
  $status           = _openruth_user_status($creds);
  $agency_info      = openruth_client_invoke('get_agency_info');
  $preferred_branch = FALSE;

  if (isset($user->data['preferred_branch'])) {
    $preferred_branch = $user->data['preferred_branch'];
  }

  $period_of_interest = array(
    30 => t('1 month'),
    60 => t('2 months'),
    180 => t('6 months'),
    360 => t('12 months'),
  );

  $form['openruth_library'] = array(
    '#type' => 'fieldset',
    '#title' => t('My library'),
  );

  $form['openruth_library']['mobile_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile phone'),
    '#value' => $status->userInfo->userMobilePhone,
  );

  $form['openruth_library']['preferred_branch'] = array(
    '#type' => 'select',
    '#title' => t('My pickup branch'),
    '#options' => ding_provider_invoke('reservation', 'pickup_branches', $user),
    '#default_value' => $preferred_branch,
  );

  return $form;
}

/**
 * Provider specific user profile form validate handler.
 */
function openruth_user_profile_form_validate($form, $form_state) { }

/**
 * Provider specific user profile form submit handler.
 */
function openruth_user_profile_form_submit($form, $form_state) {
  global $user;

  $args = array();
  $changed_settings = $form_state['input'];
  $orig_settings = $form['openruth_library'];

  if ($changed_settings['mobile_phone'] !== $orig_settings['mobile_phone']['#value']) {
    $args['mobile_phone'] = $changed_settings['mobile_phone'];
  }

  if ($changed_settings['preferred_branch'] !== $orig_settings['preferred_branch']['#default_value']) {
    $args['preferred_branch'] = $changed_settings['preferred_branch'];
  }

  if (count($args) == TRUE) {
    $creds = ding_user_get_creds($user);
    openruth_client_invoke('update_userinfo', $creds['name'], $creds['pass'], $args);
    _openruth_user_status($creds, TRUE);
  }

}

