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
  $defaults = _ding_gatewayf_load_configuration();

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
    '#default_value' => $defaults['service']['endpoint'],
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
    '#default_value' => $defaults['development']['log_auth_data'],
    '#description' => t('Log authentication data including attributes. This can be useful for debugging.'),
  );

  return system_settings_form($form);
}
