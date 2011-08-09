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
        'available' => $record['available_count'] > 0,
        'reservable' => $record['show_reservation_button'],
        'show_reservation_button' => $record['show_reservation_button'],
        'reserved_count' => (int) $record['reservation_count'],
        'deferred_period' => FALSE,
        'holdings' => array(),
      );
      $total = $total_reservable = 0;

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

      $holding['reservable_count'] = $total_reservable;
      $holding['total_count'] = $total;
      $result[$alma_id] = $holding;
    }
  }

  return $result;
}