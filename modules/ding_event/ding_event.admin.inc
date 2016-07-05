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

  $view = views_get_view('ding_event');
  $view_items_per_page = $view->display['ding_event_list_frontpage']->display_options['pager']['options']['items_per_page'];
  $default_items_per_page = variable_get('ding_event_frontpage_items_per_page', $view_items_per_page);

  $form['ding_event']['ding_event_frontpage_items_per_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of events on front page.'),
    '#size' => 4,
    '#description' => t('Maximum number of events on front page.'),
    '#default_value' => $default_items_per_page,
    '#element_validate' => array('element_validate_integer_positive'),
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
