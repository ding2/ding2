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
    '#default_value' => variable_get('ting_covers_cache_lifetime', TING_COVERS_CACHE_LIFETIME),
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
    '#description' => t('The Additional Information service is used to retrieve cover images and other information about objects. <a href="http://www.danbib.dk/index.php?doc=forsideservice">More information about the service (in Danish)</a>'),
    '#tree' => FALSE,
  );

  $form['addi']['addi_wsdl_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('URL to the Additional Information webservice, e.g. http://forside.addi.dk/addi.wsdl'),
    '#required' => TRUE,
    '#default_value' => variable_get('addi_wsdl_url', ''),
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

  $form['#submit'][] = 'ting_covers_admin_addi_settings_form_submit';

  return system_settings_form($form);
}

/**
 *  Custom submit handler for admin form.
 * 
 * @ingroup forms
 * @see ting_covers_admin_addi_settings_form()
 */
function ting_covers_admin_addi_settings_form_submit($form, $form_state) {
  $cover_service_url = $form_state['input']['addi_wsdl_url'];
  $current_service = -1;

  if (strpos($cover_service_url, 'moreinfo')) {
    $current_service = SERVICE_MOREINFO;
  }
  elseif (strpos($cover_service_url, 'forside')) {
    $current_service = SERVICE_ADDI;
  }

  variable_set('current_cover_service', $current_service);
}
