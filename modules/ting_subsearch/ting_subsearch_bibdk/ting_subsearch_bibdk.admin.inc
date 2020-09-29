<?php
/**
 * @file
 * Administration interface for ting subsearch bibliotek.dk.
 */

/**
 * Admin settings form for ting subsearch bibliotek.dk.
 */
function ting_subsearch_bibdk_admin_settings_form($form, &$form_state) {
  $form = [];

  // Info.
  $form['info'] = [
    '#type' => 'item',
    '#title' => t('Ting subsearch bibliotek.dk'),
    '#description' => t('Trigger bibliotek.dk subsearches and show suggestions and links to bibliotek.dk.'),
  ];

  // Trigger settings.
  $form['trigger'] = [
    '#type' => 'fieldset',
    '#title' => t('Trigger'),
  ];
  $form['trigger']['ting_subsearch_bibdk_max'] = [
    '#type' => 'textfield',
    '#title' => t('Maximum number of results for user search'),
    '#default_value' => variable_get('ting_subsearch_bibdk_max', 100),
    '#description' => t("If the user search returned more results than this don't bother performing bibliotek.dk search."),
    '#element_validate' => ['element_validate_integer_positive'],
  ];
  $form['trigger']['ting_subsearch_bibdk_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum ratio between nonfiction and fiction'),
    '#default_value' => variable_get('ting_subsearch_bibdk_factor', 2),
    '#description' => t('The minimum ratio of nonfiction to fiction in user search result to trigger bibliotek.dk search. Use a decimal value for the ratio with "." as decimal separator'),
    '#element_validate' => ['ting_subsearch_factor_field_validate'],
  ];
  $form['trigger']['ting_subsearch_bibdk_result_min'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum number of results for bibliotek.dk search'),
    '#description' => t("If the bibliotek.dk subsearch returned less results than this don't bother showing any suggestions and links to bibliotek.dk."),
    '#default_value' => variable_get('ting_subsearch_bibdk_result_min', 100),
    '#element_validate' => ['element_validate_integer_positive'],
  ];
  $form['trigger']['ting_subsearch_bibdk_ps_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Minimum ratio between bibliotek.dk and user search results'),
    '#default_value' => variable_get('ting_subsearch_bibdk_ps_factor', 2),
    '#description' => t('The minimum ratio of between bibliotek.dk and user search results to trigger suggestion. Use a decimal value for the ratio with "." as decimal separator'),
    '#element_validate' => ['ting_subsearch_factor_field_validate'],
  ];

  // Other settingg.
  $form['ting_subsearch_bibdk_number_of_results'] = [
    '#type' => 'textfield',
    '#title' => t('Number of results to show'),
    '#default_value' => variable_get('ting_subsearch_bibdk_number_of_results', 4),
    '#description' => t('How many results from the bibliotek.dk subsearch should be shown to the user.'),
  ];
  $form['ting_subsearch_bibdk_position'] = [
    '#type' => 'radios',
    '#title' => t('Position of message'),
    '#options' => [
      'before' => t('Before'),
      'after' => t('After'),
    ],
    '#default_value' => variable_get('ting_subsearch_bibdk_position', 'before'),
    '#description' => t('Should the bibliotek.dk suggestions and links be positioned before or after the search result?'),
  ];

  return system_settings_form($form);
}
