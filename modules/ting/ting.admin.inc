<?php
/**
 * @file
 * Admin page callback file for the ting module.
 */

/**
 * Form builder; Configure ting settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_admin_ting_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  $form = array();

  $form['ting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ting service settings'),
    '#tree' => FALSE,
  );

  $form['ting']['ting_agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Library code'),
    '#description' => t('The 6-digit code representing the library organization'),
    '#default_value' => variable_get('ting_agency', ''),
  );

  $form['ting']['ting_search_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Search service URL'),
    '#description' => t('URL to the Ting search webservice, e.g. http://opensearch.addi.dk/3.0/'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_search_url', ''),
  );

  $form['ting']['ting_filter_by_local_holdings']= array(
    '#type' => 'checkbox',
    '#title' => t('Filter search queries on holdingsItem'),
    '#description' => t('Filter searches by holdingsitem.agencyId. Only activate when opensearch uses data-well 3.5, and the provider is fbs'),
    '#required' => FALSE,
    '#default_value' => variable_get('ting_filter_by_local_holdings', 0),
  );

  $form['ting']['ting_recommendation_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Recommendation service URL'),
    '#description' => t('URL to the Ting recommendation webservice (Andre der har lånt...) , e.g. http://openadhl.addi.dk/1.1/'),
    '#required' => TRUE,
    '#default_value' => variable_get('ting_recommendation_url', ''),
  );

  $form['ting']['ting_enable_logging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => variable_get('ting_enable_logging', FALSE),
    '#weight' => 1,
  );

  $intervals = array(
    60,
    300,
    900,
    1800,
    3600,
    10800,
    43200,
    86400,
    259200,
    604800,
  );

  $options = array();
  foreach ($intervals as $interval) {
    $options[$interval] = format_interval($interval, 2);
  }

  $form['ting']['ting_cache_lifetime'] = array(
    '#type' => 'select',
    '#title' => t('Cache lifetime'),
    '#default_value' => variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME),
    '#options' => $options,
    '#description' => t("Cache answers from the datawell for this time. At least a few minutes is recommended, so the same objects doesn't have to be fetched on each page request."),
    '#weight' => 1,
  );

  $form['ting']['ting_search_profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Search profile'),
    '#description' => t('Profile name, used for filtering the search based on settings from vip.dbc.dk.'),
    '#default_value' => variable_get('ting_search_profile', ''),
  );

  return system_settings_form($form);
}

/**
 * Form builder; Configure custom search result ranking for this site.
 *
 * @ingroup forms
 */
