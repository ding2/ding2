<?php

/**
 * @file
 * Admin page callback file for the ting module.
 */

/**
 * Form builder; Configure ting settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_admin_ting_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  $form = array();

  $form['ting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ting service settings'),
    '#tree' => FALSE,
  );

  $form['ting']['ting_agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Library code'),
    '#description' => t('The 6-digit code representing the library organization'),
    '#default_value' => variable_get('ting_agency', ''),
  );

  $form['ting']['ting_search_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Search service URL'),
    '#description' => t('URL to the Ting search webservice, e.g. http://opensearch.addi.dk/1.1/'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_search_url', ''),
  );

  $form['ting']['ting_scan_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Scan service URL'),
    '#description' => t('URL to the Ting scan webservice, e.g. http://openscan.addi.dk/1.7/'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_scan_url', ''),
  );

  $form['ting']['ting_spell_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Spell service URL'),
    '#description' => t('URL to the Ting spell webservice, e.g. http://openspell.addi.dk/1.2/'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_spell_url', ''),
  );

  $form['ting']['ting_recommendation_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Recommendation service URL'),
    '#description' => t('URL to the Ting recommendation webservice (Andre der har lånt...) , e.g. http://openadhl.addi.dk/1.1/'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_recommendation_url', ''),
  );

  $form['ting']['ting_enable_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('ting_enable_logging', FALSE),
  );

  $intervals = array(
    60,
    300,
    900,
    1800,
    3600,
    10800,
    43200,
    86400,
    259200,
    604800,
  );
  $options = array(
    0 => t('No caching'),
  );

  foreach ($intervals as $interval) {
    $options[$interval] = format_interval($interval, 2);
  }

  $form['ting']['ting_cache_lifetime'] = array(
    '#type' => 'select',
    '#title' => t('Cache lifetime'),
    '#default_value' => variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME),
    '#options' => $options,
    '#description' => t("Cache answers from the datawell for this time. At least a few minutes is recommended, so the same objects doesn't have to be fetched on each page request."),
  );

  return system_settings_form($form);
}

/**
 * Form builder; Configure ADDI settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_admin_addi_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  $form['addi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Information settings'),
    '#description' => t('The Additional Information service is used to retrieve cover images and other information about objects. <a href="http://www.danbib.dk/index.php?doc=forsideservice">More information about the service (in Danish)</a>'),
    '#tree' => FALSE,
  );

  $form['addi']['addi_wdsl_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('URL to the Additional Information webservice, e.g. http://forside.addi.dk/addi.wsdl'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_wdsl_url', ''),
  );

  $form['addi']['addi_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('Username for the Additional information webservice'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_username', ''),
  );

  $form['addi']['addi_group'] = array(
    '#type' => 'textfield',
    '#title' => t('Group'),
    '#description' => t('User group for the Additional information webservice'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_group', ''),
  );

  $form['addi']['addi_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('Password for the Additional information webservice'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_password', ''),
  );

  $form['addi']['addi_enable_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('addi_enable_logging', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Form builder; Configure proxy settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_admin_proxy_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  $form['proxy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Proxy service'),
    '#description' => t('Restricted-access resources referenced by Ting may be accessed through the library\'s proxy server'),
    '#tree' => FALSE,
  );

  $form['proxy']['restricted_access_proxy_prefix'] = array(
    '#type' => 'textfield',
    '#title' => 'Proxy server URL prefix',
    '#default_value' => variable_get('restricted_access_proxy_prefix', ''),
    '#description' => t('E.g. <em>http://proxy.example.com/?url=</em>.'),
  );

  $form['proxy']['restricted_access_proxy_hostnames'] = array(
    '#type' => 'textarea',
    '#title' => 'Hostnames',
    '#rows' => 15,
    '#default_value' => implode("\n", variable_get('restricted_access_proxy_hostnames', array())),
    '#value_callback' => 'ting_admin_settings_hostnames_value',
    '#description' => t('Enter one hostname per line, e.g. <em>magazine.example.com</em>. Do not include the <em>http://</em> prefix.'),
  );

    return system_settings_form($form);
}

/**
 * Value callback for restricted_access_proxy_hostnames field defined in
 * ting_admin_proxy_settings().
 */
function ting_admin_settings_hostnames_value($form, $edit = FALSE) {
  if ($edit !== FALSE) {
    return array_filter(array_map('trim', explode("\n", $edit)));
  }
}

/**
 * @brief Implementation of hook_menu()
 *
 * Felter: Forfatter, titel, emneord,
 */
function ting_admin_register_settings() {
  $form['ting_admin_register_serie_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Serie title'),
    '#description' => t('Specify the register to be used for searching against serie titles.'),
    '#default_value' => variable_get('ting_admin_register_serie_title', 'phrase.title')
  );

  $form['#submit'][] = 'ting_search_extendform_admin_settings_submit';
  return system_settings_form($form);
}

function ting_admin_register_settings_validate($form, &$form_state) {
  $s = '';
  if (isset($form_state['values']['ting_admin_register_serie_title'])) {
    $s = $form_state['values']['ting_admin_register_serie_title'];
  }

  if ($s == '') {
    form_set_error('ting_admin_register_serie_title', t('Please specify a register for serie titles.'));
  }
}

function ting_search_extendform_admin_settings_submit($form, $form_state) {
  variable_set('ting_admin_register_serie_title', $form_state['values']['ting_admin_register_serie_title']);
}

/**
 * Form builder; Configure labels for online_url.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_admin_online_url_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  form_load_include($form_state, 'inc', 'ting', 'ting.client');
  $form = array();

  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from datawell'),
    '#description' => t('Update the list of known types by asking the datawell for all types.')
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_admin_online_url_settings_update_types'),
  );

  $settings = variable_get('ting_url_labels', _ting_default_url_labels());
  $types = variable_get('ting_url_labels_types', array());
  $form['ting_url_labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Labels'),
    '#tree' => TRUE,
  );

  $form['ting_url_labels']['_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Default label'),
    '#default_value' => isset($settings['_default']) ? $settings['_default'] : '',
    '#description' => t('Default label used for types that is not specifically set below.'),
  );

  if (sizeof($types)) {
    $form['ting_url_labels']['types'] = array(
      '#type' => 'fieldset',
      '#title' => t('Type specific labels'),
      '#tree' => TRUE,
      '#description' => t("Here you may override the default label for individual material types."),
    );

    foreach ($types as $term => $count) {
      $form['ting_url_labels']['types'][$term] = array(
        '#type' => 'textfield',
        '#title' => $term,
        '#default_value' => isset($settings[$term]) ? $settings[$term] : '',
        '#description' => t('Count: @count', array('@count' => $count)),
        // Fudge the parent so we'll get all the labels in one big array in
        // ting_url_labels.
        '#parents' => array('ting_url_labels', $term),
      );
    }
  }

  return system_settings_form($form);
}

/**
 * Submit handler. Updates the list of known types from the datawell.
 */
function ting_admin_online_url_settings_update_types($form, &$form_state) {
  // Get a list of types by executing a null query and look at the facets
  // result.
  $options = array(
    'facets' => array('facet.type'),
    'numFacets' => 99,
    'reply_only' => TRUE,
    'sort' => 'random',
  );
  $result = ting_do_search("*=*", 0, 0, $options);

  $types = array();
  foreach ($result->facets['facet.type']->terms as $term => $count) {
    $types[drupal_strtolower($term)] = $count;
  }

  // Only save if we actually got any types.
  if (!empty($types)) {
    variable_set('ting_url_labels_types', $types);
  }
}