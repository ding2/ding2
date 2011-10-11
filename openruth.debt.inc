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
                       'type' => $res->feeType,
                     ));
    }
  }

  return $result;
}

function openruth_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  $creds = ding_user_get_creds();
  // TODO: We should probably check that $amount adds up to the debts
  return openruth_client_invoke('add_payment', $creds['name'], $amount, $order_id);
}
