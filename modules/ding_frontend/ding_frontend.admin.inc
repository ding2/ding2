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
  $form['ding_frontend_fe_promote_types'] = array(
    '#title' => t('Promote types to Fronpage'),
    '#type' => 'checkboxes',
    '#options' => $types,
    '#default_value' => variable_get('ding_frontend_fe_promote_types', array('ding_event' => 'ding_event')),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'ding_frontend_settings_submit';
  return $form;
}

/**
 * Custom submit handler for settings form.
 */
function ding_frontend_settings_submit($form, &$form_state) {
  $types = array(
    'ding_news',
    'ding_event',
  );
  foreach ($types as $type) {
    $conf = variable_get('node_options_' . $type, array('status', 'promote'));
    if (in_array('promote', $conf)) {
      unset($conf[array_search('promote', $conf)]);
    }
    if ($form_state['values']['ding_frontend_fe_promote_types'][$type]) {
      $conf[] = 'promote';
    }
    variable_set('node_options_' . $type, $conf);
  }
}
