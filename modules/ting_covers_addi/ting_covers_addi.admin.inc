<?php
/**
 * @file
 * Administration interface for the ting_covers_addi module.
 *
 * Which allows configuration of moreinfo end-points and cache lifetime.
 */

/**
 * Form builder; Configure ADDI settings for this site.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function ting_covers_addi_admin_settings_form($form, &$form_state) {
  $form['addi'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Information settings'),
    '#description' => t('The Additional Information service is used to retrieve cover images. <a href="http://www.danbib.dk/index.php?doc=moreinfo">More information about the service (in Danish)</a>'),
    '#tree' => FALSE,
  );

  $form['addi']['ting_covers_addi_wsdl_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('URL to the Additional Information webservice, e.g. http://moreinfo.addi.dk/2.1/'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_covers_addi_wsdl_url', ''),
  );

  $form['addi']['ting_covers_addi_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('VIP database username'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_covers_addi_username', ''),
  );

  $form['addi']['ting_covers_addi_group'] = array(
    '#type' => 'textfield',
    '#title' => t('Group'),
    '#description' => t('User group (normally library ID)'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_covers_addi_group', ''),
  );

  $form['addi']['ting_covers_addi_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('VIP database password'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_covers_addi_password', ''),
  );

  $form['addi']['ting_covers_addi_enable_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('ting_covers_addi_enable_logging', FALSE),
  );

  return system_settings_form($form);
}
