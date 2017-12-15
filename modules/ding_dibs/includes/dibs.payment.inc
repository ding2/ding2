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
    $params['order_info_long'] = array();
    $params['order_info_short'] = t('Library dues: @value', array(
      '@value' => implode(', ', $params['params']['debt_ids']),
    ));
  }

  $transaction_hash = ding_dibs_payment_prepare($amount, $params, $callback, FALSE);

  return 'payment/dibs/redirect/' . $transaction_hash;
}

