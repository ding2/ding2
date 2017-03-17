<?php
/**
 * @file
 * Ding user settings.
 */

/**
 * Ding user admin.
 */
function ding_user_admin_setting_form($form, &$form_state) {
  $form['ding_user_signup_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link'),
    '#default_value' => variable_get('ding_user_signup_link', ''),
    '#description' => t('The link is used in the text next to the log-in form'),
  );

  return system_settings_form($form);
}

/**
 * Validate user admin form.
 */
function ding_user_admin_setting_form_validate($form, &$form_state) {
  if (!empty($form_state['values']['ding_user_signup_link'])) {
    if (!(0 === strpos($form_state['values']['ding_user_signup_link'], 'http'))) {
      form_set_error('ding_user_signup_link', t('User signup link must start with "http"'));
    }
  }
}
