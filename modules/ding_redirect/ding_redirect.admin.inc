<?php
/**
 * @file
 * Contains admin backend related code for ding redirect.
 */

/**
 * Settings fields for search and login redirect.
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
    '#maxlength' => 500,
  );

  $form['ding_redirect_settings_dialog'] = array(
    '#type' => 'fieldset',
    '#title' => t('Popup dialog'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' => t('Enables a dialog to popup and notifies the user when a redirect is happening.'),
  );

  $form['ding_redirect_settings_dialog']['ding_redirect_settings_dialog_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Delay time in miliseconds'),
    '#default_value' => variable_get('ding_redirect_settings_dialog_delay', 3000),
    '#description' => t('Miliseconds to delay the redirection. Default 3000 miliseconds = 3 seconds. Use -1 to disable dialog and delay.'),
  );

  $form['ding_redirect_settings_dialog']['ding_redirect_settings_dialog_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title of dialog shown to the user before redirecting.'),
    '#default_value' => variable_get('ding_redirect_settings_dialog_title', t('Redirecting...')),
  );

  $form['ding_redirect_settings_dialog']['ding_redirect_settings_dialog_text'] = array(
    '#type' => 'textarea',
    '#rows' => 15,
    '#title' => t('Content of dialog shown to the user before redirecting.'),
    '#default_value' => variable_get('ding_redirect_settings_dialog_text', t('You are being redirected to an external login page. Close this dialog to stop redirecting.')),
    '#description' => t('Enter the content to show in the dialog to the user, before they are getting redirected. You can use HTML.'),
  );

  return system_settings_form($form);
}
