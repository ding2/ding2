<?php
/**
 * @file
 * Admin related things here.
 */

/**
 * Creates an administrative block on the configuration page
 * for grouping various settings.
 *
 * @return type
 *   HTML for the block.
 */
function bpi_admin_menu_block_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  if ($content) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }

  return $output;
}


/**
 * Administrative settings form.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 * @return array
 *   Form structure prepared for admin settings.
 */
function bpi_admin_settings_form($form, $form_state) {
  $form['bpi_agency_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Agency ID'),
    '#default_value' => variable_get('bpi_agency_id', ''),
    '#required' => TRUE,
  );

  $form['bpi_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#default_value' => variable_get('bpi_service_url', ''),
    '#required' => TRUE,
  );

  $form['bpi_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => variable_get('bpi_api_key', ''),
    '#required' => TRUE,
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/admin.styles.css';
  $form['#validate'][] = 'bpi_admin_settings_form_validate';

  return system_settings_form($form);
}

/**
 * Custom validate handler for common settings form.
 *
 * Used for url validation, for now.
 *
 * @see bpi_admin_settings_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 */
function bpi_admin_settings_form_validate(&$form, &$form_state) {
  $url = $form_state['values']['bpi_service_url'];

  if (!valid_url($url, TRUE)) {
    form_set_error('bpi_service_url', t('Please enter a valid url.'));
  }
}
