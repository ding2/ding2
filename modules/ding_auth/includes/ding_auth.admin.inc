<?php
/**
 * @file
 * Defines the administration interface for the module.
 */

/**
 * Defines the administration settings form.
 */
function ding_auth_admin_settings_form($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $form['ding_auth_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Access platform configuration'),
  );

  $default = ding_auth_get_configuration();

  $form['ding_auth_settings']['clientId'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#description' => t('The client id should be obtained at the auth provider - DBC.'),
    '#default_value' => $default['clientId'],
  );

  $form['ding_auth_settings']['clientSecret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#description' => t('Get this form the provider - DBC.'),
    '#default_value' => $default['clientSecret'],
  );

  $form['ding_auth_settings']['redirectUri'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect URL'),
    '#description' => t('The URL to be redirected to after login - you should not change this URL as it has to match the provider configuration at DBC.'),
    '#default_value' => $default['redirectUri'],
  );

  $form['ding_auth_settings']['urlAuthorize'] = array(
    '#type' => 'textfield',
    '#title' => t('Authorization service'),
    '#description' => t('The authorization service end-point.'),
    '#default_value' => $default['urlAuthorize'],
  );

  $form['ding_auth_settings']['urlAccessToken'] = array(
    '#type' => 'textfield',
    '#title' => t('Access token service'),
    '#description' => t('The access token service end-point.'),
    '#default_value' => $default['urlAccessToken'],
  );

  $form['ding_auth_settings']['urlResourceOwnerDetails'] = array(
    '#type' => 'textfield',
    '#title' => t('Resource end-point'),
    '#description' => t('The location of the resource service.'),
    '#default_value' => $default['urlResourceOwnerDetails'],
  );

  $form['ding_auth_settings']['urlLogout'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout'),
    '#description' => t('Logout service location.'),
    '#default_value' => $default['urlLogout'],
  );

  return system_settings_form($form);
}
