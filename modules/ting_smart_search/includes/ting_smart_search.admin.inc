<?php

/**
 * @file
 * Admin related backend.
 */

/**
 * Admin page menu callback.
 *
 * @return array
 *   Admin form.
 */
function ting_smart_search_admin_page() {
  $output = '';
  $output = drupal_get_form('ting_smart_search_admin_form');
  return $output;
}

/**
 * Admin settings form for basic smart search function.
 */
function ting_smart_search_admin_form($form, &$form_state) {
  $form = array();

  $form['import_automatic_data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Automatic smart search import settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['import_automatic_data']['ting_smart_search_automatic_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate automatic smart search'),
    '#default_value' => variable_get('ting_smart_search_automatic_active', TRUE),
    '#description' => t('Fetch data for popular terms'),
  );

  $form['import_automatic_data']['ting_smart_search_master_server'] = array(
    '#title' => t('Master server for automatic smart search'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_smart_search_master_server', 'https://staging.randersbib.dk/data/autodata.txt'),
    '#required' => FALSE,
    '#states' => array(
      'visible' => array(
          ':input[name="ting_smart_search_automatic_active"]' => array('checked' => TRUE)),
    ),
    '#description' => t('The path to auto data file.'),
  );

  $form['import_webtrekk_stats'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webtrekk statistics'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['import_webtrekk_stats']['ting_smart_search_webtrekk_server_feed'] = array(
    '#title' => t('Webtrekk statistics feed'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_smart_search_webtrekk_server_feed', 'https://staging.randersbib.dk/data/searchdata.csv'),
    '#required' => FALSE,
    '#description' => t('The path to search data files, fetches stats on popular search terms'),
  );

  $form['well_index_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Well index'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['well_index_settings']['ting_smart_search_well_index_records'] = array(
    '#title' => t('Well index records'),
    '#type' => 'textarea',
    '#default_value' => variable_get('ting_smart_search_well_index_records', "term.acSource\nterm.creator\nterm.date\nterm.language\nterm.type\nterm.identifier\nterm.subject\nfacet.dk5"),
    '#required' => FALSE,
    '#description' => t('Indtast hvert brøndindeks på ny linie.'),
  );

  $form['export_smartsearch'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export Smart Search Records'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['export_smartsearch']['submit_export'] = array(
    '#value' => t('Export Smart Search records'),
    '#type' => 'submit',
    '#submit' => array('ting_smart_search_export_form_submit'),
  );
  $form['import_smartsearch'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import Smart Search records'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['import_smartsearch']['ting_smart_search_import_file'] = array (
      '#title'         => t('Upload Smart Search Records'),
      '#type'          => 'file',
  );

  $form['import_smartsearch']['submit_import'] = array(
    '#value' => t('Import smart search records'),
    '#type' => 'submit',
    '#validate' => array('ting_smart_search_import_form_validate'),
    '#submit' => array('ting_smart_search_import_form_submit'),
  );
  return system_settings_form($form);
}

/**
 * Implements submit callback
 */
function ting_smart_search_export_form_submit($form, &$form_state) {
  $destination = DRUPAL_ROOT.'/sites/default/files/smart-search-records-'.variable_get('site_name', "Default site name").'-'.date('d-m-Y-H-i').'.csv';

  $ssquery = new EntityFieldQuery();

  $ssquery->entityCondition('entity_type', 'ting_type')
    ->entityCondition('bundle', 'smart_search_string');

  $result = $ssquery->execute();

  if (isset($result['ting_type'])) {
    $string_items_nids = array_keys($result['ting_type']);

    $data = entity_load('ting_type', $string_items_nids);

    foreach ($string_items_nids as $string_item_nid) {
        $item_boostvalues = $data[$string_item_nid]->field_custom_boost_values;
        if (!empty($item_boostvalues)) {
          foreach ($item_boostvalues['und'] as $key => $field_collection_id) {
            $fce_fields = array();
            $field_collection_entity = entity_load('field_collection_item', $field_collection_id);
            $fce_fields = array(
              'field_field_boost_value' => $field_collection_entity[$field_collection_id['value']]->field_field_boost_value,
              'field_field_boost_weight' => $field_collection_entity[$field_collection_id['value']]->field_field_boost_weight,
              'field_field_name' => $field_collection_entity[$field_collection_id['value']]->field_field_name,
            );
            $data[$string_item_nid]->field_custom_boost_values['und'][$key] = $fce_fields;
          }
        }
      }

    $data = json_encode($data);
    $exportfile = file_unmanaged_save_data($data, $destination);
    $expf_arr = explode('/', $exportfile);
    $exportfile = '/sites/default/files/'.array_pop($expf_arr);
    $form_state['redirect'] = $exportfile;
  }
}

/**
 * Implements validate callback
 */
function ting_smart_search_import_form_validate($form, &$form_state) {
  $file = file_save_upload('ting_smart_search_import_file', array('file_validate_extensions' => array('csv'),
  ));
  if ($file) {
    if ($file = file_move($file, 'public://')) {

      $form_state['values']['ting_smart_search_import_file'] = $file;
    }
    else {
      form_set_error('ting_smart_search_import_file', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  }
  else {
    form_set_error('ting_smart_search_import_file', t('No file was uploaded.'));
  }
}

/**
 * Implements submit callback
 */
function ting_smart_search_import_form_submit($form, &$form_state) {
  // Store new file.
  $file = $form_state['values']['ting_smart_search_import_file'];

  // We are done with the file, remove it from storage.
  unset($form_state['values']['ting_smart_search_import_file']);

  // Make the storage of the file permanent.
  $file->status = FILE_STATUS_PERMANENT;

  // Save file status.
  file_save($file);

  // Set a response to the user.
  drupal_set_message(t('The form has been submitted and the smart search records have been saved, filename: @filename.', array(
    '@filename' => $file->filename,
  )));

  // prepare vars for import
  $import_entity = array();

  $json = @file_get_contents($file->uri);

  if ($json === FALSE) {
    drupal_set_message('Failed to load local file. Please check that filename and path are correct: '.variable_get('ting_smart_search_import_file_name', 'smart-search-records.csv'), 'warning');
  }

  $json_array = json_decode($json, true);
  if (is_null($json_array)) {
      // json decode failed. Error handling here
      return t('failed to load file');
  } else {
     $jsonIterator = new RecursiveArrayIterator($json_array);
  }

  foreach ($jsonIterator as $key => $val) {
      if(is_array($val)) {
          $import_entity[$key] = $val;
      }
  }

  foreach ($import_entity as $ssrecord) {
    if (array_key_exists('id', $ssrecord)) {

      $field_alternate_search_string = '';
      $field_sss_boost_materials = '';
      $field_custom_boost_values = array();

      // Define vars for imported values
      $title = $ssrecord['title'];

      // todo: check for 'und' og values OG lav generisk gennemløb af keys med tilhørende values
      if (!empty($ssrecord['field_alternate_search_string'])) {
        $field_alternate_search_string = $ssrecord['field_alternate_search_string']['und'][0]['value'];
      }
      if (!empty($ssrecord['field_custom_boost_values'])) {
        $field_custom_boost_values = $ssrecord['field_custom_boost_values']['und'];
      }
      if (!empty($ssrecord['field_sss_boost_materials'])) {
        $field_sss_boost_materials = $ssrecord['field_sss_boost_materials']['und'];
      }
      if (!empty($ssrecord['field_status'])) {
        $field_status = $ssrecord['field_status']['und'][0]['value'];
      }
      if (empty($title)) {
              drupal_set_message('Key fields are missing from array '.$ssrecord['id'].' Check the file and try again');
      } else {

        // find the matching entity and assign the values from import
        $ssquery = new EntityFieldQuery();

        $ssquery->entityCondition('entity_type', 'ting_type')
          ->entityCondition('bundle', 'smart_search_string')
          ->propertyCondition('title', $title, '=');

        $result = $ssquery->execute();

        if (isset($result['ting_type'])) {
          $string_items_nids = array_keys($result['ting_type']);
          $raw_item = entity_load('ting_type', array($string_items_nids[0]));
          $string_item = entity_metadata_wrapper('ting_type', $string_items_nids[0]);

          if ($string_item->field_sss_import_update->value() == 'open') {
            //update alternate search string from import
            $string_item->field_alternate_search_string->set($field_alternate_search_string);

            //empty boost materials before updating
            $string_item->field_sss_boost_materials->set(NULL);

            //update boost materials from import
            if (is_array($field_sss_boost_materials)) {
              foreach ($field_sss_boost_materials as $boost_material) {
                $string_item->field_sss_boost_materials[] = $boost_material['value'];
              }
            }

            //empty field_collection custom boost values before updating
            $string_item->field_custom_boost_values->set(NULL);

            //get to each field_collection and assign values

            foreach($field_custom_boost_values as $custom_boost_value) {
              // Create the collection entity and set it's "host".

              $collection = entity_create('field_collection_item', array('field_name' => 'field_custom_boost_values'));
              $collection->setHostEntity('ting_type', $raw_item[$string_items_nids[0]]);

              // Now define the collection parameters.
              $cwrapper = entity_metadata_wrapper('field_collection_item', $collection);

              $cwrapper->field_field_name->set($custom_boost_value['field_field_name']['und'][0]['value']);
              $cwrapper->field_field_boost_value->set($custom_boost_value['field_field_boost_value']['und'][0]['value']);
              $cwrapper->field_field_boost_weight->set($custom_boost_value['field_field_boost_weight']['und'][0]['value']);

              $cwrapper->save();
            }

            //update field_status from import
            $string_item->field_status->set($field_status);

            // save
            $string_item->save(true);

          }

        } else {

              // create a new node and assign the data
              $values = array(
                     'type' => 'smart_search_string',
                     'uid' => 1,
                     'status' => 1,
                     );
              $raw_entity = entity_create('ting_type', $values);
              $string_item = entity_metadata_wrapper('ting_type', $raw_entity);
              $string_item->title->set($title);

              //update field values from import
              $string_item->field_alternate_search_string->set($field_alternate_search_string);

              //update boost materials from import
              if (is_array($field_sss_boost_materials)) {
                foreach ($field_sss_boost_materials as $boost_material) {
                  $string_item->field_sss_boost_materials[] = $boost_material['value'];
                }
              }

              //empty field_collection custom boost values before updating
              $string_item->field_custom_boost_values->set(NULL);

              //get to each field_collection and assign values

              foreach($field_custom_boost_values as $custom_boost_value) {
                // Create the collection entity and set it's "host".

                $collection = entity_create('field_collection_item', array('field_name' => 'field_custom_boost_values'));
                $collection->setHostEntity('ting_type', $raw_entity);

                // Now define the collection parameters.
                $cwrapper = entity_metadata_wrapper('field_collection_item', $collection);

                $cwrapper->field_field_name->set($custom_boost_value['field_field_name']['und'][0]['value']);

                $cwrapper->field_field_boost_value->set($custom_boost_value['field_field_boost_value']['und'][0]['value']);
                $cwrapper->field_field_boost_weight->set($custom_boost_value['field_field_boost_weight']['und'][0]['value']);


                $cwrapper->save();
                //entity_save('field_collection_item', $cwrapper);
              }

              //update field_status from import
              $string_item->field_status->set($field_status);

              // save
              $string_item->save(true);

        }
      }
    }
  }
}