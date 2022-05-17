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

  $form['google_site_verification_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Google Search Console settings'),
    '#description' => t('Setting to add Google Site Verification key to current site'),
  ];

  $form['google_site_verification_settings']['ding_seo_google_site_verification'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Site Verification Key'),
    '#default_value' => !empty($metatag_config['google-site-verification']) ? $metatag_config['google-site-verification']['value'] : '',
    '#description' => t('Get a verification key from Google Search Console 
      by clicking on the the alternate methods tab and selecting the HTML Tag option.<br>
      It should look something like this: 
      &lt;meta name=&quot;google-site-verification&quot; content=&quot;SOMESTRINGGOESHERE&quot; /&gt;<br>
      Copy the value of the "content" attribute into the above field. 
      Remove the rest of the string so it looks like the following: SOMESTRINGGOESHERE'),
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
    '#default_value' => variable_get('ding_seo_maximum_links_in_sitemap', DING_SEO_DEFAULT_MAXIMUM_SITEMAP_LINKS),
  ];

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
  $maximum_links = $form_state['input']['ding_seo_maximum_links_in_sitemap'];
  variable_set('ding_seo_maximum_links_in_sitemap', $maximum_links);
  drupal_set_message(t('Ding seo configuration has been saved.'));
}
