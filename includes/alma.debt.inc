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
function alma_debt_list($account, $reset = FALSE) {
  $creds = ding_user_get_creds($account);

  // Use session cache to speed up communication with Alma.
  $cache_key = 'alma_debts';
  $results = &drupal_static(__FUNCTION__, FALSE);
  if (!$results || $reset) {
    $results = ding_provider_session_cache_get($cache_key);
    if (!$results || $reset) {
      // Get debts from Alma.
      $debts = alma_client_invoke('get_debts', $creds['name'], $creds['pass']);

      // Create DingProviderDebt instances from Alma's list.
      $result = array();
      foreach ($debts['debts'] as $debt) {
        $debt_object = new DingProviderDebt($debt['id'], $debt);
        $result[$debt['id']] = $debt_object;
      }

      // Store result into the session cache.
      ding_provider_session_cache_set($cache_key, $results);
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
 */
function alma_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  // Clear loans session cache.
  ding_provider_session_cache_clear('alma_debts');

  // Return result from Alma.
  return alma_client_invoke('add_payment', implode(',', $debt_ids), $order_id);
}
