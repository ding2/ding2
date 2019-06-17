<?php
/**
 * @file
 * Implements functions used to log users into the system through SSO services.
 */

/**
 * Implements hook_auth_single_sign_on().
 */
function fbs_auth_single_sign_on($name) {
  $res = array();

  // Default password is the four last letters in the name.
  $password = drupal_substr($name, -4);
  $passes = variable_get('connie_user_passes', array());
  if (isset($passes[$name])) {
    $password = $passes[$name];
  }
  
  // We simply check that the name existed in the $passes, which is basically
  // what we do at single sign on as log in is validated external.
  if ($password) {
    $res['success'] = TRUE;
    if (preg_match('/blocked/', $name)) {
      $res['success'] = FALSE;
      $res['messages'][] = t("Sorry, you're blocked");
    }

    $res['creds'] = array(
      'name' => $name,
    );

    $res['user'] = array(
      'mail' => $name . '@example.com',
      'data' => array(
        'display_name' => drupal_ucfirst($name),
      ),
    );

    // This is how we pass data from here (where the profile2 profile
    // might not yet exist) to the profile_init callback.
    $res['private']['branch'] = 'aby';
  } else {
    throw new DingProviderUserAuthFailure();
  }

  return $res;
}
