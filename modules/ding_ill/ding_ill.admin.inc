<?php
/**
 * @file
 * Ding Ill configuration.
 */

/**
 * Admin form.
 */
function ding_ill_admin_setting_form(array $form, array &$form_state) {
  $api_url = variable_get(
    'ding_ill_api_url', 'https://openplatform.dbc.dk/v3/'
  );

  $form['ding_ill_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('API URL'),
    '#description' => t('The OpenPlatform API URL'),
    '#default_value' => variable_get('ding_ill_api_url', 'https://openplatform.dbc.dk/v3/'),
  );

  $form['ding_ill_token_fieldset'] = array(
    '#type' => 'fieldset',
  );

  $form['ding_ill_token_fieldset']['ding_ill_description'] = array(
    '#type' => 'link',
    '#title' => t('Generate OpenPlatform token here'),
    '#href' => $api_url,
    '#attributes' => array('target' => '_blank'),
  );

  $form['ding_ill_token_fieldset']['ding_ill_token'] = array(
    '#type' => 'textfield',
    '#title' => t('API token'),
    '#description' => t('OpenPlatform token can be generated here: @url', array(
      '@url' => $api_url,
    )),
    '#default_value' => variable_get('ding_ill_token'),
  );

  return system_settings_form($form);
}
