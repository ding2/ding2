<?php

/**
 * @file
 * Ding user pages.
 */

/**
 * Form builder, user authentication.
 *
 * This copies the regular user login form on purpose. By making it
 * look like the regular login form, modules wanting to make changes
 * can just form_alter them both.
 *
 * @ingroup forms
 */
function ding_user_authenticate_form($form, &$form_state) {
  form_load_include($form_state, 'inc', 'ding_user', 'ding_user.pages');

  global $user;

  try {
    $creds = ding_user_get_creds();
    // If we are already authenticated on, go to the user page instead.
    if (ding_provider_implements('user', 'is_authenticated')) {
      if (ding_provider_invoke('user', 'is_authenticated', $creds)) {
        drupal_goto('user/' . $user->uid);
      }
    }
  }
  catch (DingProviderAuthException $e) {
    // Fall through.
  }

  // Display login form:
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#size' => 60,
    '#maxlength' => USERNAME_MAX_LENGTH,
    '#required' => TRUE,
  );

  $form['name']['#description'] = t('Enter your @s username.', array('@s' => variable_get('site_name', 'Drupal')));
  $form['pass'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#description' => t('Enter the password that accompanies your username.'),
    '#required' => TRUE,
  );

  // This is where we diverge from the regular login form. We're not
  // specifying any special validators, but relying on the normal behaviour.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Log in'),
  );

  return $form;
}

/**
 * Form validator.
 */
function ding_user_authenticate_form_validate($form, &$form_state) {
  global $user;
  $auth_res = ding_provider_invoke('user', 'authenticate', $form_state['values']['name'], $form_state['values']['pass']);
  if (!is_array($auth_res) || !isset($auth_res['success'])) {
    watchdog('ding_user', 'Provider returned invalid result: @res', array('@res' => print_r($auth_res, TRUE)), WATCHDOG_DEBUG);
    form_error($form, t("Internal error, please try again later."));
    return;
  }

  $form_state['authentication_success'] = FALSE;
  if ($auth_res['success']) {
    if (isset($auth_res['authname']) && !empty($auth_res['authname'])) {
      // If provider supplied an authname, use it.
      $auth_name = $auth_res['authname'];
    }
    else {
      // Else use a standard authname.
      $auth_name = ding_user_default_authname($form_state['values']['name']);
    }

    $account = user_external_load($auth_name);
    if ($account && ($account->uid == $user->uid)) {
      $form_state['authentication_success'] = TRUE;
      $form_state['auth_res'] = $auth_res;
    }
  }
  if (!$form_state['authentication_success']) {
    form_set_error('name', t('Sorry, authentication failed, did you type the right username and password?'));
    watchdog('user', 'Authentication attempt failed for %uid.', array('%user' => $user->uid));
  }
}

/**
 * Form submit function.
 */
function ding_user_authenticate_form_submit($form, &$form_state) {
  if ($form_state['authentication_success']) {
    ding_user_save_creds($form_state['auth_res']);
    $form_state['redirect'] = 'user/' . $user->uid;
  }
}
