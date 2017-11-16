<?php

/**
 * @file
 * General admin settings for autocomplete.
 */

function ting_search_autocomplete_admin() {

  $default_settings = ting_search_autocomplete_settings();

  $form['ting_search_autocomplete_settings']['maxSuggestions'] = array(
    '#type' => 'textfield',
    '#title' => t('Max suggestions', array(), array('context' => 'ting_search_autocomplete')),
    '#description' => t('Maximum suggestions to return. Default 10.'),
    '#size' => 26,
    '#default_value' => $default_settings['maxSuggestions'],
  );

  $form['ting_search_autocomplete_settings']['minimumString'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum string', array(), array('context' => 'ting_search_autocomplete')),
    '#description' => t('Minimum characters the user has to type before the suggestion service is queried.', array()
      , array('context' => 'ting_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['minimumString'],
  );

  return system_settings_form($form);
}
