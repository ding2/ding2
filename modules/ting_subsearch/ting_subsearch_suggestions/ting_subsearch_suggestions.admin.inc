<?php

/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_suggestions_form_opensearch_admin_settings_alter(&$form, &$form_state) {
  // KPI.
  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting Subsearch');
  $form['subsearch_settings']['#description'] = t('Feature modules allow additional searches to be made based on predefined conditions.');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['suggestions_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Suggestions settings'),
    '#weight' => 1,
  ];

  $form['subsearch_settings']['suggestions_settings']['ting_subsearch_suggestions_distance'] = [
    '#type' => 'textfield',
    '#title' => t('Levenshtein distance'),
    '#default_value' => variable_get('ting_subsearch_suggestions_distance', 3),
    '#description' => t('Enter the maximum Levenshtein Distance here, ie. the maximum number of characters to replace, insert or delete to transform the input string into a string from the suggestion data. A higher numbere allows for less similar words to be suggested.'),
    '#element_validate' => ['ting_subsearch_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['suggestions_settings']['ting_subsearch_suggestions_trigger_limit'] = [
    '#type' => 'textfield',
    '#title' => t('Number of hits to trigger suggestions subsearch'),
    '#default_value' => variable_get('ting_subsearch_suggestions_trigger_limit', 5),
    '#description' => t('In order to trigger a subsearch which will provide a suggestion to the user, the user-provided search string must trigger at most this number of hits. NOTE: User-provided searches that trigger 0 hits always trigger a subsearch.'),
    '#element_validate' => ['ting_subsearch_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['suggestions_settings']['ting_subsearch_suggestions_ps_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Ratio between primary and secondary searches for suggestions'),
    '#default_value' => variable_get('ting_subsearch_suggestions_ps_factor', 10),
    '#description' => t('Factor between amount of results from primary and secondary search for displaying suggestions.'),
    '#element_validate' => ['ting_subsearch_sensitive_fields_validate'],
  ];
}
