<?php
/**
 * @file
 * Contains admin backend related code for search redirect.
 */

/**
 * Module main settings lay here.
 */
function ding_redirect_admin_settings($form, $form_state) {


  $form['ding_redirect_settings_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirect searches'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['ding_redirect_settings_search']['ding_redirect_settings_search_well'] = array(
    '#type' => 'textfield',
    '#title' => t('Enable redirect for search in well'),
    '#default_value' => variable_get('ding_redirect_settings_search_well', ''),
    '#description' => t('Enter the URL where to redirect users who are searching the well. Use <code>%QUERY%</code> in the URL, to send the search string with. Keep blank to disable.'),
  );

  $form['ding_redirect_settings_search']['ding_redirect_settings_search_web'] = array(
    '#type' => 'textfield',
    '#title' => t('Enable redirect for search in web'),
    '#default_value' => variable_get('ding_redirect_settings_search_web', ''),
    '#description' => t('Enter the URL where to redirect users who are searching for web. Use <code>%QUERY%</code> in the URL, to send the search string with. Keep blank to disable.'),
  );

  $form['ding_redirect_settings_search']['ding_redirect_settings_search_default'] = array(
    '#type' => 'radios',
    '#title' => t('Choose which option should be default.'),
    '#default_value' => variable_get('ding_redirect_settings_search_default', 'well'),
    '#options' => _ding_redirect_get_options(),
  );

  $form['ding_redirect_settings_login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirect login'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['ding_redirect_settings_login']['ding_redirect_settings_login_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Enable redirect of login form except the /user/login.'),
    '#default_value' => variable_get('ding_redirect_settings_login_url', ''),
    '#description' => t('Enter the URL where to redirect users when they tries to log in. Keep blank to disable.'),
  );

  return system_settings_form($form);
}
