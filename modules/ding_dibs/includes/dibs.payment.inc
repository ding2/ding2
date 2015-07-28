<?php
/**
 * @file
 * Payment provider implementation for Ding!
 */

/**
 * Generate the payment URL to redirect the user to.
 */
function ding_dibs_payment_get_url($amount, $params, $callback) {
  if (!empty($params['params']['debt_ids'])) {
    $params['order_info_long'] = array(array(t('Payment of library dues:')));
    foreach ($params['params']['debt_ids'] as $debt_id) {
      $params['order_info_long'][] = array($debt_id);
    }
  }

  $transaction_hash = ding_dibs_payment_prepare($amount, $params, $callback, FALSE);

  return 'payment/dibs/redirect/' . $transaction_hash;
}

