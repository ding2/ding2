<?php
/**
 * @file
 * Implements administration interface that allows setting of cache duration and
 * maximum number of recommendation to fetch per ting object.
 */

/**
 * Implements the administration interface for ADHL module.
 */
function ding_adhl_frontend_settings_form($form, $form_state) {
  $form = array();

  $form['ding_adhl_frontend_cache_duration'] = array(
    '#type' => 'select',
    '#title' => t('Cache duration'),
    '#description' => t('Determines how long recommendations will be cached for (default 7 days).'),
    '#options' => array(
      3600 => t('1 hour'),
      10800 => t('3 hours'),
      43200 => t('12 hours'),
      86400 => t('1 day'),
      259200 => t('3 days'),
      604800 => t('7 days'),
      1209600 => t('2 weeks'),
      2592000 => t('1 month'),
    ),
    '#default_value' => variable_get('ding_adhl_frontend_cache_duration', 604800),
  );

  $form['ding_adhl_frontend_number_to_fetch'] = array(
    '#type' => 'textfield',
    '#title' => 'Number of recommendations',
    '#description' => t('The maximum number of elements that we should try to fetch for a given ting object (default 24).'),
    '#size' => 2,
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => variable_get('ding_adhl_frontend_number_to_fetch', 24),
  );

  $form['ding_adhl_frontend_number_to_display'] = array(
    '#type' => 'textfield',
    '#title' => 'Number of recommendations to display',
    '#description' => t('The maximum number of elements to display that are found belonging to own library (default 10).'),
    '#size' => 2,
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => variable_get('ding_adhl_frontend_number_to_display', 10),
  );

  $service_link = l(t('ting service settings'), 'admin/config/ting/settings');
  $form['information'] = array(
    '#markup' => t('If you are looking for the service configuration see !link, which currently points to %service', array(
      '!link' => $service_link,
      '%service' => variable_get('ting_recommendation_url', ''),
    )),
  );

  return system_settings_form($form);
}
