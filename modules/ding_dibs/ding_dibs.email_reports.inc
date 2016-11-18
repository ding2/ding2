<?php
/**
 * @file
 * E-mail reports functionality.
 */

/**
 * Form settings mailing reports.
 *
 * @return array
 *   Save results form settings.
 */
function ding_dibs_setting_emails($form, &$form_state) {
  drupal_add_css(drupal_get_path('module', 'ding_dibs') . '/css/ding_dibs.css');
  $hour = range(0, 23);
  $options_hour = array_map("_ding_dibs_generate_zero", $hour);
  $minute = range(0, 59);
  $options_minute = array_map("_ding_dibs_generate_zero", $minute);
  $form = array();
  $form['ding_dibs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Set the daily hour to run this cron'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '<div class="description">' . t('Set the daily hh:ii to run this cron.') . '</div></div>',
  );
  $form['ding_dibs']['ding_dibs_start_cron_hour'] = array(
    '#type' => 'select',
    '#options' => $options_hour,
    '#default_value' => variable_get('ding_dibs_start_cron_hour', 2),
    '#required' => TRUE,
  );
  $form['ding_dibs']['ding_dibs_start_cron_minute'] = array(
    '#type' => 'select',
    '#options' => $options_minute,
    '#default_value' => variable_get('ding_dibs_start_cron_minute', 0),
    '#required' => TRUE,
  );
  $form['ding_dibs_emails'] = array(
    '#type' => 'textarea',
    '#title' => t('Input emails that should be notified if something unusual happens with a payment.'),
    '#description' => t('Enter up to ten email addresses Enter through the separator or comma, without blank lines.'),
    '#default_value' => variable_get('ding_dibs_emails', ''),
    '#required' => TRUE,
    '#element_validate' => array('ding_dibs_emails_validate'),
  );
  return system_settings_form($form);
}

/**
 * Validation forms element email report settings.
 */
function ding_dibs_emails_validate($element, &$form_state, $form) {
  $arrays_email = preg_split("/\,|\r\n|\n/", $element['#value']);
  if (!empty($arrays_email)) {
    foreach ($arrays_email as $email) {
      $email = trim($email);
      if (!empty($email) && !valid_email_address($email)) {
        form_error($element, t('Please enter a valid email address.'));
      }
    }
  }
}

/**
 * The function that create table reports for email mailing.
 *
 * @return array
 *   The result of the function is a value as a table.
 */
function ding_dibs_email_reports() {
  $time = REQUEST_TIME - 86400;
  $report = db_select('dibs_transactions', 'd')
    ->fields('d', array(
      'payment_order_id',
      'payment_transaction_id',
      'payment_time',
      'customer_uid',
      'order_info_short',
      'order_info_long',
      'payment_price',
      'payment_status',
      'provider_payment_status',
      'dibs_capture_status',
    ))
    ->condition('payment_time', date('Y-m-d H:i:s', $time), '>')
    ->condition('d.api_module', 'ding_dibs')
    ->condition('d.api_delta', 1)
    ->orderBy('payment_order_id', 'DESC')
    ->execute()
    ->fetchAll();
  $max_count = count($report);
  if (!$max_count) {
    return '<p>' . t('No transactions found.') . '</p>';
  }
  for ($count = 0; $count < $max_count; $count++) {
    // As a result deliveries should fall reports from the database table
    // "dibs transactions".
    // Columns "payment status", "provider payment_status",
    // "dibs_capture_status" have both equally have the status of unpaid (0)
    // or paid (1).
    // Testing conducted by feedback from.
    if (!(
      // Payment status equal provider payment status.
      $report[$count]->payment_status == $report[$count]->provider_payment_status
      // Payment status equal dibs capture status.
      && $report[$count]->payment_status == $report[$count]->dibs_capture_status
      // Provider payment status equal dibs capture status.
      && $report[$count]->provider_payment_status == $report[$count]->dibs_capture_status
    )) {
      $report_valid[] = $report[$count];
    }
  }
  $header = array(
    array('data' => t('Order ID')),
    array('data' => t('Transaction ID')),
    array('data' => t('Date')),
    array('data' => t('User')),
    array('data' => t('Text')),
    array('data' => t('Amount')),
    array('data' => t('Cleared')),
    array('data' => t('Paid')),
    array('data' => t('Captured')),
  );
  $rows = array();
  foreach ($report_valid as $record) {
    $rows[] = _ding_dibs_report_generation_values($record);
  }

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'ding_dibs_email_reports'),
  ));
  return $output;
}

