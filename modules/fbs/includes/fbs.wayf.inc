<?php
/**
 * @file
 * Implements functions used to log users into the system through WAYF.
 */

/**
 * Implements hook_wayf_login_credentials().
 *
 * Used to set the name and password to log into the library system after WAYF
 * login.
 */
function fbs_wayf_login_credentials($authentication_attributes) {
  // Generate a one time password for this request. Shouldn't really be needed
  // as we'll check in the login function that wayf was called for the user, but
  // it'll add some randomness to the procedure.
  $pass = user_password(16);
  _fbs_wayf_login($authentication_attributes['schacPersonalUniqueID'], $pass);
  $credentials = array(
    'name' => $authentication_attributes['schacPersonalUniqueID'],
    'pass' => $pass,
  );

  return $credentials;
}

/**
 * Implements hook_wayf_attributes().
 *
 * Used to define which attribute to use as login name.
 */
function fbs_wayf_attributes() {
  return array(
    'schacPersonalUniqueID' => array(
      'field' => 'CPR',
    ),
  );
}
