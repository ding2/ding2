<?php
/**
 * @file
 * Handles fees and payment information in relation to OpenRuth.
 */

/**
 * Get list of unpayed fees.
 */
function openruth_debt_list($account) {
  $creds = ding_user_get_creds($account);
  $result = array();
  $status = _openruth_user_status($creds);

  if (isset($status->fees->fee)) {
    foreach ($status->fees->fee as $fee) {
      // OpenRuth doesn't provide any unique id. Construct one.
      $id = md5(serialize($fee));
      $result[$id] = new DingProviderDebt($id, array(
        'date' => $fee->feeDate,
        'display_name' => $fee->itemDisplayTitle,
        'pickup_branch_id' => $fee->agencyCounter,
        'amount' => $fee->feeAmount,
        'amount_paid' => isset($fee->feeAmountPaid) ? $fee->feeAmountPaid : 0,
        'invoice_number' => isset($fee->feeInvoiceNumber) ? $fee->feeInvoiceNumber : FALSE,
        'type' => $fee->feeType,
      ));
    }
  }

  return $result;
}

/**
 * Callback function used to update OpenRuth after a payment have been received.
 *
 * @param string $amount
 *   The amount that have to be payed.
 * @param array $debt_ids
 *   The payment id's.
 * @param string $order_id
 *   The payments order id.
 *
 * @return bool
 *   If TRUE the payment was received or FALSE on failure.
 */
function openruth_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  $creds = ding_user_get_creds();

  // Check that $amount adds up to the debts.
  $status = _openruth_user_status($creds);
  if ($amount != $status->userInfo->userFeesTotal) {
    watchdog('openruth', 'Payment of amount %amount does not match the full amount. Payment was cancelled.', array(
      '%amount' => $amount,
    ), WATCHDOG_CRITICAL);
    return FALSE;
  }
  return openruth_client_invoke('add_payment', $creds['name'], $amount, $order_id);
}

/**
 * Note: Debts do NOT add up to total.
 * The payable amount is returned in <userInfo><userFeesTotal>0.00</userFeesTotal></userInfo>,
 * and does not include items where billing are handled elsewhere.
 * These items have a <feeInvoiceNumber> element,
 */
