<?php

/**
 * Implements provider availability, holdings.
 */
 
function alma_availability_holdings($provider_ids) {
  $ids = join(',', $provider_ids);
  $details = alma_client_invoke('catalogue_record_detail', $ids);
  $result = array();
  
  if ($details && isset($details['records'])) {
    foreach ($details['records'] as $alma_id => $record) {
      $holding = array(
        'local_id' => $alma_id,
        'available' => ($record['available_count'] > 0),
        'reservable' => $record['show_reservation_button'],
        'show_reservation_button' => $record['show_reservation_button'],
        'holdings' => array(),
        'holdings_available' => array(),
        'reserved_count' => (int) $record['reservation_count'],
        'total_count' => 0,
        'deferred_period' => FALSE,
        'issues' => array(),
        'is_periodical' => ($record['media_class'] == 'periodical'),
      );
      
      $result[$alma_id] = $holding;
      
      $result[$alma_id]['html'] = _alma_get_holdings($details, $holding['is_periodical']);
    }
  }
  return $result;
  
}

/**
 * @param type $res; returned array from alma_client class
 * @param type $is_periodical; Boolean that indicates whether the shown record is a periodical or not
 * @return html to be shown. Returns FALSE if no data is received from alma_client class
 */
function _alma_get_holdings($res, $is_periodical = FALSE) {
  if(isset($res['records'])) {
    if($is_periodical){
      return _alma_set_holdings_periodical($res);
    }
    else {
      return _alma_set_holdings($res);
    }
  }
  else {
    return FALSE;
  }
}

  /**
   * set holdings for all kinds of material except periodicals
   * @param array $res
   * @return array $result; 
   */
function _alma_set_holdings($res) {
  $holdings = array();
  foreach ($res['records'] as $alma_id => $records) {
    foreach ($records['holdings'] as $holding) {
      $holdings[] = $holding;
    }
  }
  
  $result = _alma_set_table_html($holdings);
  return $result;
}

  /**
   * set holdings if material is periodical only
   * @param array $res
   * @return array $result 
   */
function _alma_set_holdings_periodical($res){
  $holdings = array();
  foreach ($res['records'] as $alma_id => $records) {
    foreach ($records['holdings'] as $holding => $issue_year) {
      foreach ($issue_year as $key) {
        $holdings[] = $key[0];
      }
    }
  }
  
  $result = _alma_set_table_html($holdings);
  return $result;
}
  /**
   * Make the html-table
   * @params $h; holding information for a given material
   * @return html-table
   */
function _alma_set_table_html($h) {
  // set a classname for styling the table
  $variables['attributes']=
    array('class'=>array(drupal_html_class('availability_holdings_table')));
  // set table header
  $variables['header'] = 
    array('placement'=>t('Placement'), 'copies'=>t('Copies'), 'Home'=>t('At home'),'reservations'=>t('Reservations'));
  // set table rows
  $variables['rows'] = _alma_set_rows($h);    
  // theme the table
  // @TODO; move this to ding_availability ??
  $html = theme('table',$variables );

  return $html;
}

  /**
   * set rows in table for given holdings
   * @param $h; holding information for a given material
   * @return array; 
   */
function _alma_set_rows($h) {
  $rows = array();
  $org = alma_get_organisation();
  
  $copies_total = 0;
  $home_total = 0;
  $reservations_total = 0;
  foreach ($h as $key => $data) {
    $row = array();
    $row['placement'] = $org['branch'][$data['branch_id']];
    
    if(!empty($data['department_id'])){
      $row['placement'] = $row['placement'] .' → '. $org['department'][$data['department_id']];
    }
    
    if(!empty($data['collection_id'])){
      $row['placement'] = $row['placement'] .' → '. $org['collection'][$data['collection_id']];
    }
    
    $row['copies'] = (int) $data['total_count'];
    $copies_total += $row['copies'];
    $row['home'] = (int) $data['available_count'];
    $home_total += $row['home'];
    $row['reservations'] = (int) $data['ordered_count'];
    $reservations_total += $row['reservations'];
    $rows[] = $row; 
  }
  
  if(count($rows) >= 1){
    $rows = _clean_up_rows($rows);
  }
  //Adding last row - totals
  $row = array();
  $row['data']['Library'] = t('Total');
  $row['data']['Copies'] = $copies_total;
  $row['data']['Home'] = $home_total;
  $row['data']['Reservations'] = $reservations_total;
  $row['class'] = array(drupal_html_class('availability_holdings_last_row'));
  $rows[] = $row;
  return $rows;
}

  /**
  * if the same placement exists several times collect them in one line
  * @param array
  * @return array;
  */
function _clean_up_rows($_rows) {
  $rows = array();
  $placements = array();
  
  foreach ($_rows as $row) {
    $currkey = $row['placement'];
    if(!in_array($currkey, $placements)){
      $placements[] = $currkey;
      $placementsarr = _get_placements_with_key($_rows, $currkey);
      $this_row = _sum_placement($placementsarr);
      $rows[] = $this_row;
    }
  }
  return $rows;
}

  /**
   * collect materials with the same placement
   * @param array $_rows
   * @param String $currkey
   * @return array $rows; 
   */
function _get_placements_with_key($_rows, $currkey){
  $rows = array();
  foreach ($_rows as $key) {
    if($key['placement'] == $currkey){
      $rows[] = $key;
    }
  }
  return $rows;
}
  /**
   * sum material for same placement in one row
   * @param $placementsarr; array with all instances of the same placement - ie. 'Hovedbiblioteket'
   * @return array; $row 
   */
function _sum_placement($placementsarr){
  $row = $placementsarr[0];
  for($i = 1; $i < count($placementsarr);$i++){
    $next_row = $placementsarr[$i];
    $row['copies'] += $next_row['copies'];
    $row['home'] += $next_row['home'];
    $row['reservations'] += $next_row['reservations'];
  }
  return $row;
}