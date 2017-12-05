<?php
/**
 * @file
 * Administration form definition.
 */

/**
 * Define admin page.
 */
function ding_webtrekk_admin_settings_form() {
  $form = [];
  
  $form['webtrekk_ti_domain'] = [
    '#type' => 'textfield',
    '#title' => t('TagIntegration Domain'),
    '#description' => t('Enter the TagIntegration domain here, if the TagIntegration file should be loaded from aWebtrekk server.'),
    '#default_value' => variable_get('webtrekk_ti_domain', ''),
  ];
  $form['webtrekk_ti_id'] = [
    '#type' => 'textfield',
    '#title' => t('TagIntegration ID'),
    '#description' => t('Enter your TagIntegration customer ID here, if the TagIntegration file should be loaded from aWebtrekk server.'),
    '#default_value' => variable_get('webtrekk_ti_id', ''),
  ];
  $form['webtrekk_custom_domain'] = [
    '#type' => 'textfield',
    '#title' => t('Custom Domain'),
    '#description' => t('Enter your domain here, if the TagIntegration file should be loaded from your server.'),
    '#default_value' => variable_get('webtrekk_custom_domain', ''),
  ];
  $form['webtrekk_custom_path'] = [
    '#type' => 'textfield',
    '#title' => t('Custom Path'),
    '#description' => t('Enter the path to your JavaScript file here, if the TagIntegration file should be loaded from your server.'),
    '#default_value' => variable_get('webtrekk_custom_path', ''),
  ];
  
  return system_settings_form($form);
}
