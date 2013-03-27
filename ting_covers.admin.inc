<?php

/**
 * Admin settings form for Ting covers.
 */
function ting_covers_admin_settings_form($form, &$form_state) {
  $form = array();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cover settings'),
  );

  $form['settings']['ting_covers_cache_lifetime'] = array(
    '#type' => 'select',
    '#title' => t('Cover cache lifetime'),
    '#options' => array(
      CACHE_TEMPORARY =>  t('Disable cache'),
      '86400' => t("24 hours"),
      '604800' => t("1 week"),
      '2592000' => t("1 month"),
    ),
    '#default_value' => variable_get('ting_covers_cache_lifetime', TING_COVERS_DEFAULT_CACHE_LIFETIME),
  );

  return system_settings_form($form);
}

/**
 * Form builder; Configure ADDI settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_covers_admin_addi_settings_form($form, &$form_state) {
  $form['addi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Information settings'),
    '#description' => t('The Additional Information service is used to retrieve cover images. <a href="http://www.danbib.dk/index.php?doc=moreinfo">More information about the service (in Danish)</a>'),
    '#tree' => FALSE,
  );

  $form['addi']['addi_wsdl_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('URL to the Additional Information webservice, e.g. http://moreinfo.addi.dk/2.1/'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_wsdl_url', ''),
  );

  $form['addi']['addi_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('VIP database username'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_username', ''),
  );

  $form['addi']['addi_group'] = array(
    '#type' => 'textfield',
    '#title' => t('Group'),
    '#description' => t('User group (normally library ID)'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_group', ''),
  );

  $form['addi']['addi_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('VIP database password'),
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
