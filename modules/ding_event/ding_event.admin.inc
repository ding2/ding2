<?php
/**
 * @file.
 * add system configuration option to set currency displayed on event(s)
 */

/**
 * Get a form to select currency (Euro | Kr)
 *
 * @param array $form
 *   An associative array containing the structure of the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 * @return mixed
 */
function ding_event_admin_setting_form(array $form, array &$form_state) {
  $currency = variable_get('ding_event_currency_type', 'Kr');
  $form['#submit'][] = 'ding_event_admin_submit';

  $form['ding_event']['ding_event_currency_type'] = array(
    '#type' => 'radios',
    '#title' => t('Currency'),
    '#options' => drupal_map_assoc(array('Kr', '€')),
    '#default_value' => $currency,
    '#description' => t("Select which currency to use on events"),
  );

  $form['ding_event_frontpage'] = array(
    '#type' => 'fieldset',
    '#title' => t('Frontpage'),
  );
  $form['ding_event_frontpage']['ding_event_frontpage_items_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Events in frontpage list'),
    '#options' => array(
      '6' => '3 - 6',
      '12' => '6 - 12',
      '18' => '12 - 18',
    ),
    '#default_value' => variable_get('ding_event_frontpage_items_per_page', 6),
  );
  $form['ding_event_frontpage']['ding_event_frontpage_promoted'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only promoted events'),
    '#default_value' => variable_get('ding_event_frontpage_promoted', TRUE),
  );

  $form['ding_event_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event list'),
  );

  $form['ding_event_list']['ding_event_list_items_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Number of events'),
    '#description' => t('Choose how many events items you want on each page in the event list'),
    '#default_value' => variable_get('ding_event_list_items_per_page', 10),
    '#options' => array(
      '10' => '10',
      '12' => '12',
      '14' => '14',
      '16' => '16',
      '18' => '18',
      '20' => '20',
    ),
  );

  $form['ding_event_list']['ding_event_list_group_by_date'] = array(
    '#type' => 'checkbox',
    '#title' => t('Group events by date'),
    '#description' => t('Group events by date instead of month'),
    '#default_value' => variable_get('ding_event_list_group_by_date', FALSE),
  );

// Save us the trouble of running array_filter.
  $form['array_filter'] = array('#type' => 'value', '#value' => TRUE);
  return system_settings_form($form);
}

/**
 * Validate currency input and update field_instance
 * place2book only supports danish kr. If module is enabled and euro is selected currency; validation fails
 *
 * @param array $form
 *   An associative array containing the structure of the form.
 * @param array $form_state
 *   A keyed array containing the current state of the form.
 */
function ding_event_admin_submit(array $form, array &$form_state) {
  $currency = $form_state['values']['ding_event_currency_type'];
  $instance = field_read_instance('node', 'field_ding_event_price', 'ding_event');
  if ($instance !== FALSE) {
    $instance['settings']['suffix'] = ' ' . $currency;
    field_update_instance($instance);
  }
}
