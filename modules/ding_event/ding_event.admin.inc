<?php
/**
 * @file.
 * add system configuration option to set currency displayed on event(s)
 */

/**
 * Get a form to select currency (Euro | Kr)
 * @param $form
 * @param $form_state
 * @return mixed
 */
function ding_event_admin_currency_setting_form($form, &$form_state) {
  $currency = variable_get('ding_event_currency_type', 'Kr');

  $form['ding_event_currency'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event currency'),
    '#tree' => FALSE,
    '#description' => t("Select which currency to use on events"),
  );

  $form['#submit'][] = 'ding_event_admin_currency_submit';

  $form['ding_event_currency']['ding_event_currency_type'] = array(
    '#type' => 'radios',
    '#title' => t('Currency'),
    '#options' => drupal_map_assoc(array('kr', '€')),
    '#default_value' => $currency,
  );

// Save us the trouble of running array_filter.
  $form['array_filter'] = array('#type' => 'value', '#value' => TRUE);
  return system_settings_form($form);
}

/**
 * Validate input and update field_instance
 * place2book only supports danish kr. If module is enabled and euro is selected currency; validation fails
 * @param $form
 * @param $form_state
 */
function ding_event_admin_currency_submit($form, &$form_state) {
  $currency = $form_state['values']['ding_event_currency_type'];
  $instance = field_read_instance('node', 'field_ding_event_price', 'ding_event');
  if ($instance !== FALSE) {
    $instance['settings']['suffix'] = ' ' . $currency;
    field_update_instance($instance);
  }
}

/**
 * Implement hook_permission
 */
function ding_event_permission() {
  return array(
    'administer event settings' => array(
      'title' => t('Administer event settings')
    ),
  );
}
