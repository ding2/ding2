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
function alma_wayf_login_credentials($authentication_attributes) {
  $hash = variable_get('alma_wayf_hash', '');
  $credentials = array();

  if ($hash) {
    $credentials = array(
      'name' => $authentication_attributes['schacPersonalUniqueID'],
      'pass' => $hash,
    );
  }
  else {
    // Set message that hash value was not found.
    watchdog('alma', 'The WAYF hash value has not been set in setting.php as $conf[\'alma_wayf_hash\'] and WAYF login will fail', WATCHDOG_ERROR);
  }

  return $credentials;
}

/**
 * Implements hook_wayf_attributes().
 *
 * Used to define which attribute to use as login name.
 */
function alma_wayf_attributes() {
  return array(
    'schacPersonalUniqueID' => array(
      'field' => 'CPR',
    ),
  );
}
