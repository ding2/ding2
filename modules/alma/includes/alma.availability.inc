<?php
/**
 * @file
 * Handles availability information from the library system.
 */

/**
 * Implements provider availability, items.
 */
function alma_availability_items($provider_ids) {
  $ids = implode(',', $provider_ids);
  $result = alma_client_invoke('get_availability', $ids);
  if (!$result) {
    $result = array();
  }

  return $result;
}
/**
 * Implements provider availability, holdings.
 */
function alma_availability_holdings($provider_ids, $reset = FALSE) {
  // Create cache id.
  $cid = md5(serialize($provider_ids));

  // Check the check to speed up the process, it's only cached for 10 min. to
  // ensure freshness.
  $cache = cache_get($cid, 'cache');
  if (!$reset && $cache && $cache->expire > REQUEST_TIME) {
    $result = $cache->data;
  }
  else {
    $ids = implode(',', $provider_ids);
    $details = alma_client_invoke('catalogue_record_detail', $ids);
    $result = array();

    if ($details && isset($details['records'])) {
      foreach ($details['records'] as $alma_id => $record) {
        $holding = array(
          'local_id' => $alma_id,
          'title' => $record['titles'][0],
          'available' => ($record['available_count'] > 0),
          'reservable' => $record['show_reservation_button'],
          'show_reservation_button' => $record['show_reservation_button'],
          'holdings' => $record['holdings'],
          'reserved_count' => (int) $record['reservation_count'],
          'deferred_period' => FALSE,
          'issues' => FALSE,
          'is_periodical' => ($record['media_class'] == 'periodical'),
          'is_internet' => ($record['media_class'] == 'internet'),
        );

        // If periodical render issue information.
        if ($holding['is_periodical']) {
          $holding['issues'] = _alma_populate_issues($record['holdings']);
        }

        // If it's an internet holding, don't display holdings information.
        if ($holding['is_internet']) {
          $holding['holdings'] = FALSE;
        }

        // Get pretty location name (placement) as an array.
        if (isset($holding['holdings'])) {
          $org = alma_get_organisation();
          foreach ($holding['holdings'] as $index => $data) {
            $holding['holdings'][$index]['placement'] = array();

            if (!empty($data['branch_id'])) {
              $holding['holdings'][$index]['placement'][] = $org['branch'][$data['branch_id']];
            }

            if (!empty($data['department_id'])) {
              $holding['holdings'][$index]['placement'][] = $org['department'][$data['department_id']];
            }

            if (!empty($data['location_id'])) {
              $holding['holdings'][$index]['placement'][] = $org['location'][$data['location_id']];
            }

            if (!empty($data['sublocation_id'])) {
              $holding['holdings'][$index]['placement'][] = $org['sublocation'][$data['sublocation_id']];
            }

            if (!empty($data['collection_id'])) {
              $holding['holdings'][$index]['placement'][] = $org['collection'][$data['collection_id']];
            }

            if (!empty($data['shelf_mark'])) {
              $holding['holdings'][$index]['placement'][] = $data['shelf_mark'];
            }
          }
        }

        // Count total materials.
        $holding['total_count'] = _alma_holdings_total_count($holding['holdings']);

        // Set holdings.
        $result[$alma_id] = $holding;
      }

      // Cache the result for 10 min. This will speed up materials with many
      // copies and loans.
      cache_set($cid, $result, 'cache', REQUEST_TIME + 600);
    }
  }

  return $result;
}

/**
 * Sums the total number of materials from holdings information.
 *
 * @param array $holdings
 *   Holdings information return form alma.
 *
 * @return int
 *   Total number of materials in the holding.
 */
function _alma_holdings_total_count($holdings) {
  $total = 0;
  foreach ($holdings as $holding) {
    if (isset($holding['total_count'])) {
      $total += (int) $holding['total_count'];
    }
  }

  return $total;
}

/**
 * Fill in the issues data, useful for periodical availability.
 *
 * This method takes into consideration the repeating placements,
 * and aggregates them, summing the numeric data.
 *
 * @param array $input
 *   Holdings data, as returned from the web-service.
 *
 * @return array
 *   An array, with the following keys:
 *   - Issue year.
 *     - Issue number.
 *       - local_id: Periodical identifier.
 *       - provider: Provider identifier, 'alma' here.
 *       - placement: Item placement info.
 *         - location: Actual location string.
 *         - ordered_count
 *         - checked_out_count
 *         - reference_count
 *         - total_count
 *         - available_count
 *         - reservable
 */
function _alma_populate_issues($input) {
  $org = alma_get_organisation();
  $output = array();
  $prev_hash = '';

  // Loop through volumes.
  foreach ($input as $year => $volume) {
    // Loop through issues.
    foreach ($volume as $key => $issues) {
      $ordered_count = 0;
      $checked_out_count = 0;
      $reference_count = 0;
      $total_count = 0;
      $available_count = 0;
      $output[$year][$key]['local_id'] = isset($issues[0]['reservable']) ? $issues[0]['reservable'] : '';
      $output[$year][$key]['provider'] = 'alma';
      $i = 0;
      // Loop though placements.
      foreach ($issues as $copy) {
        $placement = array();
        $branch_id = !empty($copy['branch_id']) ? $copy['branch_id'] : '';
        $department_id = !empty($copy['department_id']) ? $copy['department_id'] : '';
        $location_id = !empty($copy['location_id']) ? $copy['location_id'] : '';
        $sublocation_id = !empty($copy['sublocation_id']) ? $copy['sublocation_id'] : '';
        $shelf_mark = !empty($copy['shelf_mark']) ? $copy['shelf_mark'] : '';

        if (!empty($branch_id)) {
          $placement[] = $org['branch'][$branch_id];
        }

        if (!empty($department_id)) {
          $placement[] = $org['department'][$department_id];
        }

        if (!empty($location_id)) {
          $placement[] = $org['location'][$location_id];
        }

        if (!empty($sublocation_id)) {
          $placement[] = $org['sublocation'][$sublocation_id];
        }

        if (!empty($shelf_mark)) {
          $placement[] = $shelf_mark;
        }

        $placement_string = implode(' > ', $placement);

        // A hash value, used for recognizing differences in placement.
        $hash = md5($branch_id . $department_id . $location_id . $sublocation_id . $shelf_mark);

        // Whether it's a new placement, start a new count and increment the
        // row counter.
        if ($hash !== $prev_hash) {
          $prev_hash = $hash;
          $ordered_count = 0;
          $checked_out_count = 0;
          $reference_count = 0;
          $total_count = 0;
          $available_count = 0;
          $i++;
        }

        // The numeric data keeps summing each other, until
        // we get a new placement.
        $ordered_count += $copy['ordered_count'];
        $checked_out_count += $copy['checked_out_count'];
        $reference_count += $copy['reference_count'];
        $total_count += $copy['total_count'];
        $available_count += $copy['available_count'];

        $output[$year][$key]['placement'][$i] = array(
          'location' => $placement_string,
          'ordered_count' => $ordered_count,
          'checked_out_count' => $checked_out_count,
          'reference_count' => $reference_count,
          'total_count' => $total_count,
          'available_count' => $available_count,
          'reservable' => ($copy['show_reservation_button'] === 'yes') ? TRUE : FALSE,
        );
      }
    }
  }

  return $output;
}
