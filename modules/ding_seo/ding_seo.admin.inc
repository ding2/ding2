<?php
/**
 * @file
 * Ding SEO settings.
 */

 /**
 * Administration settings form for the module.
 */
function ding_seo_admin_settings($form, &$form_state) {

  $form['ding_seo_google_site_verification'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Site Verification'),
    '#default_value' => metatag_config_load('global')->config['google-site-verification']['value'],
    '#description' => t('A string provided in Google Search Console.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for the administration settings form.
 */
function ding_seo_admin_settings_submit($form, &$form_state) {

  // Save the google site verification code to the metatag verification module
  $config = metatag_config_load('global');
  $config->config['google-site-verification']['value'] = $form_state['input']['ding_seo_google_site_verification'];
  metatag_config_save($config);
  drupal_set_message(t('Google Site Verification has been saved.'));
}
