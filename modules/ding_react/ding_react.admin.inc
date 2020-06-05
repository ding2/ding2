<?php

/**
 * @file
 * Admin settings for Ding React module.
 */

/**
 * Admin settings for the module.
 */
function ding_react_admin_settings_form($form, &$form_state) {
  $form['services'] = [
    '#type' => 'fieldset',
    '#title' => t('Services'),
  ];

  $form['services']['ding_react_material_list_url'] = [
    '#type' => 'textfield',
    '#title' => t('Material List'),
    '#description' => t('Url to the Material List service instance to use.'),
    '#default_value' => ding_react_material_list_url(),
    '#required' => TRUE,
    '#element_validate' => [ 'ding_react_element_validate_url' ],
  ];

  $form['services']['ding_react_follow_searches_url'] = [
    '#type' => 'textfield',
    '#title' => t('Follow Searches'),
    '#description' => t('Url to the Follow Searches service instance to use.'),
    '#default_value' => ding_react_follow_searches_url(),
    '#required' => TRUE,
    '#element_validate' => [ 'ding_react_element_validate_url' ],
  ];

  $form['services']['ding_react_cover_service_url'] = [
    '#type' => 'textfield',
    '#title' => t('Cover Service'),
    '#description' => t('Url to the Cover Service instance to use.'),
    '#default_value' => ding_react_cover_service_url(),
    '#required' => TRUE,
    '#element_validate' => [ 'ding_react_element_validate_url' ],
  ];

  $form['migration'] = [
    '#type' => 'fieldset',
    '#title' => t('Migration'),
  ];

  $form['migration']['ding_react_migrate_timeout'] = [
    '#type' => 'textfield',
    '#title' => t('Migration timeout'),
    '#description' => t('The number of seconds to wait for an external service to complete a migration during login. A high timeout reduces risk of the migration not completing. A low timeout prevents the login procedure from stalling. Incomplete migrations will be retried the next time the user logs in.'),
    '#default_value' => variable_get('ding_react_migrate_timeout', 5),
    '#required' => TRUE,
    '#element_validate' => [ 'element_validate_integer_positive' ],
  ];

  $form['migration']['user_status'] = [
    '#type' => 'fieldset',
    '#title' => t('User migration status'),
  ];

  $form['migration']['user_status']['user_id'] = [
    '#type' => 'textfield',
    '#title' => t('User id'),
    '#description' => t('The Drupal id of the user to check. Enter the id and hit TAB to search.'),
    '#ajax' => [
      'callback' => 'ding_react_admin_user_callback',
      'wrapper' => 'ding-react-app-user-data',
      'method' => 'replace',
    ],
  ];
  $form['migration']['user_status']['user'] = [
    '#prefix' => '<div id="ding-react-app-user-data">',
    '#suffix' => '</div>',
  ];
  if (!empty($form_state['values']['user_id'])) {
    $account = user_load($form_state['values']['user_id']);
    if ($account) {
      $form['migration']['user_status']['user']['user_account'] = [
        '#type' => 'value',
        '#value' => $account,
      ];
      $form['migration']['user_status']['user']['openlist_uid'] = [
        '#type' => 'item',
        '#title' => t('Openlist user id'),
        '#markup' => (!empty($account->openlist_uid)) ? $account->openlist_uid : t('No OpenList UID for user'),
        '#description' => t('User ids beginning with "@prefix" have already been migrated.', ['@prefix' => DING_REACT_MIGRATED_UID_PREFIX]),
      ];
      $form['migration']['user_status']['user']['reset'] = [
        '#type' => 'submit',
        '#value' => t('Reset migration status'),
        '#submit' => ['ding_react_user_reset_migration_status'],
      ];
    }
  }

  $form['debug'] = [
    '#type' => 'fieldset',
    '#title' => t('Debugging'),
  ];
  $form['debug']['ding_react_debug'] = [
    '#type' => 'checkbox',
    '#title' => t('Enable debug logging'),
    '#default_value' => variable_get('ding_react_debug', FALSE),
  ];

  // Mimic system_settings_form().
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  ];

  return $form;
}

/**
 * Form element validator for urls.
 */
function ding_react_element_validate_url($element, &$form_state, $form) {
  if (!empty($element['#value']) && !valid_url($element['#value'], true)) {
    form_error($element, t('Please enter a valid url.'));
  }
}

/**
 * Admin settings form form submit handler.
 *
 * We do not use system_settings_form() here as our form is a mix of variables
 * and functionality. Thus we set each variable explicitly.
 */
function ding_react_admin_settings_form_submit($form, &$form_state) {
  $variables = [
    'ding_react_material_list_url',
    'ding_react_follow_searches_url',
    'ding_react_migrate_timeout',
    'ding_react_debug',
  ];
  array_walk($variables, function ($variable) use ($form_state) {
    variable_set($variable, $form_state['values'][$variable]);
  });
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * AJAX callback for admin user lookup.
 */
function ding_react_admin_user_callback(array $form, array $form_state) {
  return $form['migration']['user_status']['user'];
}

/**
 * Submit handler when resetting user migration status.
 */
function ding_react_user_reset_migration_status(array $form, array &$form_state) {
  $account = $form_state['values']['user_account'];
  if (!$account || empty($account->openlist_uid)) {
    return;
  }

  // We mark migrated users by prefixing their OpenList uid. Remove the prefix
  // to reset status.
  $account->openlist_uid = preg_replace('/^' . DING_REACT_MIGRATED_UID_PREFIX . '/', '', $account->openlist_uid);
  user_save($account);

  drupal_set_message(t('Reset migration status for user %uid', ['%uid' => $account->uid]), 'status');
  ding_react_log('Reset migration status for user %uid', ['%uid' => $account->uid], WATCHDOG_NOTICE);
}
