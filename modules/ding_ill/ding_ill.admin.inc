<?php

/**
 * @file
 * Ding Ill configuration.
 */

/**
 * Admin form.
 */
function ding_ill_admin_setting_form(array $form, array &$form_state) {
  $form['ding_ill_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable interlibrary loans'),
    '#description' => t('Makes it possible to see materials from other libraries'),
    '#default_value' => variable_get('ding_ill_enabled', TRUE),
  );

  $api_url = variable_get(
    'ding_ill_api_url', 'https://openplatform.dbc.dk/v3'
  );

  $form['ding_ill_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('API URL'),
    '#description' => t('The OpenPlatform API URL'),
    '#default_value' => $api_url,
    '#required' => TRUE,
  );

  $form['ding_ill_token_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Information related to generation of API tokens.'),
  );

  $form['ding_ill_token_fieldset']['ding_ill_token_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Token URL'),
    '#description' => t('The URL for token requests (https://auth.dbc.dk/oauth/token)'),
    '#default_value' => variable_get('ding_ill_token_url', 'https://auth.dbc.dk/oauth/token'),
    '#required' => TRUE,
  );

  $form['ding_ill_token_fieldset']['ding_ill_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#description' => t('OpenPlatform client ID'),
    '#default_value' => variable_get('ding_ill_client_id'),
    '#required' => TRUE,
  );

  $form['ding_ill_token_fieldset']['ding_ill_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client Secret'),
    '#description' => t('OpenPlatform client secret'),
    '#default_value' => variable_get('ding_ill_client_secret'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
