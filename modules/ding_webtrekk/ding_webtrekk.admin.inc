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
    '#description' => t('Enter the TagIntegration domain here, if the TagIntegration file should be loaded from a Webtrekk server.'),
    '#default_value' => variable_get('webtrekk_ti_domain', ''),
  ];
  $form['webtrekk_ti_id'] = [
    '#type' => 'textfield',
    '#title' => t('TagIntegration ID'),
    '#description' => t('Enter your TagIntegration customer ID here.'),
    '#default_value' => variable_get('webtrekk_ti_id', ''),
  ];
  
  return system_settings_form($form);
}
