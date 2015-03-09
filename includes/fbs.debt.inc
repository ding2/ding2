<?php

/**
 * @file
 * Handles user debts.
 */

/**
 * Implements provider debt, list.
 */
function fbs_debt_list($account) {
  $result = array();

  $res = fbs_service()->Payment->getFees(fbs_service()->agencyId, fbs_patron_id($account));

  foreach ($res as $fee) {
    $id = $fee->feeId;
    $result[$id] = new DingProviderDebt($id, array(
      'date' => $fee->creationDate,
      'display_name' => $fee->reasonMessage,
      'amount' => $fee->amount,
      'amount_paid' => $fee->paidDate ? $fee->amount : 0,
      'invoice_number' => NULL,
      'type' => $fee->type,
    ));
  }

  return $result;
}

/**
 * Implements provider debt, payment_received.
 */
function fbs_debt_payment_received($account, $debt_ids = array(), $order_id = NULL) {
  $payment_order = new FBS\Model\PaymentOrder();
  $payment_order->orderId = $order_id;
  $payment_order->feeId = array();
  foreach ($debt_ids as $debt_id) {
    $payment_order->feeId[] = $debt_id;
  }
  $res = fbs_service()->Payment->payFees(fbs_service()->agencyId, fbs_patron_id($account), $payment_order);

  foreach ($res as $confirmation) {
    if ($confirmation->paymentStatus !== 'paymentRegistered') {
      return FALSE;
    }
  }

  return TRUE;
}
