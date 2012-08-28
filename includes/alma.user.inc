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
 * Provider specific user profile form validate handler.
 */
function alma_user_profile_form_validate($form, $form_state) {

}


function alma_user_clear_cache($creds=NULL) {
  $status = alma_get_patron();
}


/**
 * Update profile2 with values from alma patron
 */

function alma_user_profile_init( $profile2, $auth_res ){
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
    $profile2->field_absent_id[$langs['field_absent_id']][0]['value'] = $patron->absentPeriods[0]['id'];
  }
  else {
    $profile2->field_reservation_pause[$langs['field_alma_reservation_pause']][0]['value'] = ' ';
    $profile2->field_reservation_pause[$langs['field_alma_reservation_pause']][0]['value2'] = ' ';
  }

  // preferred_branch
  $profile2->field_alma_preferred_branch[$langs['field_alma_preferred_branch']][0]['value'] = $patron->branch;

  //mobile; also here alma supports multiple phones - again we pick the first
  $profile2->field_alma_mobile_phone[$langs['field_alma_mobile_phone']][0]['value'] = isset($patron->mobiles[0]['phone']) ? $patron->mobiles[0]['phone'] : '';
  $profile2->field_alma_phone_id[$langs['field_alma_phone_id']][0]['value'] = isset($patron->mobiles[0]['id']) ? $patron->mobiles[0]['id'] : null;
  //$profile2->field_alma_phone_id[$langs['field_alma_phone_id']][0]['value'] = isset() .. etc

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

  // change password
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
