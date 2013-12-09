<?php
/**
 * @file
 * Implements the administration UI for the module.
 */

/**
 *
 *
 * @return mixed
 */
function ding_wayf_admin_settings_form() {
  $form = array(
    '#tree' => TRUE,
  );

  $default = variable_get('ding_wayf', array(
    'installdir' => '/var/simplesamlphp',
    'redirect' => 'user/%uid/status',
  ));

  $form['ding_wayf']['installdir'] = array(
    '#type' => 'textfield',
    '#title' => t('Simple SAML php installation directory'),
    '#default_value' => $default['installdir'],
    '#description' => t('Absolute path with no trailing slash to simple SAML installation.'),
    '#required' => FALSE,
  );

  $form['ding_wayf']['sp'] = array(
    '#type' => 'textfield',
    '#title' => t('Autenticaton source for this SP'),
    '#default_value' => isset($default['sp']) ? $default['sp'] : 'default-sp',
    '#description' => t('The name of the service provider (SP) to use from /var/simplesamlphp/config/authsources.php.'),
    '#required' => TRUE,
  );

  $form['ding_wayf']['redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect fallback URL'),
    '#default_value' => $default['redirect'],
    '#description' => t('Redirect to this fallback URL after login. This URL is only used if distination is not found. The token %uid is avaliable'),
    '#required' => TRUE,
  );

  $form['ding_wayf']['gatewayf'] = array(
    '#type' => 'textfield',
    '#title' => t('URL to wayf gateway'),
    '#default_value' => isset($default['gatewayf']) ? $default['gatewayf'] : 'https://dringo-ssl.dbc.dk/gatewayf',
    '#description' => t('Where to go for authentication via wayf', array(), array('context' => 'ding_wayf')),
    '#required' => TRUE,
  );

  // Checkboxes wayf- and nemid-login.
  $form['ding_wayf']['wayflogin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Wayf login', array(), array('context' => 'ding_wayf')),
    '#description' => t('Enable wayflogin', array(), array('context' => 'ding_wayf')),
    '#default_value' => isset($default['wayflogin']) ? $default['wayflogin'] : 0,
  );

  $form['ding_wayf']['nemlogin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Nemlogin', array(), array('context' => 'ding_wayf')),
    '#description' => t('Enable Nemlogin', array(), array('context' => 'ding_wayf')),
    '#default_value' => isset($default['nemlogin']) ? $default['nemlogin'] : 0,
  );

  return system_settings_form($form);
}

/**
 * Validation function for the administration settings form above.
 */
function ding_wayf_admin_settings_form_validate($form, $form_state) {
  $wayf = isset($form_state['values']['ding_wayf']['wayflogin']) ? $form_state['values']['ding_wayf']['wayflogin'] : NULL;
  $nemlogin = isset($form_state['values']['ding_wayf']['nemlogin']) ? $form_state['values']['ding_wayf']['nemlogin'] : NULL;

  if (empty($wayf) && empty($nemlogin)) {
    form_set_error('wayflogin', t('Either check wayf, nemlogin or both.', array(), array('context' => 'ding_wayf')));
  }
}
