<?php
/**
 * @file
 * Admin page callback file for the opensearch module.
 */

/**
 * Autocomplete settings.
 */
function opensearch_search_autocomplete_admin($form, &$form_state) {
  $default_settings = opensearch_search_autocomplete_settings();

  // Attach the CSS to the form.
  $path = drupal_get_path('module', 'opensearch');
  $form['#attached'] = array(
    'css' => array(
      'type' => 'file',
      'data' => $path . '/css/opensearch_autocomplete_admin_form.css',
    ),
  );

  $form['opensearch_search_autocomplete_webservice'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webservice', array(), array('context' => 'opensearch_search_autocomplete')),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['opensearch_search_autocomplete_webservice']['opensearch_search_autocomplete_suggestion_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 73,
    '#description' => t('URL to Autocomplete webservice. F.ex.: http://opensuggestion.addi.dk/1.0/', array(), array('context' => 'opensearch_search_autocomplete')),
    '#default_value' => variable_get('opensearch_search_autocomplete_suggestion_url',
      NULL),
    '#required' => TRUE,
    '#element_validate' => array('opensearch_search_autocomplete_admin_validate'),
  );

  $form['opensearch_search_autocomplete_webservice']['opensearch_search_autocomplete_method'] = array(
    '#type' => 'textfield',
    '#title' => t('Method', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 73,
    '#description' => t('The method to use. Currently there are two methods: terms and facets. Version 2.0 exposes facetSpell method', array(), array('context' => 'opensearch_search_autocomplete')),
    '#default_value' => variable_get('opensearch_search_autocomplete_method',
      'facets'),
    '#required' => TRUE,
  );

  $form['opensearch_search_autocomplete_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings', array(), array('context' => 'opensearch_search_autocomplete')),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['opensearch_search_autocomplete_settings']['index'] = array(
    '#type' => 'textfield',
    '#title' => t('Match index', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 25,
    '#default_value' => $default_settings['index'],
    '#required' => TRUE,
  );

  $form['opensearch_search_autocomplete_settings']['facetIndex'] = array(
    '#type' => 'textfield',
    '#title' => t('Facet Index', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 25,
    '#default_value' => $default_settings['facetIndex'],
    '#required' => TRUE,
  );

  $form['opensearch_search_autocomplete_settings']['filterQuery'] = array(
    '#type' => 'textfield',
    '#title' => t('Filter Query', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 25,
    '#default_value' => $default_settings['filterQuery'],
  );

  $form['opensearch_search_autocomplete_settings']['sort'] = array(
    '#type' => 'radios',
    '#title' => t('Output sort order', array(), array('context' => 'opensearch_search_autocomplete')),
    '#options' => array('count' => 'count', 'index' => 'index'),
    '#default_value' => $default_settings['sort'],
  );

  $form['opensearch_search_autocomplete_settings']['agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Agency', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['agency'],
  );

  $form['opensearch_search_autocomplete_settings']['profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['profile'],
  );

  $form['opensearch_search_autocomplete_settings']['maxSuggestions'] = array(
    '#type' => 'textfield',
    '#title' => t('Max suggestions', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['maxSuggestions'],
  );

  $form['opensearch_search_autocomplete_settings']['maxTime'] = array(
    '#type' => 'textfield',
    '#title' => t('Max request time', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['maxTime'],
  );

  $form['opensearch_search_autocomplete_settings']['highlight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Highlight', array(), array('context' => 'opensearch_search_autocomplete')),
    '#description' => t('If checked, search prefix will be enclosed in highlight prefix and suffix', array(), array('context' => 'opensearch_search_autocomplete')),
    '#default_value' => $default_settings['highlight'],
    '#return_value' => 'true',
  );

  $form['opensearch_search_autocomplete_settings']['highlight.pre'] = array(
    '#type' => 'textfield',
    '#title' => t('Highlight prefix', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['highlight.pre'],
  );

  $form['opensearch_search_autocomplete_settings']['highlight.post'] = array(
    '#type' => 'textfield',
    '#title' => t('Highlight suffix', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['highlight.post'],
  );

  $form['opensearch_search_autocomplete_settings']['minimumString'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum string', array(), array('context' => 'opensearch_search_autocomplete')),
    '#description' => t('Minimum characters the user has to type before the suggestion service is queried.', array(), array('context' => 'opensearch_search_autocomplete')),
    '#size' => 26,
    '#default_value' => $default_settings['minimumString'],
  );

  $form['opensearch_search_autocomplete_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Help', array(), array('context' => 'opensearch_search_autocomplete')),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['opensearch_search_autocomplete_help']['description'] = array(
    '#theme' => 'table',
    '#rows' => array(
      array(
        t('Match index:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('The index to find word matches in.<br/>
               If a term index, single terms are returned, while phrase indexes return entire phrases. Only entries in the specified index that begin with the specified query string are returned. For term indexes the query string can only contain one term<br/>
               F.ex.: scanterm.mainTitle + query: "kan" will match "<b>Kan</b>dis", or scanphrase.mainTitle + query: "kan" will match "<b>Kan</b>sas city"', array(), array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Facet index:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('The index to get suggestions from.<br/>
               This variant looks in the specified index for entries that contain the words from specified query string and then counts results in groups based on the specified facet index. This will also provide suggestions for phrases that contain the words from the query string.<br/>
               Care should be taken in selecting a suitable pair of indexes. The facet index should be an index generated from the same data as the match index. The match index should be a term index and the facet index should be a phrase index<br/>
               F.ex.: scanphrase.mainTitle (combined with match index: scanterm.mainTitle) + query: "kan" will match "From Impressionism to <b>Kan</b>dinsky"', array(), array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Query filter:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('A query that may be used to filter the area you want to get suggestions from. F.ex.: term.workType=literature', array(), array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Output sort order:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('Defaults to "count"', array(), array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Agency:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('Only get suggestions from data accessible to the specified library ID. F.ex.: 715100', array(), array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Profile:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('Only get suggestions from data accessible to the specified search profile, as defined in the VIP database.', array(), array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Max request time:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('Maximum request time in milliseconds. Default 2000', array(),
          array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Highlight:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('Add prefix and suffix around strings that match the query.', array(), array('context' => 'opensearch_search_autocomplete')),
      ),
      array(
        t('Highlight prefix & suffix:', array(), array('context' => 'opensearch_search_autocomplete')),
        t('Defaults to &lt;em&gt; & &lt;/em&gt;.', array(), array(
          'context' => 'opensearch_search_autocomplete',
        )),
      ),
    ),
    '#attributes' => array('class' => array('table-class')),
    '#empty' => t('Your table is empty'),
  );

  return system_settings_form($form);
}

/**
 * Form builder; Configure custom search result ranking for this site.
 *
 * @ingroup forms
 */
function opensearch_admin_ranking_settings($form, &$form_state) {
  form_load_include($form_state, 'admin.inc', 'opensearch');
  $form = array(
    '#after_build' => array('opensearch_admin_ranking_form_after_build'),
  );

  $form['opensearch_ranking_custom'] = array(
    '#title' => t('Enable custom ranking'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('opensearch_ranking_custom', 0),
    '#description' => t('If enabled, the Opensearch client will use the custom ranking settings provided below when making queries to Opensearch.'),
  );

  // Get our stored data.
  $field_data = variable_get('opensearch_ranking_fields', array());

  if (!isset($form_state['ranking_field_count'])) {
    $form_state['ranking_field_count'] = count($field_data) + 1;
  }

  // Wrapper, so that the AJAX callback have some place to put new elements.
  $form['opensearch_ranking_fields'] = array(
    '#title' => t('Custom ranking fields'),
    '#type' => 'fieldset',
    '#prefix' => '<div id="ranking-fields-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  for ($i = 0; $i < $form_state['ranking_field_count']; $i++) {
    $form['opensearch_ranking_fields']['fields'][$i] = array(
      '#type' => 'opensearch_ranking_field',
      '#default_value' => (isset($field_data[$i])) ? $field_data[$i] : array(),
    );
  }

  $form['opensearch_ranking_fields']['allindexes_notice'] = array(
    '#markup' => t('In addition to the boost values selected above, we will add a boost value of 1 to anyIndexes for both phrase and word matches. This is done to ensure that all matches is included in the result, regardless of how they are ranked.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $form['opensearch_ranking_fields']['add_field'] = array(
    '#type' => 'submit',
    '#value' => t('Add another ranking field'),
    '#submit' => array('opensearch_admin_ranking_add_more_submit'),
    '#weight' => 10,
    '#ajax' => array(
      'callback' => 'opensearch_admin_ranking_add_more_js',
      'wrapper' => 'ranking-fields-wrapper',
      'effect' => 'fade',
    ),
  );

  $opensearch_sort_value = variable_get('opensearch_sort_default', 'rank_frequency');
  $form['opensearch_sort_default'] = array(
    '#title' => t('Default sort method (best match)'),
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['opensearch_sort_default']['fields']['sort_type'] = array(
    '#title' => t('Type'),
    '#type' => 'select',
    '#options' => array(
      'rank_frequency' => t('Best match'),
      'rank_general' => t('General Rank'),
      'rank_none' => t('No rank'),
    ),
    '#default_value' => array('sort_type' => $opensearch_sort_value),
  );

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );

  return $form;
}

/**
 * Submit handler for the "Add another item" button of a field form.
 *
 * This handler is run regardless of whether JS is enabled or not. It makes
 * changes to the form state. If the button was clicked with JS disabled, then
 * the page is reloaded with the complete rebuilt form. If the button was
 * clicked with JS enabled, then ajax_form_callback() calls field_add_more_js()
 * to return just the changed part of the form.
 */
function opensearch_admin_ranking_add_more_submit($form, &$form_state) {
  // Simply add another empty set of values to the field array and ask
  // to have the form rebuilt. The form code will take care of the rest.
  $form_state['ranking_field_count'] += 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback in response to a new empty widget being added to the form.
 */
function opensearch_admin_ranking_add_more_js($form, &$form_state) {
  return $form['opensearch_ranking_fields'];
}

/**
 * After build callback to the ranking settings form.
 *
 * Add a little bit of CSS to the form.
 */
function opensearch_admin_ranking_form_after_build($form, &$form_state) {
  $path = drupal_get_path('module', 'opensearch');
  drupal_add_css($path . '/css/opensearch_admin_ranking_form.css');

  return $form;
}

/**
 * Submit handler for ranking settings form.
 */
function opensearch_admin_ranking_settings_submit($form, &$form_state) {
  variable_set('opensearch_ranking_custom', (integer) $form_state['values']['opensearch_ranking_custom']);

  $fields = $form_state['values']['opensearch_ranking_fields']['fields'];

  $fields = array_filter($fields, '_opensearch_ranking_field_filter');
  usort($fields, 'drupal_sort_weight');

  variable_set('opensearch_ranking_fields', $fields);

  $default_sort = $form_state['values']['opensearch_sort_default']['fields']['sort_type'];
  variable_set('opensearch_sort_default', $default_sort);

  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Array_filter() callback to remove empty/deleted elements.
 */
function _opensearch_ranking_field_filter($element) {
  return !empty($element['field_name']);
}

/**
 * Form builder; Configure custom search result ranking for this site.
 *
 * @ingroup forms
 */
function opensearch_admin_boost_settings($form, &$form_state) {
  form_load_include($form_state, 'admin.inc', 'opensearch');
  $form = array('#after_build' => array('opensearch_admin_boost_form_after_build'));

  // Get our stored data.
  $field_data = variable_get('opensearch_boost_fields', array());

  if (!isset($form_state['boost_field_count'])) {
    $form_state['boost_field_count'] = count($field_data);
  }

  // Wrapper, so that the AJAX callback have some place to put new elements.
  $form['opensearch_boost_fields'] = array(
    '#title' => t('Custom fields boost values'),
    '#type' => 'fieldset',
    '#prefix' => '<div id="boost-fields-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  foreach (range(0, $form_state['boost_field_count']) as $i) {
    $form['opensearch_boost_fields']['fields'][$i] = array(
      '#type' => 'opensearch_boost_field',
      '#default_value' => (isset($field_data[$i])) ? $field_data[$i] : array(),
    );
  }

  $form['opensearch_boost_fields']['add_value'] = array(
    '#type' => 'submit',
    '#value' => t('Add another boost value'),
    '#submit' => array('opensearch_admin_boost_add_more_submit'),
    '#weight' => 10,
    '#ajax' => array(
      'callback' => 'opensearch_admin_boost_add_more_js',
      'wrapper' => 'boost-fields-wrapper',
      'effect' => 'fade',
    ),
  );

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );

  return $form;
}

/**
 * Submit handler for the "Add another item" button of a field form.
 *
 * This handler is run regardless of whether JS is enabled or not. It makes
 * changes to the form state. If the button was clicked with JS disabled, then
 * the page is reloaded with the complete rebuilt form. If the button was
 * clicked with JS enabled, then ajax_form_callback() calls field_add_more_js()
 * to return just the changed part of the form.
 */
function opensearch_admin_boost_add_more_submit($form, &$form_state) {
  // Simply add another empty set of values to the field array and ask
  // to have the form rebuilt. The form code will take care of the rest.
  $form_state['boost_field_count'] += 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback in response to a new empty widget being added to the form.
 */
function opensearch_admin_boost_add_more_js($form, &$form_state) {
  return $form['opensearch_boost_fields'];
}

/**
 * After build callback to the boost settings form.
 *
 * Add a little bit of CSS to the form.
 */
function opensearch_admin_boost_form_after_build($form, &$form_state) {
  $path = drupal_get_path('module', 'opensearch');

  drupal_add_css($path . '/css/opensearch_admin_boost_form.css');

  return $form;
}

/**
 * Submit handler for boost settings form.
 */
function opensearch_admin_boost_settings_submit($form, &$form_state) {
  $fields = $form_state['values']['opensearch_boost_fields']['fields'];

  $fields = array_filter($fields, '_opensearch_boost_field_filter');
  usort($fields, 'drupal_sort_weight');

  variable_set('opensearch_boost_fields', $fields);

  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Array_filter() callback to remove empty/deleted elements.
 */
function _opensearch_boost_field_filter($element) {
  return !(empty($element['field_name']) || empty($element['field_value']));
}
