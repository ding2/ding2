<?php
/**
 * Implements provider availability, holdings.
 */
function alma_availability_holdings($provider_ids) {
  $ids = join(',', $provider_ids);

  $holding_parts = array('branch', 'department', 'location', 'sublocation', 'collection');
  $details = alma_client_invoke('catalogue_record_detail', $ids);
  $org = alma_get_organisation();
  $result = array();
  if ($details && isset($details['records'])) {
    foreach ($details['records'] as $alma_id => $record) {
      $holding = array(
        'local_id' => $alma_id,
        'available' => ($record['available_count'] > 0),
        'reservable' => $record['show_reservation_button'],
        'show_reservation_button' => $record['show_reservation_button'],
        'reserved_count' => (int) $record['reservation_count'],
        'deferred_period' => FALSE,

    'is_periodical' => ($record['media_class'] == 'periodical'),
      );

      $total = $total_reservable = 0;

      // START periodicals
      if( $holding['is_periodical'] ) {
    $parts = array();
    $holding['holdings'] = array();
    foreach( $record['holdings'] as $volume => $issues ) {
      foreach($issues as $issue_no => $holds){
        $issue = array();
        $issue['branches'] = array();
        foreach( $holds as $key => $branch_holding) {

          if( !in_array( $branch_holding['branch_id'], $issue['branches'] ) ) {
        $issue['branches'][] = $branch_holding['branch_id'];
          }

          $issue['local_id'] = $branch_holding['reservable'];
          $issue['reservable'] = (($branch_holding['status'] == 'availableForLoan') &&
        ((int) $branch_holding['total_count'] - (int) $branch_holding['reference_count']));
          $issues_array[$volume][$issue_no] = $issue;

          if (in_array($branch_holding['collection_id'], array('karens', 'karens-'))) {
        $holding['deferred_period'] = TRUE;
          }

          $parts = array();
          $total += (int) $branch_holding['total_count'];
          // Reservable is total items minus reference (which cannot be
          // loaned).
          $reservable = (int) $branch_holding['total_count'] - (int) $branch_holding['reference_count'];
          $total_reservable += $reservable;
          foreach ($holding_parts as $part) {
        if (!empty($branch_holding[$part . '_id'])) {
          $parts[] = $org[$part][$branch_holding[$part . '_id']];
        }
          }

          if (!empty($branch_holding['shelf_mark'])) {
        // Shelf mark might have leading >, strip any and replace the rest
        // with the proper arrow.
        $parts[] = strtr(trim($branch_holding['shelf_mark'], " >\n\t"), array('>' => '→'));
          }

          $parts = array_filter($parts);

          if ($parts && $branch_holding['total_count'] > $branch_holding['checked_out_count']) {
        $branch_string = join(' → ', $parts);
        $holding['holdings_available'][] = $branch_string;
        if( !in_array($branch_string,$holding['holdings']) ) {
          $holding['holdings'][] = $branch_string;
        }
          }
        }
      }
    }
    if( is_array($holding['holdings']) ) {
      asort($holding['holdings']);
    }
    $holding['issues'] = $issues_array;
      } // END periodicals

      else {
    foreach ($record['holdings'] as $branch_holding) {
      if (in_array($branch_holding['collection_id'], array('karens', 'karens-'))) {
        $holding['deferred_period'] = TRUE;
      }

      $parts = array();
      $total += (int) $branch_holding['total_count'];
      // Reservable is total items minus reference (which cannot be
      // loaned).
      $reservable = (int) $branch_holding['total_count'] - (int) $branch_holding['reference_count'];
      $total_reservable += $reservable;
      foreach ($holding_parts as $part) {
        if (!empty($branch_holding[$part . '_id'])) {
          $parts[] = $org[$part][$branch_holding[$part . '_id']];
        }
      }

      if (!empty($branch_holding['shelf_mark'])) {
        // Shelf mark might have leading >, strip any and replace the rest
        // with the proper arrow.
        $parts[] = strtr(trim($branch_holding['shelf_mark'], " >\n\t"), array('>' => '→'));
      }

      $parts = array_filter($parts);

      if ($parts && $branch_holding['total_count'] > $branch_holding['checked_out_count']) {
        $holding['holdings'][] = join(' → ', $parts);
      }
    }
      }

      $holding['reservable_count'] = $total_reservable;
      $holding['total_count'] = $total;
      $result[$alma_id] = $holding;
    }
  }

  return $result;
}
