<?php
/**
 * @file
 * Implements functions used to log users into the system through SSO services.
 */

/**
 * Implements hook_auth_single_sign_on().
 */
function connie_auth_single_sign_on($name) {
  $res = array();

  $passes = variable_get('connie_user_passes', array());

  $auth_patterns = variable_get('connie_auth_patterns', array());
  $pattern_match = array_reduce($auth_patterns, function(bool $carry, string $pattern) use ($name)  {
    return $carry || preg_match($pattern, $name);
  }, FALSE);

  // Allow users in connie_user_passes or who matches connie_auth_patterns.
  // Password has already been validated by single signon system.
  if (isset($passes[$name]) || $pattern_match) {
    $res['success'] = TRUE;
    $res['creds'] = array(
      'name' => $name,
    );

    // Hide last 4 digits in case name looks like a CPR number.
    $display_name = preg_replace('/(\d{6})(\d{4})/', '\1XXXX', $name);

    $res['user'] = array(
      'mail' => hash('crc32', $name) . '@example.com',
      'data' => array(
        'display_name' => $display_name,
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
