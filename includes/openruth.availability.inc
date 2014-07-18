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
 * @param bool $reset
 *   If TRUE the cache will be reset. Default FALSE.
 *
 * @return mixed
 *   An empty array, information about the holdings or even FALSE.
 */
function openruth_availability_holdings($provider_ids, $reset = FALSE) {
  $results = array();

  // Create cache id.
  $cid = md5(serialize($provider_ids));

  // Check the check to speed up the process, it's only cached for 10 min. to
  // ensure freshness.
  $cache = cache_get($cid, 'cache');
  if (!$reset && $cache && $cache->expire > REQUEST_TIME) {
    $results = $cache->data;
  }
  else {
    $details = openruth_client_invoke('get_holdings', $provider_ids);
    if (is_string($details->holding)) {
      watchdog('openruth', '@method error: “@message”', array('@method' => 'get_holdings', '@message' => $details->holding), WATCHDOG_ERROR);
    }
    else {
      if (is_array($details->holding)) {
        foreach ($details->holding as $holding) {
          // Find the holdings availability.
          $available = $holding->agencyHoldings->itemAvailability == 'copies available for loan and reservation';
          $reservable = $available || $holding->agencyHoldings->itemAvailability == 'no copies available, but item can be reserved';

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
                $holdings = _openruth_populate_holdings($item_holding);
                $data['total_count'] = $holdings['total_count'];
                $data['reservable_count'] = $holdings['reservable_count'];
                $data['holdings'] = $holdings['holdings'];
              }
            }
          }
          $results[$holding->itemId] = $data;
        }

        // Cache the result for 10 min. This will speed up materials with many
        // copies and loans.
        cache_set($cid, $results, 'cache', REQUEST_TIME + 600);
      }
    }
  }


  return $results;
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
    $banch_code = $holding['agencyBranchCode'];

    // First iteration or new branch code.
    if (!isset($unique_holdings[$banch_code])) {
      $unique_holdings[$banch_code] = $holding;
      continue;
    }

    // Same branch; increase copiesCount and copiesAvailableCount.
    $unique_holdings[$banch_code]['copiesCount'] += $holding['copiesCount'];
    $unique_holdings[$banch_code]['copiesAvailableCount'] += isset($holding['copiesAvailableCount']) ? $holding['copiesAvailableCount'] : 0;
  }
  return $unique_holdings;
}

/**
 * @TODO: What is this function used for ?
 */
function _openruth_populate_issues(&$holdings, $item_holding) {
  $issue = array(
    'local_id' => $item_holding->itemSerialPartId,
    'ordered_count' => $item_holding->ordersCount,
    'provider' => 'openruth',
  );

  $item_loc = isset($item_holding->itemLocation) ? $item_holding->itemLocation : $item_holding->itemComingLocation;

  foreach ($item_loc as $location) {
    $placement = array();
    if (isset($location->agencyBranchId->agencyBranchName)) {
      $placement[] = $location->agencyBranchId->agencyBranchName;
    }

    if (isset($location->agencyCollectionId->agencyCollectionName)) {
      $placement[] = $location->agencyCollectionId->agencyCollectionName;
    }

    if (isset($location->agencyPlacementId->agencyPlacementName)) {
      $placement[] = $location->agencyPlacementId->agencyPlacementName;
    }

    $issue['placement'][] = array(
      'location' => implode(' > ', $placement),
      'available_count' => isset($location->copiesAvailableCount) ? $location->copiesAvailableCount : 0,
      'total_count' => $location->copiesCount,
      'reservable' => $location->orderAllowed,
    );
  }

  // Handle year books.
  $issue_no = 0;
  if (isset($item_holding->itemSerialPartIssue)) {
    $issue_no = $item_holding->itemSerialPartIssue;
  }

  $holdings['issues'][$item_holding->itemSerialPartVolume][$issue_no] = $issue;
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
