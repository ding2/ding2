<?php

function ding_dibs_admin_reports() {

  drupal_set_title(t('Ding DIBS reports'));

  $start = ( isset($_GET['page']) ) ? (int) $_GET['page'] : 0;
  $num_per_page = 15;
  $rows = array();

  drupal_add_css(drupal_get_path('module', 'ding_dibs') . '/css/ding_dibs.css');

  $query = db_select('dibs_transactions', 'd');

  $max_count = $query->fields('d', array('tid'))
    ->countQuery()
    ->execute()
    ->fetchField();

  $no_transactions_msg =  array(
    'no_transactions_msg' => array(
      '#type' => 'markup',
      '#markup' => '<p>' . t('No transactions found.') . '</p>',
    ),
  );

  $query
    ->condition('d.api_module', 'ding_dibs')
    ->condition('d.api_delta', 1)
    ->fields('d', array('payment_order_id',
                        'payment_transaction_id',
                        'payment_time',
                        'customer_uid',
                        'order_info_short',
                        'order_info_long',
                        'payment_price',
                        'payment_status',
                        'provider_payment_status',
                        'dibs_capture_status'))
    ->range($start*$num_per_page, $num_per_page)
    ->orderBy('payment_order_id', 'DESC');
  $result = $query->execute();

  $header = array(
    array('data' => t('Order ID'), 'class' => 'payment'),
    array('data' => t('Transaction ID'), 'class' => 'payment'),
    array('data' => t('Date'), 'class' => 'payment'),
    array('data' => t('User'), 'class' => 'payment'),
    array('data' => t('Text'), 'class' => 'payment'),
    array('data' => t('Amount'), 'class' => 'payment'),
    array('data' => t('Cleared'), 'class' => 'payment'),
    array('data' => t('Paid'), 'class' => 'payment'),
    array('data' => t('Captured'), 'class' => 'payment'),
    array('data' => '', 'class' => 'payment'),
  );

  foreach ($result as $record) {
    $status = $record->payment_status*1 . $record->provider_payment_status*1 . $record->dibs_capture_status*1;
    switch ($status) {
      case '111':
      case '000':
        $status = 'ok';
        break;
      case '100':
        $status = 'warning';
        break;
      default:
        $status = 'error';
        break;
    }
    $order_info_long = unserialize($record->order_info_long);
    if (is_array($order_info_long) && count($order_info_long) > 0) {
      $text = implode(array_shift($order_info_long)) . " ";
      $text .= implode(", ", array_map("array_shift", $order_info_long));
    } elseif (is_string($order_info_long)) {
      $text = $order_info_long;
    } else { // No info_long
      $text = $record->order_info_short;
    }
    $row = array(
      array('data' => check_plain($record->payment_order_id), 'class' => 'payment'),
      array('data' => check_plain($record->payment_transaction_id), 'class' => 'payment'),
      array('data' => check_plain($record->payment_time), 'class' => 'payment'),
      array('data' => check_plain($record->customer_uid), 'class' => 'payment'),
      array('data' => check_plain($text), 'class' => 'payment'),
      array('data' => check_plain($record->payment_price), 'class' => 'payment'),
      array('data' => ( $record->payment_status ) ? t('yes') : t('no'), 'class' => 'payment'),
      array('data' => ( $record->provider_payment_status ) ? t('yes') : t('no'), 'class' => 'payment'),
      array('data' => ( $record->dibs_capture_status ) ? t('yes') : t('no'), 'class' => 'payment'),
      array('data' => '', 'class' => 'icon ' . $status),
    );
    $rows[] = $row;
    $no_transactions_msg = FALSE;
  }

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));

  pager_default_initialize($max_count, $num_per_page);

  $output .= theme('pager');

  $items[] = array(
    'data' => t('Payments that have been cleared, but not registered as paid at the backend (and not captured), ought to be deleted at DIBS. Otherwise they might be manually captured by mistake.'),
  );
  $items[] = array(
    'data' => t('Payments that are cleared and paid, but not captured, will have to be manually captured at DIBS.'),
  );

  if ( $no_transactions_msg ) {
    $output .= drupal_render($no_transactions_msg);
  }

  $output .= theme('item_list', array('items' => $items));

  return render($output);

}
