<?php
/**
 * @file
 * Alma debt provider for Ding.
 */

/**
 * Provide list of DingProviderDebt objects for a user.
 *
 * @param stdClass $account
 *   User object to provide debts for.
 * @return array
 *   DingProviderDebt objects in array, keyed by debt ID.
 */
function alma_debt_list($account) {
  $data = alma_debt_get_debts($account);

  $debts = array();

  // Create DingProviderDebt instances from Alma's list.
  foreach ($data['debts'] as $debt) {
    $debtObj = new DingProviderDebt($debt['id'], $debt);

    $debts[$debt['id']] = $debtObj;
  }

  return $debts;
}

/**
 * Mark debts as paid.
 *
 * @param float $amount
 *   The total amount paid.
 * @param array $debt_ids
 *   IDs of the paid debts.
 * @param mixed $order_id
 *   Order ID of the payment transaction, to be recorded in the backend system.
 */
function alma_debt_payment_received($amount, $params = array(), $order_id = NULL) {
  // TODO: We should probably check that $amount adds up to the debts
  // we're going to mark paid, since Alma doesn't.
  if( !empty($params['order_ids']) ) {
    $order_ids = $params['debt_ids'];
  }
  elseif( !empty($params['debts']) ) {
    $order_ids = array_keys($params['debts']) ;
  }
  else {
    $order_ids = array();
  }

  return alma_client_invoke('add_payment', implode(',', $debt_ids), $order_id);
}

/**
 * Get list of debts from Alma.
 */
function alma_debt_get_debts($account, $reset = FALSE) {
  $creds = ding_user_get_creds($account);

  return alma_client_invoke('get_debts', $creds['name'], $creds['pass']);
}