function ting_admin_ranking_settings($form, &$form_state) {
  form_load_include($form_state, 'admin.inc', 'ting');
  $form = array(
    '#after_build' => array('ting_admin_ranking_form_after_build'),
  );

  $form['ting_ranking_custom'] = array(
    '#title' => t('Enable custom ranking'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('ting_ranking_custom', 0),
    '#description' => t('If enabled, the Ting client will use the custom ranking settings provided below when making queries to Ting.'),
  );

  // Get our stored data.
  $field_data = variable_get('ting_ranking_fields', array());

  if (!isset($form_state['ranking_field_count'])) {
    $form_state['ranking_field_count'] = count($field_data) + 1;
  }

  // Wrapper, so that the AJAX callback have some place to put new elements.
  $form['ting_ranking_fields'] = array(
    '#title' => t('Custom ranking fields'),
    '#type' => 'fieldset',
    '#prefix' => '<div id="ranking-fields-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  for ($i = 0; $i < $form_state['ranking_field_count']; $i++) {
    $form['ting_ranking_fields']['fields'][$i] = array(
      '#type' => 'ting_ranking_field',
      '#default_value' => (isset($field_data[$i])) ? $field_data[$i] : array(),
    );
  }

  $form['ting_ranking_fields']['allindexes_notice'] = array(
    '#markup' => t('In addition to the boost values selected above, we will add a boost value of 1 to anyIndexes for both phrase and word matches. This is done to ensure that all matches is included in the result, regardless of how they are ranked.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $form['ting_ranking_fields']['add_field'] = array(
    '#type' => 'submit',
    '#value' => t('Add another ranking field'),
    '#submit' => array('ting_admin_ranking_add_more_submit'),
    '#weight' => 10,
    '#ajax' => array(
      'callback' => 'ting_admin_ranking_add_more_js',
      'wrapper' => 'ranking-fields-wrapper',
      'effect' => 'fade',
    ),
  );


  $ting_sort_value = variable_get('ting_sort_default', 'rank_frequency');
  $form['ting_sort_default'] = array(
    '#title' => t('Default sort method (best match)'),
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['ting_sort_default']['fields']['sort_type'] = array(
    '#title' => t('Type'),
    '#type' => 'select',
    '#options' => array(
      'rank_frequency' => t('Best match'),
      'rank_general' => t('General Rank'),
      'rank_none' => t('No rank'),
    ),
    '#default_value' => array('sort_type' => $ting_sort_value),
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
function ting_admin_ranking_add_more_submit($form, &$form_state) {
  // Simply add another empty set of values to the field array and ask
  // to have the form rebuilt. The form code will take care of the rest.
  $form_state['ranking_field_count'] += 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback in response to a new empty widget being added to the form.
 */
function ting_admin_ranking_add_more_js($form, &$form_state) {
  return $form['ting_ranking_fields'];
}

/**
 * After build callback to the ranking settings form.
 *
 * Add a little bit of CSS and JS to the form.
 */
function ting_admin_ranking_form_after_build($form, &$form_state) {
  $path = drupal_get_path('module', 'ting');
  drupal_add_css($path . '/css/ting_admin_ranking_form.css');

  return $form;
}

/**
 * Submit handler for ranking settings form.
 */
function ting_admin_ranking_settings_submit($form, &$form_state) {
  variable_set('ting_ranking_custom', (integer) $form_state['values']['ting_ranking_custom']);

  $fields = $form_state['values']['ting_ranking_fields']['fields'];

  $fields = array_filter($fields, '_ting_ranking_field_filter');
  usort($fields, '_ting_ranking_field_sort');

  variable_set('ting_ranking_fields', $fields);

  $default_sort = $form_state['values']['ting_sort_default']['fields']['sort_type'];
  variable_set('ting_sort_default', $default_sort);

  drupal_set_message(t('Settings has been saved'), 'status');
}

/**
 * Array_filter() callback to remove empty/deleted elements.
 */
function _ting_ranking_field_filter($element) {
  return !empty($element['field_name']);
}

/**
 * Usort() callback to remove empty/deleted elements.
 */
function _ting_ranking_field_sort($a, $b) {
  if ($a['weight'] == $b['weight']) {
    return 0;
  }
  return ($a['weight'] > $b['weight']) ? -1 : 1;
}

/**
 * Form builder; Configure custom search result ranking for this site.
 *
 * @ingroup forms
 */
function ting_admin_boost_settings($form, &$form_state) {
  form_load_include($form_state, 'admin.inc', 'ting');
  $form = array('#after_build' => array('ting_admin_boost_form_after_build'));

  // Get our stored data.
  $field_data = variable_get('ting_boost_fields', array());

  if (!isset($form_state['boost_field_count'])) {
    $form_state['boost_field_count'] = count($field_data);
  }

  // Wrapper, so that the AJAX callback have some place to put new elements.
  $form['ting_boost_fields'] = array(
    '#title' => t('Custom fields boost values'),
    '#type' => 'fieldset',
    '#prefix' => '<div id="boost-fields-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  foreach (range(0, $form_state['boost_field_count']) as $i) {
    $form['ting_boost_fields']['fields'][$i] = array(
      '#type' => 'ting_boost_field',
      '#default_value' => (isset($field_data[$i])) ? $field_data[$i] : array(),
    );
  }

  $form['ting_boost_fields']['add_value'] = array(
    '#type' => 'submit',
    '#value' => t('Add another boost value'),
    '#submit' => array('ting_admin_boost_add_more_submit'),
    '#weight' => 10,
    '#ajax' => array(
      'callback' => 'ting_admin_boost_add_more_js',
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
function ting_admin_boost_add_more_submit($form, &$form_state) {
  // Simply add another empty set of values to the field array and ask
  // to have the form rebuilt. The form code will take care of the rest.
  $form_state['boost_field_count'] += 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback in response to a new empty widget being added to the form.
 */
function ting_admin_boost_add_more_js($form, &$form_state) {
  return $form['ting_boost_fields'];
}

/**
 * After build callback to the boost settings form.
 *
 * Add a little bit of CSS and JS to the form.
 */
function ting_admin_boost_form_after_build($form, &$form_state) {
  $path = drupal_get_path('module', 'ting');

  drupal_add_css($path . '/css/ting_admin_boost_form.css');

  return $form;
}

/**
 * Submit handler for boost settings form.
 */
function ting_admin_boost_settings_submit($form, &$form_state) {
  $fields = $form_state['values']['ting_boost_fields']['fields'];

  $fields = array_filter($fields, '_ting_boost_field_filter');
  usort($fields, '_ting_boost_field_sort');

  variable_set('ting_boost_fields', $fields);
}

/**
 * Array_filter() callback to remove empty/deleted elements.
 */
function _ting_boost_field_filter($element) {
  return !(empty($element['field_name']) || empty($element['field_value']));
}

/**
 * Callback for usort() to remove empty/deleted elements.
 */
function _ting_boost_field_sort($a, $b) {
  if ($a['weight'] == $b['weight']) {
    return 0;
  }
  return ($a['weight'] > $b['weight']) ? -1 : 1;
}

/**
 * Form builder; Configure online resource types and their URL labels.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_admin_online_types_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  form_load_include($form_state, 'inc', 'ting', 'ting.client');
  $form = array();

  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from datawell'),
    '#description' => t('Update the list of known types by asking the datawell for all types.'),
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_admin_online_types_settings_update_types'),
  );

  $types = variable_get('ting_well_types', _ting_fetch_well_types());

  $form['ting_online'] = array(
    '#type' => 'fieldset',
    '#title' => t('Online types'),
    '#description' => t('Ting objects defined as found online (not in the library collection).'),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ting_online']['ting_online_types'] = array(
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc(array_keys($types)),
    '#default_value' => variable_get('ting_online_types', _ting_default_online_types()),
  );

  $settings = variable_get('ting_url_labels', _ting_default_url_labels());
  $form['ting_url_labels'] = array(
    '#type' => 'fieldset',
    '#title' => t('Labels'),
    '#tree' => TRUE,
  );

  $form['ting_url_labels']['_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Default label'),
    '#default_value' => isset($settings['_default']) ? $settings['_default'] : '',
    '#description' => t('Default label used for types that is not specifically set below.'),
  );

  if (count($types)) {
    $form['ting_url_labels']['types'] = array(
      '#type' => 'fieldset',
      '#title' => t('Type specific labels'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t("Here you may override the default label for individual material types."),
    );

    foreach ($types as $term => $count) {
      $form['ting_url_labels']['types'][$term] = array(
        '#type' => 'textfield',
        '#title' => $term,
        '#default_value' => isset($settings[$term]) ? $settings[$term] : '',
        '#description' => t('Count: @count', array('@count' => $count)),
        // Fudge the parent so we'll get all the labels in one big array in
        // ting_url_labels.
        '#parents' => array('ting_url_labels', $term),
      );
    }
  }

  return system_settings_form($form);
}

/**
 * Submit handler. Updates the list of known types from the data well.
 */
function ting_admin_online_types_settings_update_types($form, &$form_state) {
  _ting_fetch_well_types();
}

/**
 * Form builder; Configure reservable materials.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_admin_reservable_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  $form = array();

  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from datawell'),
    '#description' => t('Update the lists of known types and sources by asking the datawell for all types and sorces.'),
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_admin_reservable_settings_update'),
  );

  $form['reservation_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reservation settings'),
    '#tree' => FALSE,
  );

  $options = array();
  $intervals = array(
    86400,
    172800,
    259200,
    345600,
    432000,
    518400,
    604800,
    1209600,
    1814400,
  );
  foreach ($intervals as $interval) {
    $options[$interval] = format_interval($interval, 2);
  }

  $form['reservation_settings']['reservation_expire'] = array(
    '#type' => 'select',
    '#title' => t('Reservation expire message'),
    '#options' => $options,
    '#default_value' => variable_get('reservation_expire', 604800),
    '#description' => t('Time before an reservation expires that a message should be shown to the user.'),
  );

  $types = variable_get('ting_well_types', _ting_fetch_well_types());
  $sources = variable_get('ting_well_sources', _ting_fetch_well_sources());

  $form['ting_reservable'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reservation buttons'),
    '#tree' => FALSE,
    '#description' => t("A Ting object will get a reservation button, if it's source and type is <em>both</em> selected."),
  );

  $form['ting_reservable']['ting_reservable_sources'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Sources'),
    '#options' => drupal_map_assoc(array_keys($sources)),
    '#default_value' => variable_get('ting_reservable_sources', _ting_default_reservable_sources()),
  );

  $form['ting_reservable']['ting_reservable_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Types'),
    '#options' => drupal_map_assoc(array_keys($types)),
    '#default_value' => variable_get('ting_reservable_types', _ting_default_reservable_types()),
  );
  // Save us the trouble of running array_filter.
  $form['array_filter'] = array('#type' => 'value', '#value' => TRUE);

  return system_settings_form($form);
}

/**
 * Submit handler. Updates the list of known types and sources from the
 * data well.
 */
function ting_admin_reservable_settings_update($form, &$form_state) {
  _ting_fetch_well_types();
  _ting_fetch_well_sources();
}
