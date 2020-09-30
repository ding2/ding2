<?php

/**
 * @file
 * Administration interface for ting subsearch suggestions.
 */

/**
 * Admin settings form for ting subsearch suggestions.
 */
function ting_subsearch_suggestions_admin_settings_form($form, &$form_state) {
  $form = [];

  // Info.
  $form['info'] = [
    '#type' => 'item',
    '#title' => t('Ting subsearch suggestions'),
    '#description' => t('Trigger subsearches based on autocomplete suggestions and levenshtein distance.'),
  ];

  // Trigger settings.
  $form['trigger'] = [
    '#type' => 'fieldset',
    '#title' => t('Trigger'),
  ];
  $form['trigger']['ting_subsearch_suggestions_distance'] = [
    '#type' => 'textfield',
    '#title' => t('Maximum Levenshtein distance'),
    '#default_value' => variable_get('ting_subsearch_suggestions_distance', 3),
    '#description' => t('The maximum Levenshtein distance between a suggestion and the user search for it to be used in a subsearch and possibly shown as a suggestion to the user. A higher numbere allows for less similar words to be suggested.'),
    '#element_validate' => ['element_validate_integer_positive'],
  ];
  $form['trigger']['ting_subsearch_suggestions_trigger_limit'] = [
    '#type' => 'textfield',
    '#title' => t('Maximum number of results for user search'),
    '#default_value' => variable_get('ting_subsearch_suggestions_trigger_limit', 5),
    '#description' => t("If the user search returned more results than this don't bother trying to find a suggestion and perform subsearch."),
    '#element_validate' => ['element_validate_integer_positive'],
  ];
  $form['trigger']['ting_subsearch_suggestions_ps_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum ratio between suggestion and user search results'),
    '#default_value' => variable_get('ting_subsearch_suggestions_ps_factor', 10),
    '#description' => t('The minimum ratio between suggestion and user search results to trigger suggestion. Use a decimal value for the ratio with "." as decimal separator'),
    '#element_validate' => ['ting_subsearch_factor_field_validate'],
  ];
  $form['trigger']['ting_subsearch_suggestions_message_limit'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum number of results for suggestion search'),
    '#default_value' => variable_get('ting_subsearch_suggestions_message_limit', 10),
    '#description' => t("If the suggestion subsearch returned less results than this don't bother showing a suggestion."),
    '#element_validate' => ['element_validate_integer_positive'],
  ];
  // Insert notice about the zero-hit special case for this module.
  $form['zero_hit_notice'] = [
    '#type' => 'item',
    '#title' => t('NOTICE: Special case if user search returned 0 results.'),
    '#description' => t('If the user search returned 0 results, an attempt to find a suggestion within acceptable Levenshtein distance will always be performed. If the suggestion has a non-empty search result a redirect to that subsearch will be performed. This is done regardless of the trigger conditions.'),
  ];

  return system_settings_form($form);
}
