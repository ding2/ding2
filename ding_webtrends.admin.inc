<?php
/**
 * @file
 * Administration interface for the webtrends module.
 */

/**
 * Admin settings form.
 */
function ding_webtrends_admin_settings_form($form_state) {
  $form = array();

  $form['webtrends_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Hostname'),
    '#description' => t('The hostname of the tracked site.'),
    '#default_value' => variable_get('webtrends_domain', FALSE),
  );

  $form['webtrends_dcs_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Site ID'),
    '#description' => t('The site identification key.'),
    '#default_value' => variable_get('webtrends_dcs_id', FALSE),
  );

  // Clear JS cache to ensure the news version is used.
  $form['#submit'][] = 'drupal_clear_js_cache';

  return system_settings_form($form);
}

