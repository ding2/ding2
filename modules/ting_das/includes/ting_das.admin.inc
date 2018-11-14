<?php

/**
 * @file
 * Define the administration interface for the module.
 */

define('TING_DAS_PLACEMENT_WEIGHT_ABOVE', 10);
define('TING_DAS_PLACEMENT_WEIGHT_BELOW', 20);

/**
 * Admin settings form for Ting DAS integration.
 */
function ting_das_admin_settings_form() {
  $form = array();

  $form['ting_das'] = array(
    '#type' => 'fieldset',
    '#title' => t('Digital article server'),
    '#tree' => TRUE,
  );

  $defaults = variable_get('ting_das', array(
    'url' => '',
    'username' => '',
    'password' => '',
  ));

  $form['ting_das']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('End point'),
    '#description' => t('The service endpoint for "placeCopyRequest", e.g. https://developer.statsbiblioteket.dk/elba-webservices/services/placeCopyRequest'),
    '#default_value' => $defaults['url'],
    '#required' => TRUE,
  );

  // Username / password.
  $form['ting_das']['username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The username required to use the web-service.'),
    '#default_value' => $defaults['username'],
    '#required' => TRUE,
  );

  $form['ting_das']['password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('The password required to use the web-service.'),
    '#default_value' => $defaults['password'],
    '#required' => TRUE,
  );

  $types = variable_get('ting_well_types', _ting_fetch_well_types());
  $form['ting_das_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Data well types'),
    '#description' => t('Ting objects defined as being to able order via the DAS service.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ting_das_types']['ting_das_data_well_types'] = array(
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc($types),
    '#default_value' => _ting_das_get_configured_well_types(),
  );

  $defaults = variable_get('ting_das_text', array(
    'description' => array(
      'format' => 'ding_wysiwyg',
      'value' => '',
    ),
    'gdpr' => array(
      'format' => 'ding_wysiwyg',
      'value' => '',
    ),
    'placement' => TING_DAS_PLACEMENT_WEIGHT_ABOVE,
  ));

  $form['ting_das_text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Digital article server'),
    '#description' => t('Information to the user about the usage for the data sent and handled by the DAS service.'),
    '#tree' => TRUE,
  );

  $form['ting_das_text']['description'] = array(
    '#type' => 'text_format',
    '#title' => t('Description about the form (prefix) or service'),
    '#rows' => 8,
    '#format' => $defaults['description']['format'],
    '#default_value' => $defaults['description']['value'],
  );

  $form['ting_das_text']['gdpr'] = array(
    '#type' => 'text_format',
    '#title' => t('Description of data usage (GDPR)'),
    '#rows' => 8,
    '#format' => $defaults['gdpr']['format'],
    '#default_value' => $defaults['gdpr']['value'],
  );

  $form['ting_das_text']['placement'] = array(
    '#type' => 'select',
    '#title' => t('Placement'),
    '#description' => t('The placement of the text in relation to the "Place order" button.'),
    '#options' => array(
      TING_DAS_PLACEMENT_WEIGHT_ABOVE => t('Above'),
      TING_DAS_PLACEMENT_WEIGHT_BELOW => t('Below'),
    ),
    '#default_value' => isset($defaults['placement']) ? $defaults['placement'] : 10,
  );

  return system_settings_form($form);
}
