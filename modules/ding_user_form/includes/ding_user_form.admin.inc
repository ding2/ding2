<?php
/**
 * @file
 * Ding user settings.
 */

/**
 * Ding user admin.
 */
function ding_user_form_admin_setting_form($form, &$form_state) {
  $form['ding_user_signup_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link'),
    '#default_value' => variable_get('ding_user_signup_link', ''),
    '#description' => t('The link is used in the text next to the log-in form'),
  );

  $limits = drupal_map_assoc(array(0, 900, 1800, 3600, 7200, 18000, 43200, 86400), 'format_interval');
  $limits[0] = t('Disable');

  $form['ding_user_provider_session_expire'] = array(
    '#type' => 'select',
    '#title' => t('Expire provider sessions'),
    '#description' => t('Select the maximum age for provider sesssions with no activity. Sessions will be pruned on cron runs and cron must therefore be configured accordingly.'),
    '#options' => $limits,
    // ding_base features sets the auto-logout for providers to 900 seconds, so we use a default value corresponding to that.
    '#default_value' => variable_get('ding_user_provider_session_expire', 900),
  );



  return system_settings_form($form);
}

/**
 * Validate user admin form.
 */
function ding_user_form_admin_setting_form_validate($form, &$form_state) {
  if (!valid_url($form_state['values']['ding_user_signup_link'])) {
    form_set_error('ding_user_signup_link', t('Not a valid URL.'));
  }
}
