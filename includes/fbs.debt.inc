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

  $res = fbs_service()->Payment->getFees(fbs_service()->agencyId, fbs_patron_id($account), FALSE, FALSE);

  foreach ($res as $fee) {
    $id = $fee->feeId;

    $data = array(
      'date' => $fee->creationDate,
      'display_name' => $fee->reasonMessage,
      // FBS only provides the amount left to be paid on each fee, so this
      // will only reflect that.
      'amount' => $fee->amount,
      // And the only thing we can do here is set it to zero, as the original
      // amount isn't available.
      'amount_paid' => 0,
      'invoice_number' => NULL,
      'type' => $fee->type,
    );

    if (!empty($fee->materials)) {
      // As ding only support one material number, we just grab the first.
      $mat = reset($fee->materials);
      $data['material_number'] = $mat->materialItemNumber;
    }

    $result[$id] = new DingProviderDebt($id, $data);

  }

  return $result;
}

/**
 * Implements provider debt, payment_received.
 */
function fbs_debt_payment_received($account, $debt_ids = array(), $order_id = NULL) {
  $payment_order = new FBS\Model\PaymentOrder();
  $payment_order->orderId = $order_id;
  $payment_order->feeIds = array();
  foreach ($debt_ids as $debt_id) {
    $payment_order->feeIds[] = $debt_id;
  }
  $res = fbs_service()->Payment->payFees(fbs_service()->agencyId, fbs_patron_id($account), $payment_order);

  foreach ($res as $confirmation) {
    if ($confirmation->paymentStatus !== 'paymentRegistered') {
      return FALSE;
    }
  }

  return TRUE;
}
