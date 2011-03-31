<?php

/**
 * Ting recommendation panel admin form.
 */
function ting_recommendation_panes_settings_form($form_state) {
  $form = array();

  $form['ting_recommendation_panes_cache_duration'] = array(
    '#type' => 'select',
    '#title' => t('Cache duration'),
    '#description' => t('Determines how long recommendations will be cached for.'),
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
    '#default_value' => variable_get('ting_recommendation_panes_cache_duration', 604800),
  );
  
  return system_settings_form($form);    
}