/**
 * Callback that builds page reports run cron.
 *
 * @return array
 *   The result of the function is a value as a table.
 */
function ding_dibs_cron_report() {
  $report = db_select('ding_dibs_report_cron', 'd')
    ->fields('d', array('id', 'time_start', 'status'))
    ->orderBy('id', 'DESC')
    ->execute()
    ->fetchAll();
  $max_count = count($report);
  if (!$max_count) {
    return drupal_set_message(t('No cron report.'), 'warning');
  }
  drupal_add_css(drupal_get_path('module', 'ding_dibs') . '/css/ding_dibs.css');
  $header = array(array('data' => t('Date')), array('data' => t('Message')));
  $rows = array();
  foreach ($report as $record) {
    if (empty($record->status)) {
      $text = t('%date : Job failed.', array(
        '%date' => format_date($record->time_start, 'custom', 'dS F H:i', date_default_timezone_get()))
      );
    }
    else {
      $from_date = format_date($record->time_start - 86400, 'custom', 'dS F H:i', date_default_timezone_get());
      $to_date = format_date($record->time_start, 'custom', 'dS F H:i', date_default_timezone_get());
      $text = t('Job delivered report for %from_date - %to_date.', array('%from_date' => $from_date, '%to_date' => $to_date));
    }
    $rows[] = array(
      // Date and time run cron.
      array(
        'data' => check_plain(
          format_date($record->time_start, 'custom', 'dS F H:i', date_default_timezone_get())
        ),
      ),
      // Text output run cron.
      array('data' => $text),
    );
  }
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));
  return $output;
}

/**
 * The function adds to the dataset for the numbers zero to ten.
 *
 * @param int $item
 *   The number of period.
 */
function _ding_dibs_generate_zero($item) {
  return str_pad($item, 2, "0", STR_PAD_LEFT);
}

/**
 * The function generates a table row.
 *
 * @param object $dibs_transactions_value
 *   Object database table data dibs transactions.
 *
 * @return array
 *   Return table row for mailing reports.
 */
function _ding_dibs_report_generation_values($dibs_transactions_value) {
  // Long description of table warrant dibs_transactions.
  $order_info_long = unserialize($dibs_transactions_value->order_info_long);
  if (is_array($order_info_long) && count($order_info_long) > 0) {
    $text = implode(array_shift($order_info_long)) . ' ';
    $text .= implode(', ', array_map('array_shift', $order_info_long));
  }
  elseif (is_string($order_info_long)) {
    $text = $order_info_long;
  }
  else {
    $text = $dibs_transactions_value->order_info_short;
  }
  $row = array(
    // ID orders payment.
    array('data' => check_plain($dibs_transactions_value->payment_order_id)),
    // ID orders transaction.
    array('data' => check_plain($dibs_transactions_value->payment_transaction_id)),
    // Time payment.
    array('data' => check_plain($dibs_transactions_value->payment_time)),
    // User ID who has charge.
    array('data' => check_plain($dibs_transactions_value->customer_uid)),
    // Order info.
    array('data' => check_plain($text)),
    // Product price the order in payment.
    array('data' => check_plain($dibs_transactions_value->payment_price)),
    // Status payment.
    array('data' => $dibs_transactions_value->payment_status ? t('yes') : t('no')),
    // Provider payment status.
    array('data' => $dibs_transactions_value->provider_payment_status ? t('yes') : t('no')),
    // Captured payment status.
    array('data' => $dibs_transactions_value->dibs_capture_status ? t('yes') : t('no')),
  );
  return $row;
}
