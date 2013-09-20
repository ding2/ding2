<?php
/**
 * @file
 * The administration interface to select the data well types that should have
 * holdings information. 
 */

/**
 * Administration for to select which data well types that should have holdings
 * information displayed.
 */
function ding_availability_admin_holdings_settings($form_state) {
  $form = array();

  // Add button to update the types from the data well. Which requires us to
  // load the administration file for the ting module to get the information.
  form_load_include($form_state, 'inc', 'ting', 'ting.admin');
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

  // Get available types.
  $types = variable_get('ting_well_types', array());

  $form['ding_availability_holdings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Holdings information'),
    '#tree' => FALSE,
    '#description' => t("Which ting object types should display provider holdings information in the holding field e.g. on the ting object view"),
  );

  $form['ding_availability_holdings']['ding_availability_holdings_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Types'),
    '#options' => drupal_map_assoc(array_keys($types)),
    '#default_value' => variable_get('ding_availability_holdings_types', _ding_availability_holdings_default_types()),
  );
  // Save us the trouble of running array_filter.
  $form['array_filter'] = array('#type' => 'value', '#value' => TRUE);

  return system_settings_form($form);
}
