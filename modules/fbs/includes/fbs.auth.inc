<?php
/**
 * @file
 * Implements functions used to log users into the system through SSO services.
 */

/**
 * Implements hook_auth_login_credentials().
 *
 * @oaram string $uuid
 *   Unique id for the person that's should be generated credentials for.
 *
 * Used to set the name and password to log into the library system after auth
 * login.
 */
function fbs_auth_single_sign_on($uuid) {
  // Generate a one time password for this request. Shouldn't really be needed
  // as we'll check in the login function that auth was called for the user, but
  // it'll add some randomness to the procedure.
  $pass = user_password(16);
  $credentials = array(
    'name' => $uuid,
    'pass' => $pass,
  );

  return $credentials;
}
