<?php
/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_kpi_form_ting_admin_ting_settings_alter(&$form, &$form_state) {
  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting Subsearch');
  $form['subsearch_settings']['#description'] = t('Feature modules allow additional searches to be made based on predefined conditions.');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['kpi_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('KPI settings'),
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_webservice_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('KPI Webtrends On-Site Searches Web Service URL'),
    '#default_value' => variable_get('ting_subsearch_kpi_webservice_endpoint', ''),
    '#description' => t('This field must contain the "Web Services" URL to the "On-Site Searches" report that can be found in Webtrends Analytics in the Content category. Click the Share button on the report page to find this URL.'),
  );
  $params = array(
    'start_period' => 'current_day-365',
    'end_period' => 'current_day-1',
  );
  foreach ($params as $key => $value) {
    $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_' . $key] = array(
      '#type' => 'textfield',
      '#title' => t('Parameter: !key', array('!key' => $key)),
      '#default_value' => variable_get('ting_subsearch_kpi_' . $key, $value),
    );
  }
  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_account'] = array(
    '#type' => 'textfield',
    '#title' => t('Account'),
    '#default_value' => variable_get('ting_subsearch_kpi_account', ''),
    '#description' => t('Account\Username.'),
  );
  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#default_value' => variable_get('ting_subsearch_kpi_password', ''),

    '#description' => t('The password'),
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
    '#description' => t('The KPI Webtrends data has search keywords for all searches, including searches with very low frequence (eg. searched only 1 time). Enter the number of minimum searches required before a keyword is imported and used in the KPI subsearch.'),
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
}
