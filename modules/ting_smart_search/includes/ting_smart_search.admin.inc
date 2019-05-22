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

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smart search settings'),
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

  $form['webtrekk_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webtrekk account settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['webtrekk_settings']['ting_smart_search_webtrekk_customerid'] = array(
    '#title' => t('Webtrekk customerId'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_smart_search_webtrekk_customerid', 0),
    '#required' => FALSE,
    '#description' => t('The customer Id for the webtrekk account.'),
  );

  $form['webtrekk_settings']['ting_smart_search_webtrekk_customerlogin'] = array(
    '#title' => t('Webtrekk customer login'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_smart_search_webtrekk_customerlogin', ''),
    '#required' => FALSE,
    '#description' => t('The customer login for the webtrekk account.'),
  );

  $form['webtrekk_settings']['ting_smart_search_webtrekk_customerpassword'] = array(
    '#title' => t('Webtrekk customer password'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_smart_search_webtrekk_customerpassword', ''),
    '#required' => FALSE,
    '#description' => t('The customer password for the webtrekk account.'),
  );

  $form['compile_stats'] = array(
    '#type' => 'fieldset',
    '#title' => t('Compile statistics'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['compile_stats']['submit_stats'] = array(
    '#value' => t('Compile statfiles'),
    '#type' => 'submit',
    '#submit' => array('ting_smart_search_compilestats_form_submit'),
  );

  $form['compile_stats']['submit_placing'] = array(
    '#value' => t('Compile placings'),
    '#type' => 'submit',
    '#submit' => array('ting_smart_search_compileplacings_form_submit'),
  );

  $form['export_smartsearch'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export Smart Search Records'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['export_smartsearch']['ting_smart_search_export_file_name'] = array(
    '#title' => t('Export file name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_smart_search_export_file_name', '/sites/default/files/export/smart-search-records.csv'),
    '#required' => TRUE,
    '#description' => t('File will by default be located in /sites/default/files/export/ - you can change the path in this field'),
  );
  $form['export_smartsearch']['submit_export'] = array(
    '#value' => t('Export to json file'),
    '#type' => 'submit',
    '#submit' => array('ting_smart_search_export_form_submit'),
  );
  $form['import_smartsearch'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import Smart Search Records'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['import_smartsearch']['ting_smart_search_import_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import Smart Search Records from remote server'),
  );
  $form['import_smartsearch']['ting_smart_search_import_file_name'] = array(
    '#title' => t('Import local file name'),
    '#type' => 'textfield',
    '#default_value' => variable_get('ting_smart_search_import_file_name', '/sites/default/files/export/smart-search-records.csv'),
    '#required' => TRUE,
    '#states' => array(
      // Only show this field when the field: import from remote server is NOT checked.
      'visible' => array(
          ':input[name="ting_smart_search_import_status"]' => array('checked' => FALSE)),
    ),
    '#description' => t('File will be imported from this path - default path is /sites/default/files/export/'),
  );
  $form['import_smartsearch']['submit_import'] = array(
    '#value' => t('Import json file'),
    '#type' => 'submit',
    '#submit' => array('ting_smart_search_import_form_submit'),
  );
  return system_settings_form($form);
}

/**
 * A form for executing python script compilestats.py to calculate and prepare
 * a file for importing hitscores for search terms
 */
function ting_smart_search_compilestats_form($form, &$form_state) {
  $form = array();

  $form['submit'] = array(
    '#value' => t('Compile statfiles'),
    '#type' => 'submit',
  );

  return $form;
}

function ting_smart_search_compilestats_form_submit($form, &$form_state) {
  drupal_set_message('Kapow!');
  drupal_set_message($_SERVER["SCRIPT_FILENAME"]);
  $command = escapeshellcmd('python /var/www/drupal7vm/drupal/web/'.drupal_get_path('module', 'ting_smart_search').'/extras/compilestats.py');
  $return_value = shell_exec($command);
  drupal_set_message($command);
  drupal_set_message($return_value);
}

function ting_smart_search_compileplacings_form_submit($form, &$form_state) {
  drupal_set_message('Placings being compiled');
  drupal_set_message($_SERVER["SCRIPT_FILENAME"]);
  $command = escapeshellcmd('python /var/www/drupal7vm/drupal/web/'.drupal_get_path('module', 'ting_smart_search').'/extras/compilestats_placing.py');
  $return_value = shell_exec($command);
  drupal_set_message($command);
  drupal_set_message($return_value);
}

function ting_smart_search_export_form_submit($form, &$form_state) {
  drupal_set_message('Export executed!');

  $destination = DRUPAL_ROOT.variable_get('ting_smart_search_export_file_name', 'smart-search-records.csv');
  $title = 'krimi';
  $ssquery = new EntityFieldQuery();

  $ssquery->entityCondition('entity_type', 'ting_type')
    ->entityCondition('bundle', 'smart_search_string')
    //->propertyCondition('title', $title, '=')
    ->range(0,10);

  $result = $ssquery->execute();

  if (isset($result['ting_type'])) {
    $string_items_nids = array_keys($result['ting_type']);

    $data = entity_load('ting_type', $string_items_nids);//, array('nid' => $string_items_nids[0]);


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
    file_unmanaged_save_data($data, $destination);
  }
}

function ting_smart_search_import_form_submit($form, &$form_state) {

  // prepare vars for import
  $import_entity = array();

  if ($form['import_smartsearch']['ting_smart_search_import_status']['#value']) {
      $json = @file_get_contents('https://randersbib.dk/sites/default/files/smart-search-records-export.csv');
       if ($json === FALSE) {
         drupal_set_message('Failed to load file from remote location', 'warning');
       }
  } else {
    $json = @file_get_contents(DRUPAL_ROOT.variable_get('ting_smart_search_import_file_name', 'smart-search-records.csv'));
    if ($json === FALSE) {
      drupal_set_message('Failed to load local file. Please check that filename and path are correct: '.variable_get('ting_smart_search_import_file_name', 'smart-search-records.csv'), 'warning');
    }
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
      } else {
        // something something ...
      }
  }
dpm($import_entity);
  foreach ($import_entity as $ssrecord) {
    if (array_key_exists('id', $ssrecord)) {
      dpm($ssrecord);
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

        drupal_set_message($title.' found.');
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
          dpm($string_item->field_sss_import_update->value());
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

            drupal_set_message('Title: '.$title.' has been updated.');
          } else {

            drupal_set_message('Smart search string found, but locked; no update performed.');            
          }

        } else {

              drupal_set_message('No smart string found - creating new smart string');
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

              drupal_set_message('Title: '.$title.' has been created.');
        }
      }
    }
  }
  // set new import timestamp
  variable_set('smart_search_import_timestamp', time());
}

function objectToArray ($object) {
    if(!is_object($object) && !is_array($object)) return $object;

    return array_map('objectToArray', (array) $object);
}
