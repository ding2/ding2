<?php
/**
 * @file
 * Handles availability information from the library system.
 */

/**
 * Implements provider availability, items.
 */
function fbs_availability_items($provider_ids) {
  $avails = fbs_service()->Catalog->getAvailability('1234', $provider_ids);
  $result = array();
  foreach ($avails as $item) {
    $result[$item->recordId] = array('available' => $item->available, 'reservable' => $item->reservable);
  }
  return $result;
}
