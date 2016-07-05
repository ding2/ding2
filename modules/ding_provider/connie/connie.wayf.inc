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
function connie_wayf_login_credentials($attributes) {
  $credentials = array(
    'name' => $attributes['schacPersonalUniqueID'],
    // This is the master password also defined in connie_user_authenticate().
    'pass' => 'password',
  );

  return $credentials;
}

/**
 * Implements hook_wayf_attributes().
 *
 * Used to define which attribute to use as login name.
 */
function connie_wayf_attributes() {
  return array(
    'schacPersonalUniqueID' => array(
      'field' => 'CPR',
    ),
  );
}
