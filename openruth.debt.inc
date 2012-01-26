<?php

/**
 * Get list of unpayed fees
 */
function openruth_debt_list($account) {
  $creds = ding_user_get_creds($account);
  $result = array();
  $status = _openruth_user_status($creds);

  if (isset($status->fees->fee)) {
    foreach ($status->fees->fee as $res) {
      // OpenRuth doesn't provide any unique id. Construct one.
      $id = md5($res->feeDate . $res->agencyCounter . $res->itemDisplayTitle . $res->feeAmount. $res->feeAmountPaid . $res->feeType);
      $result[$id] = new DingProviderDebt($res->feeDate, array(
                       'id' => $id,
                       'date' => $res->feeDate,
                       'display_name' => $res->itemDisplayTitle,
                       'pickup_branch_id' => $res->agencyCounter,
                       'amount' => $res->feeAmount,
                       'amount_paid' => isset($res->feeAmountPaid) ? $res->feeAmountPaid : 0,
                       'invoice_number' => isset($res->feeInvoiceNumber) ? $res->feeInvoiceNumber : FALSE,
                       'type' => $res->feeType,
                     ));
    }
  }

  return $result;
}

function openruth_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  $creds = ding_user_get_creds();

  // check that $amount adds up to the debts
  $status = _openruth_user_status($creds);
  if ( $amount != $status->userInfo->userFeesTotal ) {
    watchdog('openruth', 'Payment of amount %amount does not match the full amount. Payment was cancelled.', array(
      '%amount' => $amount,
    ), WATCHDOG_CRITICAL);
    return FALSE;
  }
  return openruth_client_invoke('add_payment', $creds['name'], $amount, $order_id);
}

/*
 * Note: Debts do NOT add up to total.
 * The payable amount is returned in <userInfo><userFeesTotal>0.00</userFeesTotal></userInfo>,
 * and does not include items where billing are handled elsewhere.
 * These items have a <feeInvoiceNumber> element,
 */
