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
    '#description' => t('URL to the Additional Information webservice, e.g. http://moreinfo.addi.dk/2.11'),
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

  $form['addi']['external_url'] = array(
    '#type' => 'fieldset',
    '#title' => t('External URL'),
    '#description' => t('For some materials without cover, the service will return an URL to an external cover supplied by the owner of the record. Use these settings enable/disable this feature and, if enabled, which sources to use them on.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['addi']['external_url']['ting_covers_addi_external_url'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable external URL'),
    '#default_value' => variable_get('ting_covers_addi_external_url', TRUE),
  );

  $sources = variable_get('ting_well_sources', array());
  $form['addi']['external_url']['ting_covers_addi_external_url_sources'] = array(
    '#type' => 'checkboxes',
    '#title' => t('External URL sources'),
    '#options' => drupal_map_assoc($sources),
    '#default_value' => variable_get('ting_covers_addi_external_url_sources', _ting_covers_addi_default_external_url_sources()),
  );

  $form['addi']['external_url']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update sources'),
    '#submit' => array('ting_covers_addi_source_update'),
  );

  return system_settings_form($form);
}

/**
 * Submit handler.
 *
 * Updates the list of known sources from the data well.
 */
function ting_covers_addi_source_update($form, &$form_state) {
  _ting_fetch_well_sources();
}
