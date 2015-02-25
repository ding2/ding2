<?php
/**
 * @file
 * Handles availability information from the library system.
 */

/**
 * Implements provider availability, items.
 */
function fbs_availability_items($provider_ids) {
  $avails = fbs_service()->Catalog->getAvailability(fbs_service()->agencyId, $provider_ids);
  $result = array();
  foreach ($avails as $item) {
    $result[$item->recordId] = array('available' => $item->available, 'reservable' => $item->reservable);
  }
  return $result;
}

/**
 * Implements provider availability, holdings.
 */
function fbs_availability_holdings($provider_ids) {
  $holdings = fbs_service()->Catalog->getHoldings(fbs_service()->agencyId, $provider_ids);
  $result = array();
  foreach ($holdings as $item) {
    $result[$item->recordId] = array(
      'reservable' => $item->reservable,
      // Gets properly set in the loop later.
      'available' => FALSE,
      'holdings' => array(),
      'total_count' => 0,
      // We don't know about this one.
      'is_internet' => FALSE,
      // And FBS can't tell us this.
      'reserved_count' => 0,
    );


    $placement_parts = array('branch', 'department', 'location', 'sublocation');
    foreach ($item->holdings as $item_holding) {
      $result_holding = array(
        'available_count' => 0,
        'total_count' => 0,
        // We have no idea about this either.
        'reference_count' => 0,
        'placement' => array(),
      );

      // Add in placement.
      foreach ($placement_parts as $part) {
        if (!empty($item_holding->{$part}->title)) {
          $result_holding['placement'][] = $item_holding->{$part}->title;
        }
      }

      // Count available materials.
      foreach ($item_holding->materials as $material) {
        $result[$item->recordId]['total_count']++;
        $result_holding['total_count']++;
        if ($material->available) {
          $result_holding['available_count']++;
          $result[$item->recordId]['available'] = TRUE;
        }
      }

      $result[$item->recordId]['holdings'][] = $result_holding;
    }
  }
  return $result;
}
