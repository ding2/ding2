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

function openruth_user_profile_form($form) {
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

  $form['openruth_library']['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile phone'),
    '#value' => $status->userInfo->userTelephone,
  );

  $form['openruth_library']['pickup_branch'] = array(
    '#type' => 'select',
    '#title' => t('My pickup branch'),
    '#options' => ding_provider_invoke('reservation', 'pickup_branches', $user),
    '#default_value' => $preferred_branch,
  );

  $form['openruth_library']['period_of_interest'] = array(
    '#type' => 'select',
    '#title' => t('Period of interest'),
    '#options' => $period_of_interest,
    '#default_value' => $agency_info->orderActivePeriod,
  );

  $form['openruth_library']['pause_reservation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pause reservations from'),
  );

  $form['openruth_library']['pause_reservations']['from'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
  );

  $form['openruth_library']['pause_reservations']['to'] = array(
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#title' => t('to'),
  );

  $form['#validate'][] = 'openruth_form_user_profile_form_validate';

  return $form;
}
