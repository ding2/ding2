<?php
/**
 * @file
 * Ding SEO settings.
 */

 /**
 * Administration settings form for the module.
 */
function ding_seo_admin_settings($form, &$form_state) {
  $metatag_config = metatag_config_load('global')->config;
  $form['ding_seo_google_site_verification'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Site Verification'),
    '#default_value' => !empty($metatag_config['google-site-verification']) ? $metatag_config['google-site-verification']['value'] : '',
    '#description' => t('A string provided in Google Search Console.'),
  );

  $form['sitemap_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Sitemap settings'),
    '#description' => t('Settings for processing Ting objects into sitemap links'),
  ];

  $form['sitemap_settings']['ding_seo_maximum_links_in_sitemap'] = [
    '#type' => 'textfield',
    '#title' => t('Maximum Number of links in sitemap'),
    '#description' => t('The maximum number of links we allow in sitemaps. To large a number leads to performance strain on the server'),
    '#default_value' => variable_get('ding_seo_maximum_links_in_sitemap', 50000),
  ];

  $form['sitemap_settings']['ding_seo_number_of_links_to_delete'] = [
    '#type' => 'textfield',
    '#title' => t('Number of links to delete'),
    '#description' => t('How many links we delete to make number for new links. The links which have not been visited the longest are deleted'),
    '#default_value' => variable_get('ding_seo_number_of_links_to_delete', 1000),
  ];

  return system_settings_form($form);
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
