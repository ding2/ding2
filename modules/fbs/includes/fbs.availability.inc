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
 *   Availability info.
 */
function fbs_availability_items($provider_ids) {
  $avails = array();

  try {
    $avails = fbs_service()->Catalog->getAvailability(fbs_service()->agencyId, $provider_ids, variable_get('fbs_holdings_branches_blacklist', array()));
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  $result = array();
  foreach ($avails as $item) {
    $result[$item->recordId] = array(
      'available' => $item->available,
      'reservable' => $item->reservable,
    );
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
    $holdings = fbs_service()->Catalog->getHoldings(fbs_service()->agencyId, $provider_ids, variable_get('fbs_holdings_branches_blacklist', array()));
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  module_load_include('inc', 'opensearch', 'opensearch.client');

  // Translate all the fausts to datawell pids at once.
  $datawell_pids = ding_provider_build_entity_id($provider_ids);

  // Find out with the types of objects we need and load them all at once.
  $entities = [];
  $suffix_type = variable_get('fbs_holdings_suffix_type', 'shelf_mark');
  if ($suffix_type == 'simple') {
    // Here the entities are keyed by local entity id, so build an array keyed
    // by datawell pids for easier access.
    foreach (ding_entity_load_multiple($datawell_pids) as $entity) {
      $entities[$entity->ding_entity_id] = $entity;
    }
  }
  elseif ($suffix_type == 'shelf_mark') {
    $entities = opensearch_get_objects_marcxchange($datawell_pids);
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

    $placement_parts = array(
      'branch',
      'department',
      'location',
      'sublocation',
      'materials',
    );
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

      // Add material description.
      $material_description = $item_holding->materials;
      if (variable_get('fbs_show_material_group', 0) && $material_description[0]) {
        $result_holding['placement'][] = $material_description[0]->materialGroupName;
      }

      if ($suffix_type == 'simple' && isset($entities[$datawell_pids[$item->recordId]])) {
        $entity = $entities[$datawell_pids[$item->recordId]];
        // Get DK5 classification.
        if ($classification = $entity->getClassification()) {
          $result_holding['placement'][] = $classification;
        }

        // Get inverted author.
        if ($creator = $entity->getInvertedCreators()) {
          $result_holding['placement'][] = $creator[0];
        }
      }
      elseif ($suffix_type == 'shelf_mark' && isset($entities[$datawell_pids[$item->recordId]])) {
        $entity = $entities[$datawell_pids[$item->recordId]];

        // For non-fiction and music a special prefix is used.
        $prefix = '';

        // The DK5 classification that we need to consider can both be present
        // in subfield 'm' and 'o' of field 652. So we extract them both here
        // for later use.
        $field652 = fbs_get_marc_field($entity, '652');
        $field652m = $field652o = '';
        // There can be multiple 652 fields each with their own subfields. It's
        // important that we use data from the same 652 field that we use the
        // classification from, so remember the index of the field we end up
        // using.
        $field652index = NULL;
        if (!empty($field652['m'])) {
          $field652m = reset($field652['m']);
          $field652index = key($field652['m']);
        }

        if (!empty($field652['o'])) {
          $field652o = reset($field652['o']);
          // We need to look in both 'm' and 'o' subfield for the 'sk' marker
          // but we only need to use data from one of the fields. We prefer the
          // 'm' subfield, but if for some reason there was no data we will use
          // the 'o' field. So in these cases use remember the index of 'o'.
          if (empty($field652['m'])) {
            $field652index = key($field652['o']);
          }
        }
        // Non-fiction: Look for the 'sk' marker in both 'm' and 'o' subfield.
        // If it's not present in any of these, we consider the material be to
        // be non-fiction and we should use the special prefix for non-fiction
        // materials.
        if ($field652m !== 'sk' && $field652o !== 'sk') {
          // DK5 classification. Prefer subfield 'm'. Fallback to 'o'.
          $prefix .= $field652m ? $field652m : $field652o;

          // Additional descriptors from the DK5 classification. Note that we
          // ensure to use data from the correct subfield where we also got the
          // DK5-classification from.
          if (!empty($field652['b'][$field652index])) {
            $prefix .= ' ' . $field652['b'][$field652index];
          }
          elseif (!empty($field652['a'][$field652index])) {
            $prefix .= ' ' . $field652['a'][$field652index];
            if (!empty($field652['h'][$field652index])) {
              $prefix .= ', ' . $field652['h'][$field652index];
            }
          }
        }
        // Music: Field 039.a is present on music materials, so we can use this
        // is an indicator.
        elseif ($field039a = fbs_get_marc_field($entity, '039', 'a')) {
          $prefix .= fbs_translate_marc($field039a, '039.a');

          // We'll also append additional subfields if present.
          if ($field039b = fbs_get_marc_field($entity, '039', 'b')) {
            $prefix .= ' ' . fbs_translate_marc($field039b, '039.b');
          }
        }

        // The shelf mark is generated from a prioritized list of candidates.
        $candidates = array(
          '100.a',
          '110.a',
          '239.t',
          '245.a',
        );

        if ($shelf_mark = fbs_pick_marc_field($entity, $candidates)) {
          $words = explode(' ', $shelf_mark);
          $shelf_mark = FALSE;

          // Prefer words marked with a special sign.
          foreach ($words as &$word) {
            $word = trim($word);
            if (strpos($word, '¤') === 0) {
              $shelf_mark = mb_substr($word, 1);
            }
          }

          // If no special mark; use the first word.
          if (!$shelf_mark) {
            $shelf_mark = array_values($words)[0];
          }

          // A neat little trick for mb_ucfirst:
          // http://stackoverflow.com/questions/2517947/ucfirst-function-for-multibyte-character-encodings#answer-14161325.
          $shelf_mark = mb_strtoupper(mb_substr($shelf_mark, 0, 1)) . mb_strtolower(mb_substr($shelf_mark, 1));
        }

        // Generate and append the final holdings suffix.
        $holdings_suffix = ($prefix ? $prefix . ' > ' : '') . $shelf_mark;
        $result_holding['placement'][] = $holdings_suffix;
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
        // ding_periodical does not like null values.
        $year = isset($issue['year']) ? $issue['year'] : '0';
        if (!isset($issues[$year])) {
          $issues[$year] = array();
        }

        $year_collection = &$issues[$year];

        $vol = !empty($issue['vol']) ? $issue['vol'] : '0';
        if (!isset($year_collection[$vol])) {
          $year_collection[$vol] = array(
            'local_id' => $issue['local_id'],
            'placement' => array(),
          );
        }
        $year_collection[$vol]['placement'][] = array(
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

/**
 *  Helper to get the value of the specified marc field.
 */
function fbs_get_marc_field($entity, $field, $subfield = NULL) {
  $value = $entity->getValue($field, $subfield);

  // Ensure single value returned if subfield is specified.
  if (isset($subfield) && is_array($value)) {
    $value = reset($value);
  }

  return $value ? $value : NULL;
}

/**
 * Helper function to pick marc subfield from a range of candidates.
 */
function fbs_pick_marc_field($entity, array $candidates) {
  foreach ($candidates as $candidate) {
    list($field, $subfield) = explode('.', $candidate);

    if ($field_value = fbs_get_marc_field($entity, $field, $subfield)) {
      return $field_value;
    }
  }
  return NULL;
}

/**
 * Tranlate a marc string code to a human readable label.
 */
function fbs_translate_marc($code, $field) {
  $translations = _fbs_get_marc_039a_translations();

  if ($field == '039.a') {
    $translations = _fbs_get_marc_039a_translations();
  }
  elseif ($field == '039.b') {
    // This field contains ISO 3166-1 alpha-2 country codes and we can use the
    // build in list from the Drupal.
    // See: http://www.kat-format.dk/danMARC2/Danmarc2.22.htm#pgfId=1574621
    include_once DRUPAL_ROOT . '/includes/locale.inc';
    $translations = country_get_list();
    $code = drupal_strtoupper($code);
  }

  return isset($translations[$code]) ? $translations[$code] : NULL;
}

/**
 * Helper function to hold marc field 039.a machine code translations.
 *
 * See: http://www.kat-format.dk/danMARC2/Danmarc2.22.htm#pgfId=1574621
 */
function _fbs_get_marc_039a_translations() {
  return array (
    'sam' => 'SAMLINGER',
    'mir' => 'MIDDELALDER/RENÆSSANCE',
    'mia' => 'MIDDELALDER/RENÆSSANCE. ANTOLOGIER',
    'avg' => 'AVANTGARDE',
    'ava' => 'AVANTGARDE. ANTOLOGIER',
    'ork' => 'ORKESTERMUSIK',
    'ora' => 'ORKESTERMUSIK. ANTOLOGIER',
    'kam' => 'KAMMERMUSIK',
    'kaa' => 'KAMMERMUSIK. ANTOLOGIER',
    'eti' => 'ET INSTRUMENT',
    'eta' => 'ET INSTRUMENT. ANTOLOGIER',
    'vok' => 'VOKALMUSIK',
    'voa' => 'VOKALMUSIK. ANTOLOGIERø',
    'opr' => 'OPERAER',
    'opa' => 'OPERAER. ANTOLOGIER',
    'otm' => 'OPERETTER/MUSICALS',
    'ota' => 'OPERETTER/MUSICALS. ANTOLOGIER',
    'new' => 'NEW AGE',
    'fol' => 'FOLKEMUSIK',
    'blu' => 'BLUES',
    'bla' => 'BLUES. ANTOLOGIER',
    'jaz' => 'JAZZ',
    'jaa' => 'JAZZ. ANTOLOGIER',
    'bef' => 'ROCK',
    'bea' => 'ROCK. ANTOLOGIER',
    'und' => 'UNDERHOLDNING',
    'dau' => 'DANSK UNDERHOLDNING',
    'fau' => '**FÆRØSK UNDERHOLDNING',
    'jul' => 'JULEMUSIK',
    'fil' => 'FILMMUSIK',
    'tes' => 'TESTPLADER',
    'mmo' => 'MUSIC MINUS ONE',
    'hib' => 'HISTORIER. BØRN',
    'mub' => 'MUSIK. BØRN',
  );
}
