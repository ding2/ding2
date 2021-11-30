<?php

/**
 * @file
 * Handler for the administrative settings form for the module.
 */

/**
 * Implements hook_form().
 *
 * The reports mail settings.
 */
function ding_debt_easy_reports_admin_mails_settings_form($form, &$form_state) {
  $default = _ding_debt_easy_reports_mail_config();

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'ding_debt_easy_reports') . '/css/ding_debt_easy_reports.admin.css',
  );

  $form['ding_debt_easy_reports_mail'] = [
    '#type' => 'fieldset',
    '#title' => t('Mail report settings'),
    '#tree' => TRUE,
  ];

  $form['ding_debt_easy_reports_mail']['to'] = [
    '#type' => 'textfield',
    '#title' => t('To'),
    '#description' => t('Comma separated list of e-mail-addresses'),
    '#default_value' => $default['to'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_reports_mail']['title'] = [
    '#type' => 'textfield',
    '#title' => t('Mail title'),
    '#description' => t('Note: the "%count" in the title is substituted with the number payments awaiting action'),
    '#default_value' => $default['title'],
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_reports_mail']['header'] = [
    '#type' => 'text_format',
    '#title' => t('Mail header', [
      '@url' => DING_DEBT_EASY_DEFAULT_PRIVACY_URL,
    ]),
    '#default_value' => $default['header']['value'],
    '#format' => $default['header']['format'],
    '#rows' => 15,
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_reports_mail']['footer'] = [
    '#type' => 'text_format',
    '#title' => t('Mail footer', [
      '@url' => DING_DEBT_EASY_DEFAULT_PRIVACY_URL,
    ]),
    '#default_value' => $default['footer']['value'],
    '#format' => $default['footer']['format'],
    '#rows' => 15,
    '#required' => TRUE,
  ];

  $form['ding_debt_easy_reports_mail_test'] = [
    '#type' => 'fieldset',
    '#title' => t('Test mail'),
    '#description' => t('Try sending test mail. If you have change anything in the above form, submit the form first or the changes will not be used in the mail.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ];

  $form['ding_debt_easy_reports_mail_test']['send'] = array(
    '#type' => 'submit',
    '#value' => t('Send test'),
    '#ajax' => array(
      'callback' => '_ding_debt_easy_reports_send_mail',
    ),
    '#attributes' => [
      'class' => [
        'test-mail-send-btn',
      ],
    ],
  );

  return system_settings_form($form);
}

/**
 * Implements hook_form_validate().
 *
 * Validate that the mail-addresses enter is mail addresses.
 */
function ding_debt_easy_reports_admin_mails_settings_form_validate(&$form, &$form_state) {
  $values = $form_state['values'];
  $fields = ['to'];
  if (!empty($values['ding_debt_easy_reports_mail']['cc'])) {
    $fields[] = 'cc';
  }

  foreach ($fields as $field) {
    $mails = explode(',', $values['ding_debt_easy_reports_mail'][$field]);
    foreach ($mails as $mail) {
      if (!filter_var(trim($mail), FILTER_VALIDATE_EMAIL)) {
        form_error($form['ding_debt_easy_reports_mail'][$field], t('Invalid email format: %mail', ['%mail' => $mail]));
      }
    }
  }
}
