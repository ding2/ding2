<?php
/**
 * @file
 * Administration interface for the ting_covers_rest module.
 *
 * Which allows configuration of the REST coverservice.
 */

/**
 * Form builder; Configure REST cover service settings for this site.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function ting_covers_rest_admin_settings_form($form, &$form_state) {
  $form['ting_covers_rest'] = array(
    '#type' => 'fieldset',
    '#title' => t('REST coverservice settings'),
    '#description' => t('The REST coverservice service is used to retrieve cover images.'),
    '#tree' => FALSE,
  );

  $form['ting_covers_rest']['ting_covers_rest_url'] = array(
    '#type' => 'textfield',
    '#title' => t('REST URL'),
    '#description' => t('URL to the cover service, e.g. http://rest.ddb.dk/v2'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_covers_rest_url', ''),
  );

  $form['ting_covers_rest']['ting_covers_rest_oauth2_token'] = array(
    '#type' => 'textfield',
    '#title' => t('OAuth2 token'),
    '#description' => t('REST service OAuth2 token'),
    '#required' => FALSE,
    '#default_value' => variable_get('ting_covers_rest_oauth2_token', ''),
  );

  $form['ting_covers_rest']['ting_covers_rest_group'] = array(
    '#type' => 'textfield',
    '#title' => t('Group'),
    '#description' => t('User group (normally library ID)'),
    '#required' => FALSE,
    '#default_value' => variable_get('ting_covers_rest_group', ''),
  );

  $form['ting_covers_rest']['ting_covers_rest_enable_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('ting_covers_rest_enable_logging', FALSE),
  );

  return system_settings_form($form);
}
