<?php

/**
 * @file
 * Ding user provider dummy.
 */

/**
 * Dummy authenticate handler.
 */
function ding_dummy_provider_user_authenticate($name, $pass) {

  // At this point a user is not found in Drupal, and because we have no
  // external services to request, the user must not exist and therefore we
  // disallow the login.
  // If login is a Drupal user it is catched in ding_user_user_login_validate()
  // when $form_state['uid'] is set.
  $res = array(
    'success' => FALSE,
  );

  return $res;
}
