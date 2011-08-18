<?php

function ding_wayf_admin_settings_form() {
  $form = array(
    '#tree' => TRUE,
  );

  // Load default values
  $default = variable_get('ding_wayf', array(
    'installdir' => '/var/simplesamlphp',
    'attribute' => 'schacPersonalUniqueID',
    'attribute_field' => 'CPR',
    'redirect' => 'user/%uid/status',
  ));

  $form['ding_wayf']['installdir'] = array(
    '#type' => 'textfield',
    '#title' => t('Simple SAML php instalation directory'),
    '#default_value' => $default['installdir'],
    '#description' => t('Absolute path with no trailing slash to simple SAML installation.'),
    '#required' => TRUE,
  );

  $form['ding_wayf']['sp'] = array(
    '#type' => 'textfield',
    '#title' => t('Autenticaton source for this SP'),
    '#default_value' => isset($default['sp']) ? $default['sp'] : 'default-sp',
    '#description' => t('The name of the service provider (SP) to use from /var/simplesamlphp/config/authsources.php.'),
    '#required' => TRUE,
  );

  $form['ding_wayf']['attribute'] = array(
    '#type' => 'textfield',
    '#title' => t('Which attribute from simpleSAMLphp should be used as to extract credentials'),
    '#default_value' => $default['attribute'],
    '#description' => t('The attribute that contains the credentials.'),
    '#required' => TRUE,
  );

  $form['ding_wayf']['attribute_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Which field should be extracted'),
    '#default_value' => $default['attribute_field'],
    '#description' => t('By default the CPR number will be extracted (urn:mace:terena.org:schac:uniqueID:dk:CPR:0708741234).'),
    '#required' => TRUE,
  );

  $form['ding_wayf']['redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect fallback URL'),
    '#default_value' => $default['redirect'],
    '#description' => t('Redirect to this fallback URL after login. This URL is only used if distination is not found. The token %uid is avaliable'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Validation function for the administration settings form above.
 */
function ding_wayf_admin_settings_form_validate($form, $form_state) {
  // Check that simpleSAMLphp is found at the location given.
  if (!ding_wayf_check_simplesamlphp($form_state['values']['ding_wayf']['installdir'])) {
    form_set_error('installdir', t('Simple SAML php was not found at the location given.'));
  }
}
