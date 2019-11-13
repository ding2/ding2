<?php

/**
 * A script to parse the raw autodata files from Webtrekk via KPI index.
 *
 *
 */

$file_year = 'autodatayear.csv';
$file_month = 'autodatamonth.csv';
$output_file = 'autodata.txt';

try {
  $output = array();
  $file = fopen($file_year, 'r');
  $data = array();
  while (($line = fgetcsv($file, 1000, ";")) !== FALSE) {
    if (!(strpos($line[1], 'ereolen') !== false)) {
      $search = $line[0];
      $clicked_page = $line[1];
      $hits = $line[2];
      $object = null;
      if (strpos($clicked_page, 'ting/object/') !== false) {
        $object = explode('ting/object/', $clicked_page);
      }
      elseif (strpos($clicked_page, 'ting/collection/') !== false) {
        $object = explode('ting/collection/', $clicked_page);
      }
      $faust = $object[1];
      if (isset($object) && isset($faust)) {
        if (!array_key_exists($search, $data)) {
          $data[$search] = array();
        }

        if (!array_key_exists($faust, $data[$search])) {
          $data[$search][$faust] = $hits;
        }
        else {
          $data[$search][$faust] += $hits;
        }
      }
    }
  }
  fclose($file);
  foreach ($data as $search => $objects) {
    arsort($objects);
    if (reset($objects) >= 3) {
      $output[$search] = array_slice($objects, 0, 5);
    }
  }
  $serialized_output = serialize($output);
  file_put_contents($output_file, $serialized_output);

  ting_smart_search_write_to_log("Data succesfully updated");
}
catch (Exception $e) {
  ting_smart_search_write_to_log("Parsing of data failed: " . $e->getMessage());
}

ting_smart_search_write_to_log("Memory used: " . memory_get_peak_usage());

/**
 * Write to log.
 */
function ting_smart_search_write_to_log($entry) {
  file_put_contents("./log.txt", print_r($entry . "\n", TRUE), FILE_APPEND);
}
