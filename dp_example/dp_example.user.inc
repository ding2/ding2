<?php

/**
 * @file
 * Ding user provider example.
 */

/**
 *
 */
function dp_example_user_authenticate($name, $pass) {
  $res = array(
    'success' => FALSE,
  );

  if (substr($name, -4) == $pass) {
    $res['success'] = TRUE;
    if (preg_match('/blocked/', $name)) {
      $res['success'] = FALSE;
      $res['messages'][] = t("Sorry, you're blocked");
    }

    $res['creds'] = array(
      'name' => $name,
      'pass' => $pass,
    );

    $res['user'] = array(
      'mail' => $name . '@example.com',
      'data' => array(
        'display_name' => drupal_ucfirst($name),
      ),
    );
  }

  return $res;
}

/**
 * @todo Determine if this is required, or if it can be made optional
 * (by assuming things if creds are available or not)
 */
function dp_example_user_is_authenticated($creds) {
  return (isset($creds['name']) && isset($creds['pass']));
}

/**
 * Testing function, shouldn't be implemented in provider implementations.
 * @todo: move testing code to use another existing function.
 */
function dp_example_user_test() {
  if (!ding_user_get_creds()) {
    throw new DingProviderAuthException;
  }
  return "Wolla!";
}
