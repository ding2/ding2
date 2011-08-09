<?php

/**
 * Implements provider availability, holdings.
 */
function openruth_availability_holdings($provider_ids) {
  $holdings = openruth_client_invoke('get_holdings', $provider_ids);
  if (is_string($holdings)) {
    watchdog('openruth', '@method error: “@message”', array('@method' => 'get_holdings', '@message' => $holdings), WATCHDOG_ERROR);
    return array();
  }
  return $holdings;
}
