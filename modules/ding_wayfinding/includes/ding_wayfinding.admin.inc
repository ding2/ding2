<?php
/**
 * @file
 * Administrative forms for the module.
 */

/**
 * Defines the administration form for this module.
 */
function ding_wayfinding_settings_form() {
  $form = [
    '#tree' => FALSE,
    'access' => [
      '#type' => 'fieldset',
      '#title' => 'Access settings',
    ],
    'branches' => [
      '#type' => 'fieldset',
      '#title' => 'Branch selection',
    ],
  ];


  $form['access']['ding_wayfinding_customer_id'] = [
    '#type' => 'textfield',
    '#title' => t('Customer id'),
    '#default_value' => variable_get('ding_wayfinding_customer_id', ''),
  ];

  $form['access']['ding_wayfinding_api_key'] = [
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => variable_get('ding_wayfinding_api_key', ''),
  ];

  $form['access']['ding_wayfinding_agency_id'] = [
    '#type' => 'textfield',
    '#title' => t('Agency id'),
    '#description' => t('You library agency id without the "DK-" prefix. Defaults to the agency used by the provider.'),
    '#default_value' => ding_wayfinding_get_agency_id(),
  ];

  $form['access']['ding_wayfinding_type'] = [
    '#type' => 'select',
    '#title' => t('Type of data to base POI on'),
    '#description' => t(''),
    '#options' => array('ims' => 'IMS', 'fbs' => 'FBS'),
    '#default_value' => variable_get('ding_wayfinding_type', 'fbs'),
  ];


  $form['branches']['ding_wayfinding_branches'] = [
    '#type' => 'checkboxes',
    '#descriptions' => t('Select the branches that supports way finding'),
    '#default_value' => variable_get('ding_wayfinding_branches', []),
    '#options' => ding_wayfinding_get_branches(),
  ];

  # Support branches
  return system_settings_form($form);
}
