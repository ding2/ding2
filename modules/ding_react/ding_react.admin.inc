<?php

/**
 * @file
 * Admin settings for Ding React module.
 */

/**
 * Admin settings for the module.
 */
function ding_react_admin_settings_form($form, &$form_state) {
  $form['services'] = [
    '#type' => 'fieldset',
    '#title' => t('Services'),
  ];

  $form['services']['ding_react_material_list_url'] = [
    '#type' => 'textfield',
    '#title' => t('Material List'),
    '#description' => t('Url to the Material List service instance to use.'),
    '#default_value' => ding_react_material_list_url(),
    '#required' => TRUE,
    '#element_validate' => ['ding_react_element_validate_url'],
  ];

  $form['services']['ding_react_follow_searches_url'] = [
    '#type' => 'textfield',
    '#title' => t('Follow Searches'),
    '#description' => t('Url to the Follow Searches service instance to use.'),
    '#default_value' => ding_react_follow_searches_url(),
    '#required' => TRUE,
    '#element_validate' => ['ding_react_element_validate_url'],
  ];

  $form['services']['ding_react_cover_service_url'] = [
    '#type' => 'textfield',
    '#title' => t('Cover Service'),
    '#description' => t('Url to the Cover Service instance to use.'),
    '#default_value' => ding_react_cover_service_url(),
    '#required' => TRUE,
    '#element_validate' => ['ding_react_element_validate_url'],
  ];

  $form['debug'] = [
    '#type' => 'fieldset',
    '#title' => t('Debugging'),
  ];
  $form['debug']['ding_react_debug'] = [
    '#type' => 'checkbox',
    '#title' => t('Enable debug logging'),
    '#default_value' => variable_get('ding_react_debug', FALSE),
  ];

  // Mimic system_settings_form().
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  ];

  return $form;
}

/**
 * Form element validator for urls.
 */
function ding_react_element_validate_url($element, &$form_state, $form) {
  if (!empty($element['#value']) && !valid_url($element['#value'], true)) {
    form_error($element, t('Please enter a valid url.'));
  }
}

/**
 * Admin settings form form submit handler.
 *
 * We do not use system_settings_form() here as our form is a mix of variables
 * and functionality. Thus we set each variable explicitly.
 */
function ding_react_admin_settings_form_submit($form, &$form_state) {
  $variables = [
    'ding_react_material_list_url',
    'ding_react_follow_searches_url',
    'ding_react_migrate_timeout',
    'ding_react_debug',
  ];
  array_walk($variables, function ($variable) use ($form_state) {
    variable_set($variable, $form_state['values'][$variable]);
  });
  drupal_set_message(t('The configuration options have been saved.'));
}
