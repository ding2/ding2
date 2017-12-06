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

  return system_settings_form($build);
}
