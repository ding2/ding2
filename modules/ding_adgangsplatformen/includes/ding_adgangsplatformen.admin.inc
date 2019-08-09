<?php
/**
 * @file
 * Defines the administration interface for the module.
 */

/**
 * Defines the administration settings form.
 */
function ding_adgangsplatformen_admin_settings_form($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  $form['ding_adgangsplatformen_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Adgangsplatformen configuration'),
  );

  $default = ding_adgangsplatformen_get_configuration();

  $form['ding_adgangsplatformen_settings']['clientId'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#size' => 35,
    '#description' => t('The client id should be obtained from the authentication provider - DBC.'),
    '#default_value' => $default['clientId'],
  );

  $form['ding_adgangsplatformen_settings']['clientSecret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#size' => 63,
    '#description' => t('Get this from the provider - DBC.'),
    '#default_value' => $default['clientSecret'],
  );

  $form['ding_adgangsplatformen_settings']['redirectUri'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect URL'),
    '#description' => t('The URL to be redirected to after login - you should not change this URL as it has to match the provider configuration at DBC.'),
    '#default_value' => $default['redirectUri'],
    '#disabled' => TRUE,
  );

  $form['ding_adgangsplatformen_settings']['urlAuthorize'] = array(
    '#type' => 'textfield',
    '#title' => t('Authorization service'),
    '#description' => t('The authorization service end-point.'),
    '#default_value' => $default['urlAuthorize'],
  );

  $form['ding_adgangsplatformen_settings']['urlAccessToken'] = array(
    '#type' => 'textfield',
    '#title' => t('Access token service'),
    '#description' => t('The access token service end-point.'),
    '#default_value' => $default['urlAccessToken'],
  );

  $form['ding_adgangsplatformen_settings']['urlResourceOwnerDetails'] = array(
    '#type' => 'textfield',
    '#title' => t('Resource end-point'),
    '#description' => t('The location of the resource service.'),
    '#default_value' => $default['urlResourceOwnerDetails'],
  );

  $form['ding_adgangsplatformen_settings']['urlLogout'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout'),
    '#description' => t('Logout service location.'),
    '#default_value' => $default['urlLogout'],
  );

  $form['ding_adgangsplatformen_settings']['singleLogout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Single logout'),
    '#description' => t('Use single logout when a user logs out of the site. This will log the user out of all sites where they are currently logged in using Adgangsplatformen.'),
    '#return_value' => true,
    '#default_value' => $default['singleLogout'],
  );

  return system_settings_form($form);
}
