<?php
/**
 * @file
 * Implements functions used to log users into the system through WAYF.
 */

/**
 * Implements hook_auth_login_credentials().
 *
 * Used to set the name and password to log into the library system after auth
 * login.
 */
function fbs_auth_login_credentials($personalUniqueID) {
  // Generate a one time password for this request. Shouldn't really be needed
  // as we'll check in the login function that wayf was called for the user, but
  // it'll add some randomness to the procedure.
  $pass = user_password(16);
  $credentials = array(
    'name' => $personalUniqueID,
    'pass' => $pass,
  );

  return $credentials;
}
