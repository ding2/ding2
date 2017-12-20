<?php

/**
 * @file
 * Admin settings for ting search ortograf autocomplete.
 */

/**
 * Ting Search Ortograf admin form
 */
function ting_search_ortograf_admin() {

  $form['ting_search_ortograf_webservice'] = array(
    '#type' => 'fieldset',
    '#title' => t('Autocomplete URL', array(), array('context' => 'ting_search_ortograf')),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
  ); 

  $form['ting_search_ortograf_webservice']['ting_search_ortograf_suggestion_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Autocomplete URL', array(), array('context' => 'ting_search_ortograf')),
    '#description' => t('URL to Autocomplete webservice. F.ex.: https://ortograf.dbc.dk/ortograf/suggest', array(), array('context' => 'ting_search_ortograf')),
    '#default_value' => variable_get('ting_search_ortograf_suggestion_url', NULL),
    '#required' => TRUE,
  );

  $form['ting_search_ortograf_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Autocomplete settings', array(), array('context' => 'ting_search_ortograf')),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
  );

  $form['ting_search_ortograf_settings']['ting_search_ortograf_rows'] = array(
    '#type' => 'textfield',
    '#title' => t('Max suggestions', array(), array('context' => 'ting_search_ortograf')),
    '#default_value' => variable_get('ting_search_ortograf_rows', 10),
    '#element_validate' => array('element_validate_integer_positive'), 
    '#description' => t('Maximum suggestions to return. Default 10', array(), array('context' => 'ting_search_ortograf')),
  );

  $form['ting_search_ortograf_settings']['ting_search_ortograf_minimum_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum string', array(), array('context' => 'ting_search_ortograf')),
    '#description' => t('Minimum characters the user has to type before the suggestionservice is queried. Default 3', array(), array('context' => 'ting_search_ortograf')),
    '#default_value' => variable_get('ting_search_ortograf_minimum_string', 3),
    '#element_validate' => array('element_validate_integer_positive'), 
  );

  return system_settings_form($form);
}


/**
 * Validation handler for ting_search_ortograf_admin
 */
function ting_search_ortograf_admin_validate($form, &$form_state) {
  $form_state['values']['ting_search_ortograf_suggestion_url'] = trim($form_state['values']['ting_search_ortograf_suggestion_url']);
  if (!filter_var($form_state['values']['ting_search_ortograf_suggestion_url'], FILTER_VALIDATE_URL)) {
    form_set_error(
      'ting_search_ortograf_suggestion_url',
      t('Invalid URL: %url',
        array('%url' => $form_state['values']['ting_search_ortograf_suggestion_url']),
        array('context' => 'ting_search_ortograf'))
      );
  }
}
