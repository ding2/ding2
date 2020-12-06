<?php

/**
 * @file
 * Administration interface for ting subsearch translate.
 */

/**
 * Admin settings form for ting subsearch translate.
 */
function ting_subsearch_translate_admin_settings_form($form, &$form_state) {
  $form = [];

  // Info.
  $form['info'] = [
    '#type' => 'item',
    '#title' => t('Ting subsearch translate'),
    '#description' => t('Trigger subsearches with translated user searches and show suggestion.'),
  ];

  // Trigger settings.
  $form['trigger'] = [
    '#type' => 'fieldset',
    '#title' => t('Trigger'),
  ];
  $form['trigger']['ting_subsearch_translate_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum ratio between nonfiction and fiction'),
    '#description' => t('The minimum ratio of nonfiction to fiction in user search result to trigger translation. Use a decimal value for the ratio with "." as decimal separator'),
    '#default_value' => variable_get('ting_subsearch_translate_factor', 50),
    '#element_validate' => ['ting_subsearch_factor_field_validate'],
  ];
  $form['trigger']['ting_subsearch_translate_ps_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum ratio between suggestion and user search results'),
    '#description' => t('The minimum ratio between suggestion and user search results to trigger suggestion. Use a decimal value for the ratio with "." as decimal separator'),
    '#default_value' => variable_get('ting_subsearch_translate_ps_factor', 10),
    '#element_validate' => ['ting_subsearch_factor_field_validate'],
  ];

  // Other settings.
  $form['ting_subsearch_translate_url'] = [
    '#type' => 'textfield',
    '#title' => t('Google translation service url'),
    '#description' => t('Google Translation API endpoint. <strong>Example:</strong> https://www.googleapis.com/language/translate/v2'),
    '#default_value' => variable_get('ting_subsearch_translate_url', 'https://www.googleapis.com/language/translate/v2'),
  ];
  $form['ting_subsearch_translate_google_key'] = [
    '#type' => 'textfield',
    '#title' => t('Google Cloud Translation API key'),
    '#description' => t('You need to have an API key configured with billing for this to work. take a look at <a href="https://cloud.google.com/translate/pricing">Pricing</a>'),
    '#default_value' => variable_get('ting_subsearch_translate_google_key', ''),
  ];

  return system_settings_form($form);
}
