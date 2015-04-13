<?php

/**
 * @file
 * Admin settings for bibliotek.dk autocomplete.
 */

function ting_search_autocomplete_admin() {

  $base_settings['index'] = NULL;
  $base_settings['facetIndex'] = NULL;
  $base_settings['filterQuery'] = NULL;
  $base_settings['sort'] = 'count';

  $base_settings['agency']  = variable_get('ting_agency', NULL);
  $base_settings['profile'] = variable_get('ting_search_profile', NULL);
  $base_settings['maxSuggestions'] = 10;
  $base_settings['maxTime'] = 2000;

  $base_settings['highlight'] = NULL;
  $base_settings['highlightPre'] = NULL;
  $base_settings['highlightPost'] = NULL;
  $base_settings['minimumString'] = 3;

  $defaults = variable_get('ting_search_autocomplete_settings', array());

  foreach ($base_settings as $key => $base_setting) {
    $default_settings[$key] = (!empty($defaults[$key])) ? $defaults[$key] : $base_setting;
  }

  // Attach the CSS to the form
  $path = drupal_get_path('module', 'ting_search_autocomplete');
  $form['#attached'] = array(
    'css' => array(
      'type' => 'file',
      'data' => $path . '/css/ting_autocomplete_admin_form.css',
    ),
  );

  $form['ting_search_autocomplete_webservice'] = array(
    '#type' => 'fieldset',
    '#title' => t('Autocomplete URL', array(), array('context' => 'ting_search_autocomplete')),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
  ); 

  $form['ting_search_autocomplete_webservice']['ting_suggestion_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Autocomplete URL', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 73,
    '#description' => t('URL to Autocomplete webservice. F.ex.: http://opensuggestion.addi.dk/1.0/', array(), array('context' => 'ting_search_autocomplete')),
    '#default_value' => variable_get('ting_suggestion_url', NULL),
    '#required' => TRUE,
  );

  $form['ting_search_autocomplete_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Autocomplete settings', array(), array('context' => 'ting_search_autocomplete')),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
  );

  $form['ting_search_autocomplete_settings']['index'] = array(
    '#type' => 'textfield',
    '#title' => t('Match index', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 25,
    '#default_value' => $default_settings['index'],
    '#required' => TRUE,
  );

  $form['ting_search_autocomplete_settings']['facetIndex'] = array(
    '#type' => 'textfield',
    '#title' => t('Facet Index', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 25,
    '#default_value' => $default_settings['facetIndex'],
  );

  $form['ting_search_autocomplete_settings']['filterQuery'] = array(
    '#type' => 'textfield',
    '#title' => t('Filter Query', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 25,
    '#default_value' => $default_settings['filterQuery'],
  );

  $form['ting_search_autocomplete_settings']['sort'] = array(
    '#type' => 'radios',
    '#title' => t('Output sort order', array(), array('context' => 'ting_search_autocomplete')),
    '#options' => array('count' => 'count', 'index' => 'index',),
    '#default_value' => $default_settings['sort'],
  );

  $form['ting_search_autocomplete_settings']['agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Agency', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['agency'],
  );

  $form['ting_search_autocomplete_settings']['profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['profile'],
  );
  $form['ting_search_autocomplete_settings']['maxSuggestions'] = array(
    '#type' => 'textfield',
    '#title' => t('Max suggestions', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['maxSuggestions'],
  );

  $form['ting_search_autocomplete_settings']['maxTime'] = array(
    '#type' => 'textfield',
    '#title' => t('Max request time', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['maxTime'],
  );

  $form['ting_search_autocomplete_settings']['highlight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Highlight', array(), array('context' => 'ting_search_autocomplete')),
    '#description' => t('If checked, search prefix will be enclosed in highlight prefix and suffix', array(), array('context' => 'ting_search_autocomplete')),
    '#default_value' => $default_settings['highlight'],
  );

  $form['ting_search_autocomplete_settings']['highlightPre'] = array(
    '#type' => 'textfield',
    '#title' => t('Highlight prefix', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 20,
    '#default_value' => $default_settings['highlightPre'],
  );

  $form['ting_search_autocomplete_settings']['highlightPost'] = array(
    '#type' => 'textfield',
    '#title' => t('Highlight suffix', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 18,
    '#default_value' => $default_settings['highlightPost'],
  );

  $form['ting_search_autocomplete_settings']['minimumString'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum string', array(), array('context' => 'ting_search_autocomplete')),
    '#description' => t('Minimum string length to do autocomplete lookup on.', array(), array('context' => 'ting_search_autocomplete')),
    '#size' => 18,
    '#default_value' => $default_settings['minimumString'],
  );

  $form['ting_search_autocomplete_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Autocomplete help', array(), array('context' => 'ting_search_autocomplete')),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ting_search_autocomplete_help']['description'] = array(
    '#theme' => 'table',
    '#rows' => array(
      array(t('Match index:', array(), array('context' => 'ting_search_autocomplete')),
            t('The index to find word matches in.<br/>
               If a term index, single terms are returned, while phrase indexes return entire phrases. Only entries in the specified index that begin with the specified query string are returned. For term indexes the query string can only contain one term<br/>
               F.ex.: scanterm.mainTitle + query: "kan" will match "<b>Kan</b>dis", or scanphrase.mainTitle + query: "kan" will match "<b>Kan</b>sas city"', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Facet index:', array(), array('context' => 'ting_search_autocomplete')),
            t('The index to get suggestions from.<br/>
               This variant looks in the specified index for entries that contain the words from specified query string and then counts results in groups based on the specified facet index. This will also provide suggestions for phrases that contain the words from the query string.<br/>
               Care should be taken in selecting a suitable pair of indexes. The facet index should be an index generated from the same data as the match index. The match index should be a term index and the facet index should be a phrase index<br/>
               F.ex.: scanphrase.mainTitle (combined with match index: scanterm.mainTitle) + query: "kan" will match "From Impressionism to <b>Kan</b>dinsky"', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Query filter:', array(), array('context' => 'ting_search_autocomplete')),
            t('A query that may be used to filter the area you want to get suggestions from. F.ex.: term.workType=literature', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Output sort order:', array(), array('context' => 'ting_search_autocomplete')), t('Defaults to "count"', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Agency:', array(), array('context' => 'ting_search_autocomplete')),
            t('Only get suggestions from data accessible to the specified library ID. F.ex.: 715100', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Profile:', array(), array('context' => 'ting_search_autocomplete')),
            t('Only get suggestions from data accessible to the specified search profile, as defined in the VIP database.', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Max suggestions:', array(), array('context' => 'ting_search_autocomplete')),
            t('Maximum suggestions to return. Default 10', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Max request time:', array(), array('context' => 'ting_search_autocomplete')),
            t('Maximum request time in milliseconds. Default 2000', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Highlight:', array(), array('context' => 'ting_search_autocomplete')),
            t('Add prefix and suffix around strings that match the query.', array(), array('context' => 'ting_search_autocomplete'))),
      array(t('Highlight prefix & suffix:', array(), array('context' => 'ting_search_autocomplete')), 
            t('Defaults to &lt;em&gt; & &lt;/em&gt;.', array(), array('context' => 'ting_search_autocomplete'))),
    ),
    '#attributes' => array('class' => array('table-class')),
    '#empty' =>t('Your table is empty'),
  );

  $form['#submit'][] = 'ting_search_autocomplete_admin_submit';

  return system_settings_form($form);

}


/**
 * Validation handler for ting_search_autocomplete_admin
 */
function ting_search_autocomplete_admin_validate($form, &$form_state) {

  $form_state['values']['ting_suggestion_url'] = trim($form_state['values']['ting_suggestion_url'], $character_mask = " \t\n\r\0\x0B");

}


/**
 * Submt handler for ting_search_autocomplete_admin
 */
function ting_search_autocomplete_admin_submit($form, &$form_state) {
  //
}
