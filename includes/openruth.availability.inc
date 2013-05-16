<?php
/**
 * @file
 * Implements support for holdings and availability information from OpenRuth.
 */

/**
 * Implements provider availability, holdings.
 *
 * @param $provider_ids
 *  Array of provider ids that should be fetched information for.
 * @return mixed
 *  An empty array, information about the holdings or even FALSE.
 */
function openruth_availability_holdings($provider_ids) {
  $res = openruth_client_invoke('get_holdings', $provider_ids);
  if (is_string($res->holding)) {
    watchdog('openruth', '@method error: “@message”', array('@method' => 'get_holdings', '@message' => $res->holding), WATCHDOG_ERROR);
    return array();
  }

  return _openruth_get_holdings($res);
}

/**
 * Get information about holdings.
 *
 * @param $res
 *  A json encoded response from openruth-client (get_holdings).
 * @return mixed
 *  An array with holding-information OR an errorstring OR FALSE.
 */
function _openruth_get_holdings($res) {
  if (isset($res->agencyError)) {
    return $res->agencyError;
  }
  elseif (isset($res->holding)) {
    return _openruth_set_holdings($res);
  }
  else {
    return FALSE;
  }
}

/**
 *
 * @param $res
 *  A json encoded response from openruth-client (get_holdings).
 * @return array
 *  An array with holding-information.
 */
function _openruth_set_holdings($res) {
  $holdings = array();
  foreach ($res->holding as $holding) {
    $h = _openruth_init_holding($holding);
    $item_holdings = isset($holding->itemHoldings) ? $holding->itemHoldings : NULL;

    // For 1.1 version. Override the path.
    if (isset($holding->holdingAgency[0]->itemHoldings)) {
      $item_holdings = $holding->holdingAgency[0]->itemHoldings;
    }

    if (isset($item_holdings)) {
      foreach ($item_holdings as $item_holding) {
        // remember to count ordersCount
        $h['reserved_count'] += $item_holding->ordersCount;
        _openruth_set_locations($h, $item_holding);
        _openruth_set_periodicals($h, $item_holding);
      }
    }
    if ($h['is_periodical']) {
      $h['holdings'] = _openruth_periodicals_unique_holdings($h['holdings']);
    }
    _openruth_set_table_html($h);
    $holdings[$holding->itemId] = $h;
  }
  return $holdings;
}

/**
 *
 * @param $holding
 *  A JSON encoded holdingpart from openruth-client (get_holdings).
 * @return array
 *  Initialized holding array set with default values
 */
function _openruth_init_holding($holding) {
  $holdings = isset($holding->agencyHoldings) ? $holding->agencyHoldings : NULL;

  // For 1.1 version. Override the path.
  if (isset($holding->holdingAgency[0]->agencyHoldings)) {
    $holdings = $holding->holdingAgency[0]->agencyHoldings;
  }

  if (isset($holdings)) {
    $available = $holdings->itemAvailability == 'copies available for loan and reservation';
    $reservable = $available || $holdings->itemAvailability == 'no copies available, but item can be reserved';
  }
  else {
    $available = FALSE;
    $reservable = FALSE;
  }
  $holding = array(
    'local_id' => $holding->itemId,
    'available' => $available,
    'reservable' => $reservable,
    'show_reservation_button' => $reservable,
    'holdings' => array(),
    'holdings_available' => array(),
    'reserved_count' => isset($holding->ordersCount) ? (int) $holding->ordersCount : 0,
    'total_count' => 0,
    'reservable_count' => 0,
    'issues' => array(),
    'is_periodical' => FALSE,
  );

  // check if number of copies available (copiesAvailableCount) is > 0; if not set available to false
  if ($holding['available'] && ($available < 1)) {
    $holding['available'] = FALSE;
  }

  return $holding;
}

/**
 * Creates a html-table with availability information.
 *
 * @params $holdings
 *  Holding information for a given material
 */
function _openruth_set_table_html(&$holdings) {
  // Set a classname for styling the table.
  $variables['attributes'] = array(
    'class' => array(
      drupal_html_class('availability_holdings_table'),
    ),
  );

  // Set table header.
  $variables['header'] = array(
    'placement' => t('Placement'),
    'copies' => t('Copies'),
    'home' => t('At home'),
  );

  // Set table rows.
  $variables['rows'] = _openruth_set_rows($holdings);

  // Theme the table.
  // @TODO; move this to ding_availability ??
  $html = theme('table', $variables);

  $holdings['html'] = $html;
}

/**
 * Set table rows for given holdings.
 *
 * @param $holdings
 *  Holding information for a given material
 * @return array
 *  An array with tabel rows, which can be used by theme table.
 */
