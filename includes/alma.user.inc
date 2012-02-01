<?php

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
  $return['creds'] = array (
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

function alma_user_is_authenticated($creds) {
  return (isset($creds['name']) && isset($creds['pass']));
}

/**
 * Callback function to get OpenRuth user information
 */
function alma_user_info($creds = NULL) {
  // Get patron informations from ALMA.
  $status = alma_get_patron($creds);

  // Build basic information array, with patron information.
  $info = array(
    'firstname' => $status->name,
    'lastname' => '',
    'email' => $status->email,
    'address' => $status->address,
    'postal' => $status->postal,
    'city' => $status->city,
    'mobile' => $status->mobile,
    'agency' => $status->branchName,
  );

  return (object)$info;
}




/*function alma_user_profile_form($form, $form_state) {
  $status = alma_get_patron();
  $organisation = alma_get_organisation();

  // NOT IMPLEMNETED YET
//  $period_of_interest = array(
//    30 => t('1 month'),
//    60 => t('2 months'),
//    180 => t('6 months'),
//    360 => t('12 months'),
//  );

  $form['alma_library']['email'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

  $form['alma_library']['password'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );

  $form['alma_library']['mobile_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile phone'),
    '#value' => $status->mobile,
  );

  $form['alma_library']['preferred_branch'] = array(
    '#type' => 'select',
    '#title' => t('My pickup branch'),
    '#options' => $organisation['reservation'],
    '#default_value' => $status->branch,
  );

  // Since we dont know the users internal password, we will remove the form fields
  // And the validate check.
  unset($form['#validate'][array_search('user_validate_current_pass', $form['#validate'])]);
  unset($form['account']['current_pass']);
  unset($form['account']['current_pass_required_values']);

  return $form;
  }*/

/**
 * Provider specific user profile form validate handler.
 */
function alma_user_profile_form_validate($form, $form_state) {

}

/**
 * Update profile2 with values from alma patron
 */

function alma_user_profile_init( $profile2, $auth_res ){
  // @todo implement
  $creds = ding_user_get_creds($profile2);
  $patron = alma_get_patron($creds);
  // reservation pause (absentPeriod)
  // apparently alma supports multiple absentPeriods, but for now we handle one only (the first found)
  // @todo - check if it's correct to handle the first only
  $langs = field_language('profile2', $profile2);
  // reservation pause
  if( isset($patron->absentPeriods[0]['from_date']) && isset($patron->absentPeriods[0]['to_date'] ) ) {
    $profile2->field_alma_reservation_pause[$langs['field_alma_reservation_pause']][0]['value'] = $patron->absentPeriods[0]['from_date'];
    $profile2->field_alma_reservation_pause[$langs['field_alma_reservation_pause']][0]['value2'] = $patron->absentPeriods[0]['to_date'];
    $profile2->absentId = $patron->absentPeriods[0]['id'];;
  }  
  else {
    $profile2->field_reservation_pause[$langs['field_alma_reservation_pause']][0]['value'] = ' ';
    $profile2->field_reservation_pause[$langs['field_alma_reservation_pause']][0]['value2'] = ' ';
  }

  // preferred_branch
  $profile2->field_alma_preferred_branch[$langs['field_alma_preferred_branch']][0]['value'] = $patron->branch;

  // handle init parameter in alma.module/alma_profile2_presave
  $profile2->alma_init = TRUE;
  $profile2->save();
  unset($profile2->alma_init);
}

/**
 * update provider user;
 * @invoked from: ding_user/ding_user_user_presave
 * possible changes; email, pincode, preferred_branch
 */
function alma_user_account_update($account, $changes) {
  $creds = ding_user_get_creds($account);

  if( isset($changes['mail']) ) {
    // add email
    if( empty( $account->mail ) && !empty($changes['mail'] ) ) {
       $res = alma_client_invoke('add_email_address', $creds['name'], $creds['pass'], $changes['mail']);
    }
    // change email
    elseif( isset( $account->mail ) && !empty($changes['mail'] ) ){
       $res = alma_client_invoke('change_email_address', $creds['name'], $creds['pass'], $account->mail, $changes['mail']);
    }
  }

  if (isset($changes['pass'])) {
    $res = alma_client_invoke('change_pin', $creds['name'], $creds['pass'], $changes['pass']);
    if( $res ) {
      // @see ding_user.module/ding_user_user_presave
      // Set new password.
      $creds['pass'] = $changes['pass'];
      // Update creds.
      $result['creds'] = $creds;    
      return $result;
    }
  }
}


/**
 * Provider specific user profile form submit handler.
 */
/*function alma_user_profile_form_submit($form, $form_state) {
  global $user;

  $updated = FALSE;
  $creds = ding_user_get_creds($user);
  $changed_settings = $form_state['input'];
  $orig_settings = $form['alma_library'];

  // Update e-mail address.
  if ($orig_settings['email'] == TRUE && ($form['account']['mail']['#default_value'] !== $changed_settings['mail'])) {
    alma_client_invoke('change_email_address', $creds['name'], $creds['pass'], $form['account']['mail']['#default_value'], $changed_settings['mail']);
    $updated = TRUE;
  }

  // Update password.
  if ($orig_settings['password'] == TRUE && ($changed_settings['pass']['pass1'])) {
    alma_client_invoke('change_pin', $creds['name'], $creds['pass'], $changed_settings['pass']['pass1']);

    // Update informations local.
    ding_user_save_creds(array('creds' => array('name' => $creds['name'], 'pass' => $changed_settings['pass']['pass1'])), $user);
    $creds = ding_user_get_creds($user);
    $creds['pass'] = $changed_settings['pass']['pass1'];
    $updated = TRUE;
  }

  // Mobile phone number.
  if ($changed_settings['mobile_phone'] !== $orig_settings['mobile_phone']['#value']) {
    alma_client_invoke('change_phone_number', $creds['name'], $creds['pass'], $orig_settings['mobile_phone']['#value'], $changed_settings['mobile_phone']);
    $updated = TRUE;
  }

  // Preferred branch.
  if ($changed_settings['preferred_branch'] !== $orig_settings['preferred_branch']['#default_value']) {
    alma_client_invoke('change_patron_preferences', $creds['name'], $creds['pass'], $changed_settings['preferred_branch']);
    $updated = TRUE;
  }

  if ($updated) {
    // Update local cache.
    alma_get_patron($creds, TRUE);
  }
  }*/
