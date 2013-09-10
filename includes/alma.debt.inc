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
 * @param bool $reset
 *   Reset static cache if TRUE else get debts from cache.
 *
 * @return array
 *   DingProviderDebt objects in array, keyed by debt ID.
 */
function alma_debt_list($account, $reset = FALSE) {
  $creds = ding_user_get_creds($account);

  // Use session cache to speed up communication with Alma.
  $results = &drupal_static(__FUNCTION__, FALSE);
  if (!$results || $reset) {
    // Get debts from Alma.
    $debts = alma_client_invoke('get_debts', $creds['name'], $creds['pass']);

    // Create DingProviderDebt instances from Alma's list.
    $result = array();
    foreach ($debts['debts'] as $debt) {
      // Get the material number from the display name and remove it form it.
      preg_match('/^(\w+)\s+(.+)/', $debt['display_name'], $matchs);
      $debt['display_name'] = $matchs[2];
      $debt['material_number'] = $matchs[1];

      $debt_object = new DingProviderDebt($debt['id'], $debt);
      $result[$debt['id']] = $debt_object;
    }
  }

  return $result;
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
 *
 * @return array
 *   Array from ALMA with the results.
 */
function alma_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  // Return result from Alma.
  return alma_client_invoke('add_payment', implode(',', $debt_ids), $order_id);
}
