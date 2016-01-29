<?php
/**
 * @file
 * Defines the administration interface for the module.
 */

/**
 * Implements hook_form().
 */
function ding_gatewayf_admin_settings_form() {
  $form = array();
  $defaults = variable_get('ding_gatewayf', array());

  $form['ding_gatewayf'] = array(
    '#tree' => TRUE,
  );

  $form['ding_gatewayf']['service'] = array(
    '#type' => 'fieldset',
    '#title' => t('Service configuration'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['ding_gatewayf']['service']['endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Gateway WAYF URL'),
    '#description' => t('Endpoint URL for the gateway WAYF service.'),
    '#default_value' => isset($defaults['service']['endpoint']) ? $defaults['service']['endpoint'] : 'https://bibliotek.dk/gatewayf/gatewayf.php',
  );

  $form['ding_gatewayf']['development'] = array(
    '#type' => 'fieldset',
    '#title' => t('Development configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ding_gatewayf']['development']['log_auth_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log authentication requests'),
    '#default_value' => isset($defaults['development']['log_auth_data']) ? $defaults['development']['log_auth_data'] : FALSE,
    '#description' => t('Log authentication data including attributes. This can be useful for debugging.'),
  );

  return system_settings_form($form);
}
