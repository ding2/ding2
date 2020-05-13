<?php

/**
 * @file
 * Admin page callbacks for the ding_provider module.
 */

/**
 * Provides an overview of used provides, and setting pages.
 */
function ding_provider_admin_overview() {
  $build = array();
  $providers = _ding_provider_get_provider();

  if (empty($providers)) {
    $build['no-providers'] = array(
      '#markup' => t('No providers available.'),
    );
  }
  else {
    foreach ($providers as $type => $provider) {
      $build[$type] = array(
        '#type' => 'item',
        '#title' => t("Provider type '@type'", array('@type' => $type)),
        '#markup' => t('Provided by @title', array('@title' => $provider['title'])),
      );
    }
  }

  $build['ding_provider_users_wipe_threshold'] = array(
    '#type' => 'select',
    '#title' => t('Delete provider users that are inactive for:'),
    '#options' => array(
      '0' => t('None (keep all users)'),
      '31536000' => t('1 year'),
      '63072000' => t('2 years'),
      '94608000' => t('3 years'),
      '126144000' => t('4 years'),
      '157680000' => t('5 years'),
    ),
    '#default_value' => variable_get('ding_provider_users_wipe_threshold', 0),
  );

  $build['session_expire'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expire inactive provider sessions'),
    '#tree' => FALSE,
  );

  $limits = drupal_map_assoc(array(
    0,
    100,
    900,
    1800,
    3600,
    7200,
    18000,
    43200,
    86400,
  ), 'format_interval');

  $limits[0] = t('Disable');

  $build['session_expire']['ding_provider_session_expire'] = array(
    '#type' => 'select',
    '#description' => t('Select the maximum age for provider sesssions with no activity. Sessions will be pruned on cron runs and cron must therefore be configured accordingly. Alternatively, the lightweight cron option this module provides can be used, if sessions needs to be pruned more often than is practical with core cron.'),
    '#options' => $limits,
    // ding_base features sets the auto-logout for providers to 900 seconds, so we use a default value corresponding to that.
    '#default_value' => variable_get('ding_provider_session_expire', 900),
  );

  $build['session_expire']['ding_provider_session_expire_cron'] = array(
    '#markup' => '<p>' . t('This module provides a lightweight cron endpoint, which only expires provider sessions. Use to following endpoint to run it: %path', array(
      '%path' => '/ding_provider/expire_sessions/cron/' . variable_get('cron_key'),
    )) . '</p>',
  );

  return system_settings_form($build);
}
