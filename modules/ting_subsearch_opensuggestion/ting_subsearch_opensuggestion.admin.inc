<?php

/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_opensuggestion_form_ting_admin_ting_settings_alter(&$form, &$form_state) {
  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting subsearch settings');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['os_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Open Suggestion settings'),
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
  $form['subsearch_settings']['kpi_settings']['ting_subsearch_os_additional_url_params_0_hit'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for redirect link'),
    '#default_value' => variable_get('ting_subsearch_os_additional_url_params_0_hit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  );

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_os_additional_url_params_inlimit'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for link in message'),
    '#default_value' => variable_get('ting_subsearch_os_additional_url_params_inlimit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  );
}
