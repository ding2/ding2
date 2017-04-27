<?php
/**
 * @file
 *
 * Implements the historical_loans get interface.
 */

/**
 * Get a list of historical loans.
 */
function alma_historical_loans_get($account, $from = 0) {
  $creds = ding_user_get_creds($account);
  if (!empty($creds['name'])) {
    return alma_client_invoke('get_historical_loans', $creds['name'], $from);
  }
}
