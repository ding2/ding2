<?php

/**
 * @file
 * Module's admin features.
 */

/**
 * Administration form.
 */
function ding_frontend_settings($form, &$form_state) {
  $types = array(
    'ding_news' => t('News'),
    'ding_event' => t('Event'),
  );

  // Determine default promote to frontpage using CT settings.
  $default_values = array();
  foreach ($types as $key => $type) {
    $promote_status = variable_get('node_options_' . $key);

    if (in_array('promote', $promote_status)) {
      $default_values[$key] = $key;
    }
  }

  $form['ding_frontend_fe_promote_types'] = array(
    '#title' => t('Promote types to Frontpage'),
    '#type' => 'checkboxes',
    '#options' => $types,
    '#default_value' => $default_values,
    '#description' => t('Please specify types which can be promoted to Frontpage.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Custom submit handler for settings form.
 */
function ding_frontend_settings_submit($form, &$form_state) {
  ding_frontend_set_promote_configuration($form_state['values']['ding_frontend_fe_promote_types']);
}

/**
 * Function to set drupal promote to frontpage from custom form settings.
 *
 * @param array $custom_promote_settings
 *   Contain custom settings for drupal promote to frontpage settings.
 *
 * @see ding_frontend_settings()
 */
function ding_frontend_set_promote_configuration(array $custom_promote_settings) {
  $types = array(
    'ding_news',
    'ding_event',
  );

  foreach ($types as $type) {
    $conf = variable_get('node_options_' . $type, array('status', 'promote'));
    if (in_array('promote', $conf)) {
      unset($conf[array_search('promote', $conf)]);
    }
    if ($custom_promote_settings[$type]) {
      $conf[] = 'promote';
    }
    variable_set('node_options_' . $type, $conf);
  }
}