function _openruth_set_rows($holdings) {
  $rows = array();
  if (isset($holdings['holdings'])) {
    foreach ($holdings['holdings'] as $key => $data) {
      $row = array();
      $row['placement'] = $data['placement'];
      $row['copies'] = $data['copiesCount'];
      $row['home'] = $data['copiesAvailableCount'];
      $rows[] = $row;
    }

    // Add row (totals).
    $row = array();
    $row['data']['Library'] = t('Total');
    $row['data']['Copies'] = $holdings['total_count'];
    $row['data']['Home'] = $holdings['reservable_count'];
    $row['class'] = array(drupal_html_class('availability_holdings_last_row'));
    $rows[] = $row;

    // Add last row (reservations).
    $row = array();
    $row['data']['Library'] = t('Reservations');
    $row['data']['Copies'] = array('data' => $holdings['reserved_count'], 'colspan' => 2);
    $rows[] = $row;
  }

  return $rows;
}

/**
 * Special method for periodicals that iterate holdings and make a unique entry
 * for each branch.
 *
 * @param $holdings
 *  Array of holdings for a periodical.
 * @return array
 *  With unique holdings for each branch.
 */
function _openruth_periodicals_unique_holdings($holdings) {
  $uh = array();
  foreach ($holdings as $holding) {
    $key = $holding['agencyBranchCode'];

    // First iteration or new branchcode.
    if (empty($uh) || !isset($uh[$key])) {
      $uh[$key] = $holding;
      continue;
    }

    // Same branch; increase copiesCount and copiesAvailableCount.
    $uh[$key]['copiesCount'] += $holding['copiesCount'];
    $uh[$key]['copiesAvailableCount'] += isset($holding['copiesAvailableCount']) ? $holding['copiesAvailableCount'] : 0;
  }
  return $uh;
}

/**
 * @TODO: What is this function used for ?
 */
function _openruth_set_periodicals(&$holdings, $item_holding) {
  if (isset($item_holding->itemSerialPartId) || isset($item_holding->itemSerialPartVolume) || isset($item_holding->itemSerialPartIssue)) {
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

    // Set flag for periodical.
    $holdings['is_periodical'] = TRUE;
  }
}

/**
 * @TODO: What is this function used for ?
 *
 * @param type $holdings
 * @param type $item_holding
 */
function _openruth_set_locations(&$holdings, $item_holding) {
  $holding_reservable = FALSE;
  $fields = array('itemLocation', 'itemComingLocation');

  foreach ($fields as $field) {
    if (isset($item_holding->{$field})) {
      foreach ($item_holding->{$field} as $item_location) {
        $data = array();

        $location_available = 0;

        if ($item_location->orderAllowed) {
          $holding_reservable = TRUE;
        }

        // $total += $itemLocation->copiesCount;
        $holdings['total_count'] += $item_location->copiesCount;

        $data['copiesCount'] = $item_location->copiesCount;

        if (isset($item_location->copiesAvailableCount)) {
          // $available += $itemLocation->copiesAvailableCount;
          $holdings['reservable_count'] += $item_location->copiesAvailableCount;
          $location_available += $item_location->copiesAvailableCount;

          $data['copiesAvailableCount'] = $item_location->copiesAvailableCount;

        }

        $parts = array();
        if (isset($item_location->agencyBranchId->agencyBranchName)) {
          $parts[] = $item_location->agencyBranchId->agencyBranchName;

          $data['agencyBranchName'] = $item_location->agencyBranchId->agencyBranchName;
          $data['agencyBranchCode'] = $item_location->agencyBranchId->agencyBranchCode;

        }

        if (isset($item_location->agencyDepartmentId->agencyDepartmentName)) {
          $parts[] = $item_location->agencyDepartmentId->agencyDepartmentName;

          $data['agencyDepartmentName'] = $item_location->agencyDepartmentId->agencyDepartmentName;
        }

        if (isset($item_location->agencyCollectionId->agencyCollectionName)) {
          $parts[] = $item_location->agencyCollectionId->agencyCollectionName;

          $data['agencyCollectionName'] = $item_location->agencyCollectionId->agencyCollectionName;
        }

        if (isset($item_location->agencyPlacementId->agencyPlacementName)) {
          $parts[] = $item_location->agencyPlacementId->agencyPlacementName;

          $data['agencyPlacementName'] = $item_location->agencyPlacementId->agencyPlacementName;
        }

        if ($parts) {
          $data['placement'] = join(' → ', $parts);
          $holdings['holdings'][] = $data;
        }

        if ($parts && ($location_available > 0)) {
          $holdings['holdings_available'][] = join(' → ', $parts);
        }
      }
    }
  }
}
