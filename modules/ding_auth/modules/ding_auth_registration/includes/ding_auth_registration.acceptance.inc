<?php
/**
 * @file
 * The acceptance form handling.
 */

/**
 * Implements hook_form().
 */
function ding_auth_registration_acceptance_form() {
  $config = _ding_auth_registration_config();

  // @TODO: use defaults.
  $userinfo = unserialize($_SESSION['oauth2userinfo']);

  // This is a little style hack to get around the panels design requirements of
  // the DDB default theme. The module existing_pages could have been used to
  // wrapper the form in panels. But seen form a performance point this is
  // faster and simpler.
  $form = array(
    '#theme_wrappers' => array('form', 'ding_auth_registration_acceptance'),
  );

  $form['accept'] = array(
    '#type' => 'checkbox',
    '#title' => t('I accept the user agreements'),
    '#description' => $config['acceptance']['description']['value'],
    '#required' => TRUE,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('Your full name.'),
    // Max length of 100 is the current limit set by the database in the library
    // system.
    '#maxlength' => 100,
    '#required' => TRUE,
    '#attributes' => array(
      // Auto-complete is disabled here as the registration may be preform on a
      // public computer in the library and information about which user there
      // is registered and the name is classified information.
      'autocomplete' => 'off',
    ),
  );

  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address'),
    '#description' => t('The Email address that we can use to get in contact with you.'),
    '#required' => TRUE,
    '#attributes' => array(
      // Auto-complete is disabled here as the registration may be preform on a
      // public computer in the library and information about which user there
      // is registered and the mail address is classified information.
      'autocomplete' => 'off',
    ),
  );

  // Get branch options form the active provider. We are using the anonymous
  // user here to get default provider branches.
  global $user;
  $provider = _ding_provider_get_provider('reservation');
  $options = ding_provider_invoke('reservation', 'options', $user);
  $form['branch'] = $options[$provider['module'] . '_preferred_branch'];

  $form['pin'] = array(
    '#type' => 'password',
    '#title' => t('Pin code'),
    '#description' => t('Pin code with an max length of %length', array('%length' => ding_user_get_pincode_length())),
    '#maxlength' => ding_user_get_pincode_length(),
    '#required' => TRUE,
    '#element_validate' => array('ding_user_element_validate_pincode'),
    '#attributes' => array(
      'autocomplete' => 'off',
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create me'),
  );

  // Link cancel button to auth logout to ensure that the user is signed
  // out correctly.
  $form['cancel'] = array(
    '#markup' => l(t('Cancel'), DING_AUTH_LOGOUT_URL, array('attributes' => array('class' => 'ding-auth--cancel'))),
  );

  return $form;
}

/**
 * Submit handler for the acceptance form.
 *
 * It tries to create the user at the provider and redirect the user.
 */
function ding_auth_registration_acceptance_form_submit($form, $form_state) {
  $values = $form_state['values'];

  $userinfo = unserialize($_SESSION['oauth2userinfo']);
  unset($_SESSION['oauth2userinfo']);

  // Check that the logged in user is over the age limit.
  if (!_ding_auth_registration_is_age_limit_met($userinfo['attributes']['userId'])) {
    $config = _ding_auth_registration_config();
    drupal_set_message(t('You are not allowed to automatically be created because of the age limit (!limit years). Please go to your local library to registry.', array('!limit' => $config['age_limit'])));

    // Logout the user from auth.
    ding_auth_logout();
    _ding_auth_redirect_user('<front>');
    return;
  }

  // Try to create the user at the provider.
  try {
    // Create user as the provider.
    ding_provider_invoke('user', 'create', $userinfo['attributes']['userId'], $values['pin'], $values['name'], $values['mail'], $values['branch']);

    // Set redirect and try logging in the user.
    $_REQUEST['destination'] = DING_AUTH_REGISTRATION_SUCCESS_URL;
    _ding_auth_provider_login($userinfo);
  }
  catch (Exception $exception) {
    watchdog_exception('ding_auth_registration', $exception);
    drupal_set_message(t('There was an error creating your account, please try again later or contact the library.'), 'error');
  }
}
