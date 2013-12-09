<?php
/**
 * @file
 * Implements the administration UI for the module.
 */

/**
 * Menu callback that builds the administration interface for the module.
 */
function ding_wayf_admin_settings_form() {
  $form = array();

  $default = variable_get('ding_wayf', array(
    'installdir' => '/var/simplesamlphp',
    'redirect' => 'user/%uid/status',
    'sp' => 'default-sp',
    'gatewayf' => 'https://dringo-ssl.dbc.dk/gatewayf',
    'wayflogin' => 0,
    'nemlogin' => 1,
  ));

  $form['ding_wayf'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ding WAYF configuration'),
  );

  $form['ding_wayf']['ding_wayf_type'] = array(
    '#type' => 'radios',
    '#title' => t('Installation type'),
    '#description' => t('Which type of installation are you using'),
    '#options' => array(
      'local' => t('Local (same server)'),
      'gateway' => t('Gateway/proxy'),
    ),
    '#required' => TRUE,
    '#default' => variable_get('ding_wayf_type', array()),
  );

  $form['ding_wayf']['ding_wayf_local'] = array(
    '#type' => 'fieldset',
    '#title' => t('Local installation'),
    '#description' => t('SimpleSAML PHP is installed locally.'),
    '#tree' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="ding_wayf_type"]' => array('value' => 'local'),
      ),
    ),
  );

  $form['ding_wayf']['ding_wayf_local']['installdir'] = array(
    '#type' => 'textfield',
    '#title' => t('Simple SAML php installation directory'),
    '#default_value' => $default['installdir'],
    '#description' => t('Absolute path with no trailing slash to simple SAML installation.'),
  );

  $form['ding_wayf']['ding_wayf_gatewayf'] = array(
    '#type' => 'fieldset',
    '#title' => t('WAYF gateway installation'),
    '#description' => t('Communications through a SimpleSAML gateway (ask DBC).'),
    '#tree' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="ding_wayf_type"]' => array('value' => 'gateway'),
      ),
    ),
  );

  $form['ding_wayf']['ding_wayf_gatewayf']['address'] = array(
    '#type' => 'textfield',
    '#title' => t('URL to wayf gateway'),
    '#default_value' => $default['gatewayf'],
    '#description' => t('Gateway/proxy address to use in authentication.'),
  );

  $form['ding_wayf']['sp'] = array(
    '#type' => 'textfield',
    '#title' => t('Autenticaton source for this SP'),
    '#default_value' => $default['sp'],
    '#description' => t('The name of the service provider (SP) to use from /var/simplesamlphp/config/authsources.php.'),
    '#required' => TRUE,
    '#states' => array(
      'invisible' => array(
        ':input[name="ding_wayf_type"]' => array('value' => FALSE),
      ),
    ),
  );

  $form['ding_wayf']['redirect'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect fallback URL'),
    '#default_value' => $default['redirect'],
    '#description' => t('Redirect to this fallback URL after login. This URL is only used if the distination parameter is not found.'),
    '#required' => TRUE,
    '#states' => array(
      'invisible' => array(
        ':input[name="ding_wayf_type"]' => array('value' => FALSE),
      ),
    ),
  );

  $form['ding_wayf']['ding_wayf_login_type'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Login types'),
    '#description' => t('Enable login types'),
    '#required' => TRUE,
    '#options' => array(
      'wayf',
      'nemlogin',
    ),
    '#default_value' => array('nemlogin'),
    '#states' => array(
      'invisible' => array(
        ':input[name="ding_wayf_type"]' => array('value' => FALSE),
      ),
    ),
  );

  return system_settings_form($form);
}
