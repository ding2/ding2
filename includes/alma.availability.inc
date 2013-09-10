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
function alma_availability_holdings($provider_ids) {
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

      $result[$alma_id] = $holding;

      $result[$alma_id]['html'] = _alma_get_holdings($details, $holding['is_periodical']);
    }
  }
  return $result;

}

/**
 * Get holdings base information from alma and base on if it's a periodical or
 * not.
 *
 * @todo: Rewrite this to have the provider create the holdings tables and not
 *        return HTML from inside the provides them self.
 *
 * @param array $res
 *   Returned array from alma_client class
 * @param bool $is_periodical
 *   Indicates whether the shown record is a periodical or not
 *
 * @return string
 *   HTML to be shown or FALSE if no data is received from alma.
 */
function _alma_get_holdings($res, $is_periodical = FALSE) {
  if (isset($res['records'])) {
    if ($is_periodical) {
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
 * Set holdings for all kinds of material except periodicals.
 *
 * @param array $res
 *
 * @return array $result;
 */
function _alma_set_holdings($res) {
  $holdings = array();
  $reservation_count = 0;
  foreach ($res['records'] as $alma_id => $records) {
    $reservation_count += (int) $records['reservation_count'];
    foreach ($records['holdings'] as $holding) {
      $holdings[] = $holding;
    }
  }

  $result = _alma_set_table_html($holdings, $reservation_count);
  return $result;
}

/**
 * Set holdings if material is periodical only.
 *
 * @param array $res
 * @return array $result
 */
function _alma_set_holdings_periodical($res) {
  $holdings = array();
  $reservation_count = 0;
  foreach ($res['records'] as $alma_id => $records) {
    $reservation_count += (int) $records['reservation_count'];
    foreach ($records['holdings'] as $holding => $issue_year) {
      foreach ($issue_year as $key) {
        $holdings[] = $key[0];
      }
    }
  }

  $result = _alma_set_table_html($holdings, $reservation_count);
  return $result;
}

/**
 * Make the html-table.
 *
 * @param array $holding
 *   Holding information for a given material.
 *
 * @return html-table
 */
function _alma_set_table_html($holdings, $r_count) {
  // Set a classname for styling the table.
  $variables['attributes'] = array(
    'class' => array(
      drupal_html_class('availability_holdings_table')
    ),
  );

  // Set table header.
  $variables['header'] = array(
    'placement' => t('Placement'),
    'copies' => t('Copies'),
    'home' => t('At home'),
    'not_for_loan' => t('Not for loan'),
    'checked_out' => t('Checked out'),
  );

  // Set table rows.
  $variables['rows'] = _alma_set_rows($holdings);

  // Set last row with reservation count.
  $row = array();
  $row['data']['Library'] = t('Reservations');
  $row['data']['Copies'] = array('data' => $r_count, 'colspan' => 4);
  $variables['rows'][] = $row;

  // Disable sticky headers.
  $variables['sticky'] = FALSE;

  // Theme the table.
  $html = theme('table', $variables);

  return $html;
}

/**
 * Set rows in table for given holdings.
 *
 * @param $holdings
 *   Holding information for a given material
 *
 * @return array;
 */
function _alma_set_rows($holdings) {
  $rows = array();
  $org = alma_get_organisation();

  $copies_total = 0;
  $home_total = 0;
  $not_for_loan_total = 0;
  $checked_out_total = 0;

  foreach ($holdings as $key => $data) {
    $row = array();

    if (!empty($data['branch_id'])) {
      $row['placement'][] = $org['branch'][$data['branch_id']];
    }

    if (!empty($data['department_id'])) {
      $row['placement'][] = $org['department'][$data['department_id']];
    }

    if (!empty($data['location_id'])) {
      $row['placement'][] = $org['location'][$data['location_id']];
    }

    if (!empty($data['sublocation_id'])) {
      $row['placement'][] = $org['sublocation'][$data['sublocation_id']];
    }

    if (!empty($data['shelf_mark'])) {
      $row['placement'][] = $data['shelf_mark'];
    }

    $row['placement'] = implode(' > ', $row['placement']);

    $row['copies'] = isset($data['total_count']) ? (int) $data['total_count'] : 0;
    $copies_total += $row['copies'];

    $row['home'] = isset($data['available_count']) ? (int) $data['available_count'] : 0;
    $home_total += $row['home'];

    $row['not_for_loan'] = isset($data['reference_count']) ? (int) $data['reference_count'] : 0;
    $not_for_loan_total += $row['not_for_loan'];

    $row['checked_out'] = isset($data['checked_out_count']) ? (int) $data['checked_out_count'] : 0;
    $checked_out_total += $row['checked_out'];

    $rows[] = $row;
  }

  if (count($rows) >= 1) {
    $rows = _clean_up_rows($rows);
  }
  // Adding row - totals.
  $row = array();
  $row['data']['Library'] = t('Total');
  $row['data']['Copies'] = $copies_total;
  $row['data']['Home'] = $home_total;
  $row['data']['Not for loan'] = $not_for_loan_total;
  $row['data']['Checked out'] = $checked_out_total;
  $row['class'] = array(drupal_html_class('availability_holdings_last_row'));
  $rows[] = $row;

  return $rows;
}

/**
 * If the same placement exists several times collect them in one line.
 *
 * @param array
 *
 * @return array
 */
function _clean_up_rows($_rows) {
  $rows = array();
  $placements = array();

  foreach ($_rows as $row) {
    $currkey = $row['placement'];
    if (!in_array($currkey, $placements)) {
      $placements[] = $currkey;
      $placementsarr = _get_placements_with_key($_rows, $currkey);
      $this_row = _sum_placement($placementsarr);
      $rows[] = $this_row;
    }
  }
  return $rows;
}

/**
 * Collect materials with the same placement.
 *
 * @param array $_rows
 * @param String $currkey
 *
 * @return array $rows;
 */
function _get_placements_with_key($_rows, $currkey) {
  $rows = array();
  foreach ($_rows as $key) {
    if ($key['placement'] == $currkey) {
      $rows[] = $key;
    }
  }
  return $rows;
}

/**
 * Sum material for same placement in one row.
 *
 * @param array $placementsarr
 *  All instances of the same placement - ie. 'Hovedbiblioteket'.
 *
 * @return array $row
 */
function _sum_placement($placementsarr) {
  $row = $placementsarr[0];
  for ($i = 1; $i < count($placementsarr); $i++) {
    $next_row = $placementsarr[$i];
    $row['copies'] += $next_row['copies'];
    $row['home'] += $next_row['home'];
    $row['not_for_loan'] += $next_row['not_for_loan'];
    $row['checked_out'] += $next_row['checked_out'];
  }
  return $row;
}

/**
 * Fill in the issues data, useful for periodical availability.
 *
 * This method takes into consideration the repeating placements,
 * and aggregates them, suming the numeric data.
 *
 * @param $input
 *   Holdings data, as returned from the web-servce.
 * @return
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

  // Numeric info about the issue.
  $ordered_count = 0;
  $checked_out_count = 0;
  $reference_count = 0;
  $total_count = 0;
  $available_count = 0;

  $i = -1;
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
          'reservable' => ($copy['status'] === 'availableForLoan') ? TRUE : FALSE,
        );
      }
    }
  }

  return $output;
}
