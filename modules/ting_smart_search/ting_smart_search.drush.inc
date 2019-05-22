<?php

/**
 * Implementation of hook_drush_command().
 */
function ting_smart_search_drush_command() {
  $items = array();
  $items['stats-importer'] = array(
    'description' => 'Drush command to import csv-stats to entity.',
    'aliases' => array('sti'), // alias of command
    'examples' => array(      // List these example when user types : drush help nc
      'Import csv file' => 'drush sti --file=sites/default/files/mystats.txt',
    ),
    'arguments' => array(
      'type' => 'The type of statement - optional (import only for now).',
    ),
    'options' => array(
      'file' => 'The path to the file to import.',
    ),
  );
  $items['score-importer'] = array(
    'description' => 'Drush command to import csv-scores to entity.',
    'aliases' => array('sci'), // alias of command
    'examples' => array(      // List these example when user types : drush help nc
      'Import csv file' => 'drush sci --file=sites/default/files/compile/myscores.txt',
    ),
    'arguments' => array(
      'type' => 'The type of statement - optional (import only for now).',
    ),
    'options' => array(
      'file' => 'The path to the file to import.',
    ),
  );

  return $items;
}

/**
 * Import stats from csv file
 */
 function drush_ting_smart_search_stats_importer() {

         $file = drush_get_option('file');

         if (!empty($file) && file_exists($file)) {
                 $csv_data = array_map(function($v){return str_getcsv($v, "\t");}, file($file));
                 // loop through array and skip 0 lines
                 for ($i = 5; $i < 5005/*count($csv_data)*/;$i++) {
                         $title = $csv_data[$i][0];
                         $hits_year = ($csv_data[$i][1] == '-') ? 0 : $csv_data[$i][1];
                         $hits_month = ($csv_data[$i][2] == '-') ? 0 : $csv_data[$i][2];


                         // fail if key fields are not present
                         if (empty($title)) {
                                 drupal_set_message('Key fields are missing from array '.$i.'. Check the file and try again');
                         } else {

                           drupal_set_message($title.' - '.$hits_year.' - '.$hits_month);
                           // find the matching entity and assign the stats
                           $ssquery = new EntityFieldQuery();

                           $ssquery->entityCondition('entity_type', 'ting_type')
                             ->entityCondition('bundle', 'smart_search_string')
                             ->propertyCondition('title', $title, '=');

                           $result = $ssquery->execute();

                           if (isset($result['ting_type'])) {
                             $string_items_nids = array_keys($result['ting_type']);
                             $string_item = entity_metadata_wrapper('ting_type', $string_items_nids[0]);
                             $string_item->field_sss_hits_per_year->set($hits_year);
                             $string_item->field_sss_hits_per_month->set($hits_month);
                             // save
                             $string_item->save();
                             drupal_set_message('Title: '.$title.' has been substituted with: '.$hits_year.' - '.$hits_month);

                           } else {

                                drupal_set_message('No smart string found - creating new smart string');
                                // create a new node and assign the data
                                $values = array(
                                        'type' => 'smart_search_string',
                                        'uid' => 1,
                                        'status' => 1,
                                        );
                                $entity = entity_create('ting_type', $values);
                                $new_string_item = entity_metadata_wrapper('ting_type', $entity);
                                $new_string_item->title->set($title);
                                $new_string_item->field_sss_hits_per_year->set($hits_year);
                                $new_string_item->field_sss_hits_per_month->set($hits_month);

                                // save
                                $new_string_item->save();
                           }

                         }



                 }
         } else {
                 return 'No file given to import or file does not exist';
         }
 }

 /**
  * Import stats from csv file
  */
  function drush_ting_smart_search_score_importer() {

          $file = drush_get_option('file');
          //dpm($file);
          if (!empty($file) && file_exists($file)) {
                  $csv_data = array_map(function($v){return str_getcsv($v, ",", "\t");}, file($file));
                  // loop through array and skip 0 lines
                  for ($i = 0; $i < 80000/*count($csv_data)*/;$i++) {
                          $title = str_replace(' and ', ' ', $csv_data[$i][0]);
                          $title = str_replace('(', '', $title);
                          $title = str_replace(')', '', $title);
                          $score = ($csv_data[$i][1] == '-') ? 0 : $csv_data[$i][1];


                          // fail if key fields are not present
                          if (empty($title)) {
                                  drupal_set_message('Key fields are missing from array '.$i.'. Check the file and try again');
                          } else {

                            drupal_set_message($title.' - '.$score);
                            // find the matching entity and assign the stats
                            $ssquery = new EntityFieldQuery();

                            $ssquery->entityCondition('entity_type', 'ting_type')
                              ->entityCondition('bundle', 'smart_search_string')
                              ->propertyCondition('title', $title, '=');

                            $result = $ssquery->execute();

                            if (isset($result['ting_type'])) {
                              $string_items_nids = array_keys($result['ting_type']);
                              $string_item = entity_metadata_wrapper('ting_type', $string_items_nids[0]);
                              $string_item->field_sss_hits_score->set($score);
                              // save
                              $string_item->save();
                              drupal_set_message('Title: '.$title.' has been updated with: '.$score);

                            }

                          }

                  }
          } else {
                  return 'No file given to import or file does not exist';
          }
  }
