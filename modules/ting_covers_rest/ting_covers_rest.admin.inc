<?php

/**
 * @file
 * Admin configuration for the DDB cover service.
 */

use OpenAPI\Client\Model\Type;

/**
 * @file
 * Administration interface for the ting_covers_rest module.
 *
 * Which allows configuration of the DDB Cover Service API.
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
    '#title' => t('DDB Cover Service API settings'),
    '#description' => t('The DDB Cover Service API service is used to retrieve cover images.'),
    '#tree' => FALSE,
  );

  $form['ting_covers_rest']['ting_covers_rest_url'] = array(
    '#type' => 'textfield',
    '#title' => t('REST URL'),
    '#description' => t('URL to the cover service, e.g. https://rest.ddb.dk/v2'),
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

  $allowed_types = Type::getAllowableEnumValues();
  $form['ting_covers_rest']['ting_covers_rest_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t('The type of cover IDs'),
    '#required' => FALSE,
    '#options' => array_combine($allowed_types, $allowed_types),
    '#default_value' => variable_get('ting_covers_rest_type', Type::PID),
  );

  $form['ting_covers_rest']['ting_covers_rest_format'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Format'),
    '#description' => t('The image format of the cover images'),
    '#required' => FALSE,
    '#options' => array(
      'jpeg' => t('JPEG'),
      'png' => t('PNG'),
    ),
    '#default_value' => variable_get('ting_covers_rest_format', array('jpeg', 'png')),
  );

  $form['ting_covers_rest']['ting_covers_rest_size'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Size'),
    '#description' => t('The image size of the cover images'),
    '#required' => FALSE,
    '#options' => array(
      'thumbnail' => t('Thumbnail'),
      'default' => t('Default'),
      'original' => t('Original'),
    ),
    '#default_value' => variable_get('ting_covers_rest_size', array(
      'thumbnail', 'default', 'original',
    )),
  );

  $form['ting_covers_rest']['ting_covers_rest_enable_debugging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debugging'),
    '#default_value' => variable_get('ting_covers_rest_enable_debugging', FALSE),
  );

  return system_settings_form($form);
}
