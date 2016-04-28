<?php

/**
 * @file
 * Ding interaction pane
 */

/**
 * Form builder; Configure online resource types and their URL labels.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function ding_interests_admin_form($form, $form_state) {
  module_load_include('inc', 'ting', 'ting.admin');

  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update from datawell'),
    '#description' => t('Update the list of known types by asking the datawell for all types.'),
  );

  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('ting_admin_reservable_settings_update'),
  );

  $types = variable_get('ting_well_types', array());
  $subjects = variable_get('ting_well_subject', array());
  $genres = variable_get('ting_well_genre', array());

  $form['ting_reservable'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reservation buttons'),
    '#tree' => FALSE,
    '#description' => t("A Ting object will get a reservation button, if it's source and type is <em>both</em> selected."),
  );

  $form['ting_reservable']['ting_reservable_sources'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Sources'),
    '#options' => drupal_map_assoc(array_keys($subjects)),
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
