<?php

/**
 * Implements provider availability, holdings.
 */
function openruth_availability_holdings($provider_ids) {
   $res = openruth_client_invoke('get_holdings', $provider_ids);
   if (is_string($res->holdings)) {
     watchdog('openruth', '@method error: “@message”', array('@method' => 'get_holdings', '@message' => $holdings), WATCHDOG_ERROR);
     return array();
   }
   return _openruth_get_holdings($res);
}

/**
 * @param $res; a json encoded response from openruth-client (get_holdings)
 * @return mixed; an array with holding-information OR an errorstring OR FALSE
 */
function _openruth_get_holdings($res)
{
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
 * @param $res; a json encoded response from openruth-client (get_holdings)
 * @return array; an array with holding-information
 */
function _openruth_set_holdings($res) {
  $holdings = array();
  foreach ($res->holding as $holding) {
    $h = _openruth_init_holding($holding);
    if (isset($holding->itemHoldings)) {
      foreach ($holding->itemHoldings as $itemHolding) {
	_openruth_set_locations($h, $itemHolding);
	_openruth_set_periodicals($h, $itemHolding);
      }
    }
    if (sizeof($h['issues'])) {
      $h['holdings'] = array_unique($h['holdings']);
    }
    
    // check if number of copies available (copiesAvailableCount) is > 0; if not set available to false
    if( $h['available'] && ($available < 1) ) {
      $h['available'] = FALSE;
    }

    $holdings[$holding->itemId] = $h;
  }
  return $holdings;
}

function _openruth_set_periodicals(&$h, $itemHolding) {
  if (isset($itemHolding->itemSerialPartId) ||
      isset($itemHolding->itemSerialPartVolume) ||
      isset($itemHolding->itemSerialPartIssue)) {
    $issue = array(
		   'local_id' => $itemHolding->itemSerialPartId,
		   'reservable' => $holding_reservable,
		   );
    $h['issues'][$itemHolding->itemSerialPartVolume][$itemHolding->itemSerialPartIssue] = $issue;
    // set flag for periodical
    $h['is_periodical'] = TRUE;
  }
}

/**
 * @param $holding; json encoded holdingpart from openruth-client (get_holdings)
 * @return array; holding array set with default values
 */
function _openruth_init_holding($holding) {
  if (isset($holding->agencyHoldings)){
    $available = $holding->agencyHoldings->itemAvailability == 'copies available for loan and reservation';
    $reservable = $available || $holding->agencyHoldings->itemAvailability == 'no copies available, but item can be reserved';
  }
  else {
    $available = FALSE;
    $reservable = FALSE;
  }
  $holding = 
    array('local_id' => $holding->itemId,
	  'available' => $available,
	  'reservable' => $reservable,
	  'show_reservation_button' => $reservable,
	  'holdings' => array(),
	  'holdings_available' => array(),
	  'reserved_count' => isset($holding->ordersCount) ? (int) $holding->ordersCount : 0,
	  'issues' => array(),
	  'is_periodical' => FALSE,);

  return $holding;
}


function _openruth_set_locations(&$h, $itemHolding) {
  $total = 0;
  $available = 0;

  $holding_reservable = FALSE;
  $fields = array('itemLocation', 'itemComingLocation');

  foreach ($fields as $field) {
    if (isset($itemHolding->{$field})){
      foreach ($itemHolding->{$field} as $itemLocation) {
	$data = array();

	$location_available = 0;

	if ($itemLocation->orderAllowed) {
	  $holding_reservable = TRUE;
	}
	$total += $itemLocation->copiesCount;

	$data['copiesCount'] = $itemLocation->copiesCount;

	if (isset($itemLocation->copiesAvailableCount)) {
	  $available += $itemLocation->copiesAvailableCount;
	  // pjo; 
	  $location_available += $itemLocation->copiesAvailableCount;

	  $data['copiesAvailableCount'] =  $itemLocation->copiesAvailableCount;

	}
	$parts = array();
	if (isset($itemLocation->agencyBranchId->agencyBranchName)) {
	  $parts[] = $itemLocation->agencyBranchId->agencyBranchName;
	  
	  $data['agencyBranchName'] = $itemLocation->agencyBranchId->agencyBranchName;

	}
	if (isset($itemLocation->agencyDepartmentId->agencyDepartmentName)) {
	  $parts[] = $itemLocation->agencyDepartmentId->agencyDepartmentName;

	  $data['agencyDepartmentName'] = $itemLocation->agencyDepartmentId->agencyDepartmentName;
	}
	if (isset($itemLocation->agencyCollectionId->agencyCollectionName)) {
	  $parts[] = $itemLocation->agencyCollectionId->agencyCollectionName;

	  $data['agencyCollectionName'] = $itemLocation->agencyCollectionId->agencyCollectionName;
	}
	if (isset($itemLocation->agencyPlacementId->agencyPlacementName)) {
	  $parts[] = $itemLocation->agencyPlacementId->agencyPlacementName;
	  
	  $data['agencyPlacementName'] = $itemLocation->agencyPlacementId->agencyPlacementName;
	}
	if ($parts) {
	  $data['placement'] = join(' → ', $parts);
	  // $h['holdings'][] = join(' → ', $parts);
	  $h['holdings'][] = $data;
	}
	if ($parts && $available && ($location_available > 0) ) {
	  $h['holdings_available'][] = join(' → ', $parts);		   
	}
      }
    }
  }
  $h['total_count'] = $total;
  $h['reservable_count'] = $available;
}
