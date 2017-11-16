<?php

/**
 * @file
 * General admin settings for autocomplete.
 */

function ting_search_autocomplete_admin() {

  $form['ting_search_autocomplete_settings']['maxSuggestions'] = array(
    '#type' => 'textfield',
    '#title' => t('Max suggestions', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['maxSuggestions'],
  );

  $form['ting_search_autocomplete_settings']['minimumString'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum string', array(), array('context' => 'ting_search_autocomplete')),
    '#description' => t('Minimum string length to do autocomplete lookup on.', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['minimumString'],
  );

  $form['ting_search_autocomplete_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Autocomplete help', array(), array('context' => 'ting_search_autocomplete')),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['ting_search_autocomplete_help']['description'] = array(
    '#theme' => 'table',
    '#rows' => array(
      array(t('Max suggestions:', array(), array('context' => 'ting_search_autocomplete')),
            t('Maximum suggestions to return. Default 10', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Minimum string:', array(), array('context' => 'ting_search_autocomplete')),
            t('Minimum characters the user has to type before the suggestionservice is queried.', array(), array('context' => 'ting_search_autocomplete'))),
    ),
    '#attributes' => array('class' => array('table-class')),
    '#empty' => t('Your table is empty'),
  );

  return system_settings_form($form);
}
