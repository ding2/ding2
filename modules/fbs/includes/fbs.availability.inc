<?php
/**
 * @file
 * Handles availability information from the library system.
 */

/**
 * Implements provider availability, items.
 *
 * @param array $provider_ids
 *   Array of ting object ids (faust).
 *
 * @return array
 *   Avaliability info.
 */
function fbs_availability_items($provider_ids) {
  $avails = array();

  try {
    $avails = fbs_service()->Catalog->getAvailability(fbs_service()->agencyId, $provider_ids);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  $result = array();
  foreach ($avails as $item) {
    $result[$item->recordId] = array('available' => $item->available, 'reservable' => $item->reservable);
  }

  return $result;
}

/**
 * Implements provider availability, holdings.
 *
 * @param array $provider_ids
 *   Array of ting object ids (faust).
 *
 * @return array
 *   Holdings info.
 */
function fbs_availability_holdings($provider_ids) {
  $holdings = array();

  try {
    $holdings = fbs_service()->Catalog->getHoldings(fbs_service()->agencyId, $provider_ids);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  $result = array();
  $tmp_issues = array();
  foreach ($holdings as $item) {
    $result[$item->recordId] = array(
      'reservable' => $item->reservable,
      // Gets properly set in the loop later.
      'available' => FALSE,
      'holdings' => array(),
      'total_count' => 0,
      // We don't know about this one.
      'is_internet' => FALSE,
      'reserved_count' => $item->reservations,
      'is_periodical' => FALSE,
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
      $placement_string = implode(' > ', $result_holding['placement']);
      // Count available materials.
      foreach ($item_holding->materials as $material) {
        $result[$item->recordId]['total_count']++;
        $result_holding['total_count']++;
        if ($material->available) {
          $result_holding['available_count']++;
          $result[$item->recordId]['available'] = TRUE;
        }

        if ($material->periodical) {
          // Add to issues.
          $key = (!empty($material->periodical->volumeYear) ?
                  $material->periodical->volumeYear : '') . ':' .
               $material->periodical->volume . ':' .
               (!empty($material->periodical->volumeNumber) ?
               $material->periodical->volumeNumber : '') . ':' .
               $placement_string;
          if (isset($tmp_issues[$key])) {
            $tmp_issues[$key]['available'] += $material->available ? 1 : 0;
            $tmp_issues[$key]['total'] += 1;
          }
          else {
            $tmp_issues[$key] = array(
              'vol' => $material->periodical->volume . (!empty($material->periodical->volumeNumber) ? '-' . $material->periodical->volumeNumber : ''),
              'year' => $material->periodical->volumeYear,
              'available' => $material->available ? 1 : 0,
              'total' => 1,
              'placement' => $placement_string,
              'local_id' => _fbs_periodical_get_local_id($item->recordId, $material->periodical),
            );
          }
        }
      }

      $result[$item->recordId]['holdings'][] = $result_holding;
    }

    // Add issues in the right nesting.
    if (!empty($tmp_issues)) {
      $issues = array();
      $result[$item->recordId]['is_periodical'] = TRUE;
      foreach ($tmp_issues as $issue) {
        if (!isset($issues[$issue['year']])) {
          $issues[$issue['year']] = array();
        }

        $year = &$issues[$issue['year']];

        if (!isset($year[$issue['vol']])) {
          $year[$issue['vol']] = array(
            'local_id' => $issue['local_id'],
            'placement' => array(),
          );
        }
        $year[$issue['vol']]['placement'][] = array(
          'reservable' => $item->reservable,
          'available_count' => $issue['available'],
          'location' => $issue['placement'],
          'total_count' => $issue['total'],
        );
      }
      $result[$item->recordId]['issues'] = $issues;
    }

  }

  return $result;
}
