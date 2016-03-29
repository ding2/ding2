<?php
/**
 * @file
 * Admin-related stuff in this file.
 */

/**
 * Module settings form.
 *
 * Set basic info for future mailing.
 */
function ding_dashboard_notification_admin_form() {
  $form = array(
    '#tree' => TRUE,
  );

  $form['ding_dashboard_notification_from_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('From email address'),
    '#default_value' => variable_get('ding_dashboard_notification_from_mail', ''),
    '#required' => TRUE,
  );

  $form['ding_dashboard_notification_from_name'] = array(
    '#type' => 'textfield',
    '#title' => t('From name'),
    '#default_value' => variable_get('ding_dashboard_notification_from_name', ''),
    '#required' => TRUE,
  );

  $form['ding_dashboard_notification_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('ding_dashboard_notification_subject', ''),
    '#description' => t('This will be prepended to the mail subject/title.'),
    '#required' => TRUE,
  );

  $form['ding_dashboard_notification_footer'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer'),
    '#default_value' => variable_get('ding_dashboard_notification_footer', ''),
    '#description' => t('This will be prepended to the mail footer. You can use placeholder @year.'),
    '#required' => TRUE,
  );

  $roles = user_roles(TRUE);
  // Exludes anon and authenticated roles.
  $roles = array_slice($roles, 2);
  // And make copy value to keys.
  $roles = array_combine($roles, $roles);
  // Makes header translatible.
  $header = array_map(function($v) {
    return t($v);
  }, $roles);
  // Adds custom elem to header.
  array_unshift($header, 'Action');

  // Define all editor actions.
  $editor_actions = array(
    EDITORIAL_ACTION_APPROVE => t('Approve'),
    EDITORIAL_ACTION_REJECT => t('Reject'),
    EDITORIAL_ACTION_DELETE => t('Delete'),
    EDITORIAL_ACTION_COMMENTED => t('Commented'),
  );

  $form['notifications'] = array(
    '#theme' => 'ed_notifications_table',
    '#header' => $header,
    '#author_actions' => array(
      EDITORIAL_ACTION_PUSH  => t('Push'),
    ),
    '#editor_actions' => $editor_actions,
  );

  // Author settings.
  $values = variable_get('ding_dashboard_notification_settings', array());
  foreach ($roles as $role) {
    $form['notifications']['author'][EDITORIAL_ACTION_PUSH][$role] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($values['author'][EDITORIAL_ACTION_PUSH][$role]) ? $values['author'][EDITORIAL_ACTION_PUSH][$role] : 0,
    );
  }

  // Editor settings.
  foreach ($editor_actions as $action => $name) {
    $form['notifications']['editor'][$action] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($values['editor'][$action]) ? $values['editor'][$action] : 0,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Validate editorial dashboard notification admin form.
 *
 * @see ding_dashboard_notification_admin_form()
 */
function ding_dashboard_notification_admin_form_validate($form, &$form_state) {
  $values = &$form_state['values'];

  if (!filter_var($values['ding_dashboard_notification_from_mail'], FILTER_VALIDATE_EMAIL)) {
    form_set_error('ding_dashboard_notification_from_mail', t('Email not valid.'));
  }

  $values['ding_dashboard_notification_from_name'] = check_plain(trim($values['ding_dashboard_notification_from_name']));
  $values['ding_dashboard_notification_subject'] = check_plain(trim($values['ding_dashboard_notification_subject']));
  $values['ding_dashboard_notification_footer'] = check_plain(trim($values['ding_dashboard_notification_footer']));
}

/**
 * Validate editorial dashboard notification admin form.
 *
 * @see ding_dashboard_notification_admin_form()
 */
function ding_dashboard_notification_admin_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  variable_set('ding_dashboard_notification_from_mail', $values['ding_dashboard_notification_from_mail']);
  variable_set('ding_dashboard_notification_from_name', $values['ding_dashboard_notification_from_name']);
  variable_set('ding_dashboard_notification_subject', $values['ding_dashboard_notification_subject']);
  variable_set('ding_dashboard_notification_footer', $values['ding_dashboard_notification_footer']);
  variable_set('ding_dashboard_notification_settings', $values['notifications']);
}
