<?php

/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_suggestions_form_ting_admin_ting_settings_alter(&$form, &$form_state) {
  // KPI.
  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting Subsearch');
  $form['subsearch_settings']['#description'] = t('Feature modules allow additional searches to be made based on predefined conditions.');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['ting_subsearch_suggestions_service'] = array(
    '#type' => 'radios',
    '#title' => t('Choose suggestion service'),
    '#options' => array(
      'os' => 'Opensuggestion',
      'kpi' => 'KPI-Webtrekk',
    ),
    '#weight' => 0,
    '#default_value' => variable_get('ting_subsearch_suggestions_service', ''),
  );

  $form['subsearch_settings']['kpi_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('KPI settings'),
    '#states' => array(
      'visible' => array(
        'input[name=ting_subsearch_suggestions_service]' => array('value' => 'kpi'),
      ),
    ),
    '#weight' => 1,
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_webservice_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('KPI Webtrekk On-Site Searches Web Service URL'),
    '#default_value' => variable_get('ting_subsearch_kpi_webservice_endpoint', ''),
    '#description' => t('This field must contain the "Web Services" URL to the "On-Site Searches" report that can be found in Webtrekk Analytics in the Content category. Click the Share button on the report page to find this URL.'),
  );

  $week_numbers = range(1, 52);
  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_week_nrs'] = array(
    '#type' => 'select',
    '#title' => t('Weeks count'),
    '#description' => t('Indicates how many weeks from local storage to use in suggestion process.'),
    '#options' => $week_numbers,
    '#default_value' => variable_get('ting_subsearch_kpi_week_nrs', 0),
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_distance'] = array(
    '#type' => 'textfield',
    '#title' => t('Levenshtein distance'),
    '#default_value' => variable_get('ting_subsearch_kpi_distance', 3),

    '#description' => t('Enter the maximum Levenshtein Distance here, ie. the maximum number of characters to replace, insert or delete to transform the input string into a string from the KPI data. A higher numbere allows for less similar words to be suggested.'),
  );
  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_minimum_searches'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum search import limit'),
    '#default_value' => variable_get('ting_subsearch_kpi_minimum_searches', 1),
    '#description' => t('The KPI Webtrekk data has search keywords for all searches, including searches with very low frequence (eg. searched only 1 time). Enter the number of minimum searches required before a keyword is imported and used in the KPI subsearch.'),
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_trigger_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of hits to trigger KPI subsearch'),
    '#default_value' => variable_get('ting_subsearch_kpi_trigger_limit', 5),
    '#description' => t('In order to trigger a subsearch which will provide a suggestion to the user, the user-provided search string must trigger at most this number of hits. NOTE: User-provided searches that trigger 0 hits always trigger a subsearch.'),
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_message_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of subsearch hits to display message'),
    '#default_value' => variable_get('ting_subsearch_kpi_message_limit', 10),
    '#description' => t('Minimum number of hits on secondary search to display suggested search message. Given that the trigger above is hit.'),
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_additional_url_params_0_hit'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for redirect link'),
    '#default_value' => variable_get('ting_subsearch_kpi_additional_url_params_0_hit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_additional_url_params_inlimit'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for link in message'),
    '#default_value' => variable_get('ting_subsearch_kpi_additional_url_params_inlimit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  );

  // Opensuggestions.
  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting subsearch settings');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['os_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Open Suggestion settings'),
    '#states' => array(
      'visible' => array(
        'input[name=ting_subsearch_suggestions_service]' => array('value' => 'os'),
      ),
    ),
    '#weight' => 2,
  );

  $form['subsearch_settings']['os_settings']['ting_subsearch_os_trigger_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of hits to trigger Open Suggestion subsearch'),
    '#default_value' => variable_get('ting_subsearch_os_trigger_limit', 5),
    '#description' => t('In order to trigger a subsearch which will provide a suggestion to the user, the user-provided search string must trigger at most this number of hits. NOTE: User-provided searches that trigger 0 hits always trigger a subsearch.'),
  );

  $form['subsearch_settings']['os_settings']['ting_subsearch_os_message_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of subsearch hits to display message'),
    '#default_value' => variable_get('ting_subsearch_os_message_limit', 10),
    '#description' => t('Minimum number of hits on secondary search to display suggested search message. Given that the trigger above is hit.'),
  );
  $form['subsearch_settings']['os_settings']['ting_subsearch_os_additional_url_params_0_hit'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for redirect link'),
    '#default_value' => variable_get('ting_subsearch_os_additional_url_params_0_hit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  );

  $form['subsearch_settings']['os_settings']['ting_subsearch_os_additional_url_params_inlimit'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for link in message'),
    '#default_value' => variable_get('ting_subsearch_os_additional_url_params_inlimit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  );

  // Reordering fieldsets.
  $form['subsearch_settings']['secondary_settings']['#weight'] = 3;
  $form['subsearch_settings']['subsearch_translate']['#weight'] = 4;
}
