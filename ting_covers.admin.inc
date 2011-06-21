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

  $form['styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cover image styles'),
    '#description' => t("Select the cover image style for each view mode."),
  );

  $entity_info = entity_get_info('ting_object');
  foreach ($entity_info['view modes'] as $mode => $view_mode) {
    $form['styles']['ting_covers_' . $mode. '_style'] = array(
      '#type' => 'select',
      '#title' => $view_mode['label'],
      '#options' => _ting_covers_image_style_options(),
      '#default_value' => variable_get('ting_covers_' . $mode . '_style', 'thumbnail'),
    );
  }

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

  return system_settings_form($form);
}

function _ting_covers_image_style_options() {
  $styles = image_styles();
  foreach ($styles as $id => &$style) {
    $style = $style['name'];
  }
  return $styles;
}
