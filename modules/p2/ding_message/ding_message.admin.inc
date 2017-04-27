<?php

/**
 * @file
 * Code for the Ding message administration.
 */

/**
 * Displays the amount of daily checked users in the administration page.
 */
function ding_messages_admin_user_checks() {

  $query = db_select('ding_message_check', 'dmc');

  $query->addExpression("FROM_UNIXTIME(dmc.time, '%Y %m %d')", 'date');
  $query->addExpression('COUNT(dmc.time)', 'cnt');

  $query->groupBy('date')->orderBy('date', 'ASC');

  $results = array();
  foreach ($query->execute()->fetchAllKeyed(0, 1) as $date => $count) {
    $results[] = array($date, $count);
  }

  $output = array(
    '#theme' => 'table',
    '#rows' => $results,
    '#header' => array(t('Date'), t('Count')),
    '#sticky' => TRUE,
  );

  return $output;
}

/**
 * Todo: function description here.
 */
function ding_message_admin_form($form, &$form_state) {
  $form['ding_message_login_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Login delay'),
    '#description' => t('The time to pass after a user logs out before they come into consideration for message updates. The number is the amount of seconds.'),
    '#default_value' => variable_get('ding_message_login_delay', 3600),
  );
  $form['ding_message_batch_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Batch size'),
    '#description' => t('The number of users to evaluate each time cron runs.'),
    '#default_value' => variable_get('ding_message_batch_size', 50),
  );
  $form['ding_message_list_check_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Lists to check'),
    '#description' => t('The number of lists to check for each user.'),
    '#default_value' => variable_get('ding_message_list_check_size', 10),
  );
  $form['ding_message_search_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Search size'),
    '#description' => t('The maximum number of searches to run for each list..'),
    '#default_value' => variable_get('ding_message_search_size', 5),
  );
  $form['ding_message_channel_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum messages pr. channel'),
    '#description' => t('The maximum number of messages in a channel before channel is bypassed'),
    '#default_value' => variable_get('ding_message_channel_max', 10),
  );
  return system_settings_form($form);
}

/**
 * Todo: function description here.
 */
function ding_message_update_form($form, &$form_state) {
  global $user;
  $form['ding_message_update_uid'] = array(
    '#type' => 'textfield',
    '#title' => t('Uid to fetch new messages for'),
    '#description' => t('Update a specific user and fetch notifications about new list updates.'),
    '#default_value' => $user->uid,
  );

  $form['reset_user'] = array(
    '#type' => 'checkbox',
    '#title' => 'Fetch everything again.',
    '#description' => 'Fetches everything for lists no matter when they were last checked.',
  );
  $form['ding_message_update_form_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Update',
  );

  return $form;
}

/**
 * Todo: function description here.
 */
function ding_message_update_form_submit($form, &$form_state) {
  $accounts[] = $form_state['values']['ding_message_update_uid'];
  $reset = $form_state['values']['reset_user'];
  ding_message_update_users($accounts, TRUE, $reset);
  drupal_set_message(t('User updated'));
}

/**
 * Todo: function description here.
 */
function ding_message_purge_user_messages() {
  global $user;
  ding_message_purge_messages($user->uid);
  drupal_set_message(t("Your notifications has been marked as read"));
  drupal_goto("user");
}

/**
 * Todo: function description here.
 */
function ding_message_purge() {
  ding_message_purge_messages();
  return "OK";
}
