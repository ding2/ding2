<?php
/**
 * @file
 * Implements support for holdings and availability information from OpenRuth.
 */

/**
 * Implements provider availability, holdings.
 *
 * @param array $provider_ids
 *   Array of provider ids that should be fetched information for.
 *
 * @return mixed
 *   An empty array, information about the holdings or even FALSE.
 */
function openruth_availability_holdings($provider_ids) {
  $holdings = array();

  $details = openruth_client_invoke('get_holdings', $provider_ids);
  if (is_string($details->holding)) {
    watchdog('openruth', '@method error: “@message”', array('@method' => 'get_holdings', '@message' => $details->holding), WATCHDOG_ERROR);
  }
  else {
    if (is_array($details->holding)) {
      foreach ($details->holding as $holding) {
        // Find the holdings availability.
        $available = FALSE;
        $reservable = FALSE;
        if (isset($holding)) {
          $available = $holding->agencyHoldings->itemAvailability == 'copies available for loan and reservation';
          $reservable = $available || $holding->agencyHoldings->itemAvailability == 'no copies available, but item can be reserved';
        }

        $data = array(
          'local_id' => $holding->itemId,
          'available' => $available,
          'reservable' => $reservable,
          'show_reservation_button' => $reservable,
          'holdings' => array(),
          'reserved_count' => 0,
          'deferred_period' => FALSE,
          'issues' => array(),
          'is_periodical' => FALSE,
          'is_internet' => FALSE,
        );

        if (isset($holding->itemHoldings)) {
          foreach ($holding->itemHoldings as $item_holding) {
            // Add reservation count.
            $data['reserved_count'] += $item_holding->ordersCount;

            // Check if it's a periodical.
            if (isset($item_holding->itemSerialPartId) || isset($item_holding->itemSerialPartVolume) || isset($item_holding->itemSerialPartIssue)) {
              $data['is_periodical'] = TRUE;
              _openruth_populate_issues($data, $item_holding);
              $data['holdings'] = _openruth_periodicals_unique_holdings($data['holdings']);
            }
            else {
              // Parse holdings information.
              $stats = _openruth_populate_holdings($item_holding);;
              $data['total_count'] = $stats['holdings'];
              $data['reservable_count'] = $stats['holdings'];
              $data['holdings'] = $stats['holdings'];
            }
          }
        }
        $holdings[$holding->itemId] = $data;
      }
    }
  }

  return $holdings;
}

/**
 * Special method for periodicals that iterate holdings and make a unique entry
 * for each branch.
 *
 * @param $holdings
 *   Array of holdings for a periodical.
 * @return array
 *   With unique holdings for each branch.
 */
function _openruth_periodicals_unique_holdings($holdings) {
  $unique_holdings = array();
  foreach ($holdings as $holding) {
    $key = $holding['agencyBranchCode'];

    // First iteration or new branch code.
    if (empty($unique_holdings) || !isset($unique_holdings[$key])) {
      $unique_holdings[$key] = $holding;
      continue;
    }

    // Same branch; increase copiesCount and copiesAvailableCount.
    $unique_holdings[$key]['copiesCount'] += $holding['copiesCount'];
    $unique_holdings[$key]['copiesAvailableCount'] += isset($holding['copiesAvailableCount']) ? $holding['copiesAvailableCount'] : 0;
  }
  return $unique_holdings;
}

/**
 * @TODO: What is this function used for ?
 */
function _openruth_populate_issues(&$holdings, $item_holding) {
  $issue = array(
    'local_id' => $item_holding->itemSerialPartId,
    'orders_count' => $item_holding->ordersCount,
    'provider' => 'openruth',
  );

  $item_loc = isset($item_holding->itemLocation) ? $item_holding->itemLocation : $item_holding->itemComingLocation;

  foreach ($item_loc as $location) {
    $loc = array();
    if (isset($location->agencyBranchId->agencyBranchName)) {
      $loc[] = $location->agencyBranchId->agencyBranchName;
    }

    if (isset($location->agencyCollectionId->agencyCollectionName)) {
      $loc[] = $location->agencyCollectionId->agencyCollectionName;
    }

    if (isset($location->agencyPlacementId->agencyPlacementName)) {
      $loc[] = $location->agencyPlacementId->agencyPlacementName;
    }

    $issue['placement'][] = array(
      'location' => implode(' > ', $loc),
      'available_count' => isset($location->copiesAvailableCount) ? $location->copiesAvailableCount : 0,
      'total_count' => $location->copiesCount,
      'reservable' => $location->orderAllowed,
    );
  }

  $holdings['issues'][$item_holding->itemSerialPartVolume][$item_holding->itemSerialPartIssue] = $issue;
}

/**
 * Helper function to build holdings information for a given location (branch).
 *
 * @param StdClass $item_holding
 *   Holdings information about the material (item).
 *
 * @return array
 *   Holdings information indexed to match ding_availability.
 */
function _openruth_populate_holdings($item_holding) {
  $holdings = array();
  $total_count = 0;
  $reservable_count = 0;

  foreach (array('itemLocation', 'itemComingLocation') as $field) {
    if (isset($item_holding->{$field})) {
      foreach ($item_holding->{$field} as $location) {
        // Add to total count for the material.
        $total_count += isset($location->copiesCount) ? $location->copiesCount : 0;
        $reservable_count += isset($location->copiesAvailableCount) ? $location->copiesAvailableCount : 0;

        // Set holdings for the location.
        $data = array(
          'total_count' => isset($location->copiesCount) ? $location->copiesCount : 0,
          'available_count' => isset($location->copiesAvailableCount) ? $location->copiesAvailableCount : 0,
          'placement' => array(),
        );

        // Build the placement array.
        if (isset($location->agencyBranchId->agencyBranchName)) {
          $data['placement'][] = $location->agencyBranchId->agencyBranchName;
        }

        if (isset($location->agencyDepartmentId->agencyDepartmentName)) {
          $data['placement'][] = $location->agencyDepartmentId->agencyDepartmentName;
        }

        if (isset($location->agencyCollectionId->agencyCollectionName)) {
          $data['placement'][] = $location->agencyCollectionId->agencyCollectionName;
        }

        if (isset($location->agencyPlacementId->agencyPlacementName)) {
          $data['placement'][] = $location->agencyPlacementId->agencyPlacementName;
        }

        // Add the location information to holdings.
        $holdings[] = $data;
      }
    }
  }

  return array(
    'total_count' => $total_count,
    'reservable_count' => $reservable_count,
    'holdings' => $holdings,
  );
}
