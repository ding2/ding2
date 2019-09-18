<?php

/**
 * @file
 * Ding user settings.
 */

/**
 * Ding user admin.
 */
function ding_user_admin_setting_form($form, &$form_state) {
  $limits = drupal_map_assoc(array(
    0,
    900,
    1800,
    3600,
    7200,
    18000,
    43200,
    86400,
  ), 'format_interval');

  $limits[0] = t('Disable');

  $form['ding_user_provider_session_expire'] = array(
    '#type' => 'select',
    '#title' => t('Expire provider sessions'),
    '#description' => t('Select the maximum age for provider sesssions with no activity. Sessions will be pruned on cron runs and cron must therefore be configured accordingly. Alternatively, the lightweight cron option this module provides can be used, if sessions needs to be pruned more often than is practical with core cron.'),
    '#options' => $limits,
    // ding_base features sets the auto-logout for providers to 900 seconds, so we use a default value corresponding to that.
    '#default_value' => variable_get('ding_user_provider_session_expire', 900),
  );

  $form['ding_user_session_expire_cron'] = array(
    '#markup' => '<p>' . t('This module provides a lightweight cron endpoint, which only expires provider sessions. Use to following endpoint to run it: %path', array(
      '%path' => '/ding_user/expire_sessions/cron/' . variable_get('cron_key'),
    )) . '</p>',
  );

  return system_settings_form($form);
}
