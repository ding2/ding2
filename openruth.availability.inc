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
    if( $h['is_periodical'] ) {
      $h['holdings'] = _openruth_periodicals_unique_holdings($h['holdings']);
    }
    _openruth_set_table_html($h);
    $holdings[$holding->itemId] = $h;
  }
  return $holdings;
}

/**
 * @param $holding; json encoded holdingpart from openruth-client (get_holdings)
 * @return array; initialized holding array set with default values
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
	  'total_count' => 0,
	  'reservable_count' => 0,
	  'issues' => array(),
	  'is_periodical' => FALSE,);

  // check if number of copies available (copiesAvailableCount) is > 0; if not set available to false
  if( $holding['available'] && ($available < 1) ) {
    $holding['available'] = FALSE;
  }

  // pjo; while developing
  $holding['available'] = TRUE;

  return $holding;
}

/**
 * make a html-table
 * @params $h; holding information for a given material
 * @return; a html table
 */
function _openruth_set_table_html( &$h ) {
  // set a classname for styling the table
  $variables['attributes']=
    array('class'=>array(drupal_html_class('availability_holdings_table')));
  // set table header
  $variables['header'] = 
    array('branch'=>t('Branch'), 'copies'=>t('Copies'), 'Home'=>t('At home'),);
  // set table rows
  $variables['rows'] = _openruth_set_rows($h);    
  // theme the table
  // @TODO; move this to ding_availability ??
  $html = theme('table',$variables );

  $h['html'] = $html;
}

/**
 * set table rows for given holdings
 * @param $h; holding information for a given material
 * @return array; an array for rendering
 */
function _openruth_set_rows( $h ) {
  $rows = array();
  if( isset($h['holdings']) ) {
    foreach( $h['holdings'] as $key => $data ) {
      $row = array();
      $row['Library'] = $data['agencyBranchName'];
      $row['copies'] = $data['copiesCount'];
      $row['Home'] = $data['copiesAvailableCount'];
      $rows[] = $row;
    }
    // add last row (totals)
    $row = array();
    $row['data']['Library'] = t('Total');
    $row['data']['Copies'] = $h['total_count'];
    $row['data']['Home'] = $h['reservable_count'];
    $row['class'] = array(drupal_html_class('availability_holdings_last_row'));
    $rows[] = $row;
  }
  return $rows;
}

/**
 * special method for periodicals. iterate holdings and make a unique entry for each branch
 * @param; $holdings; array of holdings for a periodical
 * @return; array; with unique holdings for each branch
 */
function _openruth_periodicals_unique_holdings( $holdings ) {
  $uh = array();
  foreach( $holdings as $holding ) {
    $key = $holding['agencyBranchCode'];
    // first iteration or new branchcode
    if( empty($uh) || !isset($uh[$key]) ) {
      $uh[$key] = $holding;
      continue;
    }
    // same branch; increase copiesCount and copiesAvailableCount
      $uh[$key]['copiesCount'] += $holding['copiesCount'];
      $uh[$key]['copiesAvailableCount'] += $holding['copiesAvailableCount'];
  }  
  return $uh;
}

/**
 *
 */
function _openruth_set_periodicals(&$h, $itemHolding) {
  if (isset($itemHolding->itemSerialPartId) ||
      isset($itemHolding->itemSerialPartVolume) ||
      isset($itemHolding->itemSerialPartIssue)) {

    $issue = array(
		   'local_id' => $itemHolding->itemSerialPartId,
		   'reservable' => $itemHolding->itemLocation[0]->orderAllowed,
		   );
    $h['issues'][$itemHolding->itemSerialPartVolume][$itemHolding->itemSerialPartIssue] = $issue;
    // set flag for periodical
    $h['is_periodical'] = TRUE;
  }
}


function _openruth_set_locations(&$h, $itemHolding) {
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
	//$total += $itemLocation->copiesCount;
	$h['total_count'] += $itemLocation->copiesCount;

	$data['copiesCount'] = $itemLocation->copiesCount;

	if (isset($itemLocation->copiesAvailableCount)) {
	  //$available += $itemLocation->copiesAvailableCount;
	  $h['reservable_count'] += $itemLocation->copiesAvailableCount;
	  // pjo; 
	  $location_available += $itemLocation->copiesAvailableCount;

	  $data['copiesAvailableCount'] =  $itemLocation->copiesAvailableCount;

	}
	$parts = array();
	if (isset($itemLocation->agencyBranchId->agencyBranchName)) {
	  $parts[] = $itemLocation->agencyBranchId->agencyBranchName;
	  
	  $data['agencyBranchName'] = $itemLocation->agencyBranchId->agencyBranchName;
	  $data['agencyBranchCode'] = $itemLocation->agencyBranchId->agencyBranchCode;

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
}
