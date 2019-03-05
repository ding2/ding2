<?php
/**
 * @file
 * Admin page callback file for the ting module.
 */

/**
 * Form builder; Configure ting settings for this site.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function ting_admin_ting_settings($form_state) {
  // This form is for configuration elements which work across all Ting (search)
  // providers.
  // This form element is primarily a stopgap in case users get confused about
  // where the former OpenSearch configuration was located.
  return array(
    array(
      '#type' => 'item',
      '#title' => t('Search configuration'),
      '#description' => t(
        'Search is now handled by a provider. Please <a href="@provider-page">check the settings</a> for your currently active search provider.',
        array(
          '@provider-page' => url('admin/config/ding/provider'),
        )
      ),
    ),
  );
}

/**
 * Form builder; Configure online resource types and their URL labels.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function ting_admin_online_types_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');

  $form = array();

  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from search provider'),
    '#description' => t('Update the list of known types by asking the search provider for all types.'),
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_admin_type_source_update'),
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
    '#options' => drupal_map_assoc($types),
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

    foreach ($types as $term) {
      $form['ting_url_labels']['types'][$term] = array(
        '#type' => 'textfield',
        '#title' => $term,
        '#default_value' => isset($settings[$term]) ? $settings[$term] : '',
        // Fudge the parent so we'll get all the labels in one big array in
        // ting_url_labels.
        '#parents' => array('ting_url_labels', $term),
      );
    }
  }

  return system_settings_form($form);
}

/**
 * Form builder; Configure reservable materials.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function ting_admin_reservable_settings($form_state) {
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
  $form = array();

  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from search provider'),
    '#description' => t('Update the lists of known types and sources by asking the search provider for all types and sorces.'),
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_admin_type_source_update'),
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
    '#options' => drupal_map_assoc($sources),
    '#default_value' => variable_get('ting_reservable_sources', _ting_default_reservable_sources()),
  );

  $form['ting_reservable']['ting_reservable_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Types'),
    '#options' => drupal_map_assoc($types),
    '#default_value' => variable_get('ting_reservable_types', _ting_default_reservable_types()),
  );
  // Save us the trouble of running array_filter.
  $form['array_filter'] = array('#type' => 'value', '#value' => TRUE);

  return system_settings_form($form);
}

/**
 * Form for managing language configuration.
 *
 * This configuration deals with how materials are handled depending on their
 * language.
 */
function ting_admin_language_settings($form_state) {
  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from search provider'),
    '#description' => t('Update the lists of known types.'),
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_admin_type_source_update'),
  );

  $form['language'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default language'),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Note that this relies on a single global default language and not the user
  // language or the like. We cannot expect that the material language and
  // Drupal user language will be in the same format.
  global $language;
  $form['language']['ting_language_default'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_language_default', $language->native),
    '#description' => t('The language expected to be used by most materials. Please use the full textual version of the language name as provided by your search provider.'),
  );

  $form['title_suffix'] = array(
    '#type' => 'fieldset',
    '#title' => t('Title suffix'),
    '#tree' => FALSE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t("Select which material types should have the language appended as suffix."),
  );

  $types = variable_get('ting_well_types', _ting_fetch_well_types());
  $form['title_suffix']['ting_language_type_title_suffix'] = array(
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc($types),
    '#default_value' => variable_get('ting_language_type_title_suffix', []),
  );

  return system_settings_form($form);
}

/**
 * Submit handler.
 *
 * Updates the list of known types and sources from the data well.
 */
function ting_admin_type_source_update($form, &$form_state) {
  _ting_fetch_well_types();
  _ting_fetch_well_sources();
}
