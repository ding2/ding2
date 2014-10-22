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

  return $build;
}
