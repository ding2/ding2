<?php

/**
 * @file
 * A script to parse the raw search files from Webtrekk via KPI index.
 */

try {
  $search_data = array();
  $file = fopen('./search_feed.csv', 'r');
  while (($line = fgetcsv($file, 1000, ",")) !== FALSE) {
    $search_key = $line[2];
    $number_of_searches = $line[3];
    if (!((strpos($search_key, '=') !== false) || (strpos($search_key, '(') !== false))) {
      if (ting_smart_search_is_from_period($line, 52)) {
        if (array_key_exists($search_key, $search_data) && is_numeric($number_of_searches)) {
          $search_data[$search_key]['long_period'] += $number_of_searches;
        }
        else {
          $search_data[$search_key] = array('long_period' => $number_of_searches, 'short_period' => 0);
        }
        if (ting_smart_search_is_from_period($line, 4)) {
          $search_data[$search_key]['short_period'] += $number_of_searches;
        }
      }
    }
  }
  uasort($search_data, 'ting_smart_search_sort_search_data');
  $search_data = array_slice($search_data, 0, 5000);
  $fp = fopen('searchdata.csv', 'w');

  foreach ($search_data as $search_key => $data) {
    $line = array($search_key, $data['long_period'], $data['short_period']);
    fputcsv($fp, $line);
  }

  fclose($fp);
  ting_smart_search_write_to_feedlog("Feed data succesfully updated");
}
catch (Exception $e) {
  ting_smart_search_write_to_feedlog("Parsing of data failed: " . $e->getMessage());
}

ting_smart_search_write_to_feedlog("Memory used: " . memory_get_peak_usage());

/**
 * Write to logfile
 */
function ting_smart_search_write_to_feedlog($entry) {
  file_put_contents("./feedlog.txt", print_r($entry . "\n", TRUE), FILE_APPEND);
}

/**
 * Check if smart search record is within active year.
 */
function ting_smart_search_is_from_period($line, $lookback_period = 4) {
  $date = new DateTime();
  $year = $date->format("Y");
  $week = $date->format("W");
  $search_year = $line[0];
  $search_week = $line[1];
  if ($search_year == $year && $week - $lookback_period <= $search_week) {
    return true;
  }
  elseif (($search_year == $year - 1) && $week <= $lookback_period) {
    if ($search_week >= (52 - $lookback_period + $week)) {
      return true;
    }
  }
  return false;
}

/**
 * Sort the search data.
 */
function ting_smart_search_sort_search_data($a, $b) {
  if ($a['long_period'] == $b['long_period']) {
    return 0;
  }
  return ($a['long_period'] < $b['long_period']) ? 1 : -1;
}
