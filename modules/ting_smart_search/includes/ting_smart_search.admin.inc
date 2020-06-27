<?php

/**
 * @file
 * Admin related backend.
 */

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
        ':input[name="ting_smart_search_automatic_active"]' => array('checked' => TRUE),
      ),
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

  $form['export_smartsearch'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export Smart Search Records'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['export_smartsearch']['submit_to_list'] = array(
    '#value' => t('View local Smart Search records'),
    '#type' => 'submit',
    '#submit' => array('smart_search_string_to_list'),
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
  $form['import_smartsearch']['ting_smart_search_import_file'] = array(
    '#title' => t('Upload Smart Search Records'),
    '#type' => 'file',
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
  $destination = 'public://' . variable_get('site_name', 'ddb-cms') . '-' . date('d-m-Y-H-i') . '.json';

  $ssquery = new EntityFieldQuery();

  // export only active smart search records
  $ssquery->entityCondition('entity_type', 'ting_type')
          ->entityCondition('bundle', 'smart_search_string')
          ->fieldCondition('field_status', 'value', 'active', '=');

  $result = $ssquery->execute();

  if (isset($result['ting_type'])) {
    $string_items_nids = array_keys($result['ting_type']);

    $data = entity_load('ting_type', $string_items_nids);

    foreach ($string_items_nids as $string_item_nid) {
      $item_boostvalues = $data[$string_item_nid]->field_custom_boost_values_p;
      if (!empty($item_boostvalues)) {
        foreach ($item_boostvalues['und'] as $key => $field_collection_id) {
          $fce_fields = array();
          $field_collection_entity = entity_load('paragraphs_item', $field_collection_id);
          $fce_fields = array(
              'field_field_boost_value' => $field_collection_entity[$field_collection_id['value']]->field_field_boost_value,
              'field_field_boost_weight' => $field_collection_entity[$field_collection_id['value']]->field_field_boost_weight,
              'field_field_name' => $field_collection_entity[$field_collection_id['value']]->field_field_name,
          );
          $data[$string_item_nid]->field_custom_boost_values_p['und'][$key] = $fce_fields;
        }
      }
    }

    $data = json_encode($data);
    $exportfile = file_unmanaged_save_data($data, $destination);
    $expf_arr = explode('/', $exportfile);
    $exportfile = file_create_url('public://') . array_pop($expf_arr);
    $form_state['redirect'] = $exportfile;
  }
}

/**
 * Implements validate callback
 */
function ting_smart_search_import_form_validate($form, &$form_state) {
  $file = file_save_upload('ting_smart_search_import_file', array(
      'file_validate_extensions' => array('json'),
  ));
  if ($file) {
    if ($file = file_move($file, 'public://')) {

      $form_state['values']['ting_smart_search_import_file'] = $file;
    } else {
      form_set_error('ting_smart_search_import_file', t('Failed to write the uploaded file the site file folder.'));
    }
  } else {
    form_set_error('ting_smart_search_import_file', t('No file was uploaded.'));
  }
}

/**
 * Implements submit callback
 */
function ting_smart_search_import_form_submit($form, &$form_state) {
  // Store new file.
  $file = $form_state['values']['ting_smart_search_import_file'];

  // Prepare vars for import.
  $import_entity = array();

  $json = @file_get_contents($file->uri);

  if ($json === FALSE) {
    drupal_set_message(t('Failed to load local file. Please check that the file format is correct'), 'warning');
  } else {
    // Set a response to the user.
    drupal_set_message(t('The form has been submitted and the smart search records have been imported, filename: @filename.', array(
        '@filename' => $file->filename,
    )));
  }

  $json_array = json_decode($json, true);
  if (is_null($json_array)) {
    // Json decode failed. Error handling here.
    drupal_set_message(t('failed to load file. Error message: @error_msg.', array('@error_msg' => json_last_error_msg())));
  } else {
    $jsonIterator = new RecursiveArrayIterator($json_array);
  }

  foreach ($jsonIterator as $key => $val) {
    if (is_array($val)) {
      $import_entity[$key] = $val;
    }
  }

  foreach ($import_entity as $ssrecord) {
    if (array_key_exists('id', $ssrecord)) {

      $field_alternate_search_string = '';
      $field_sss_boost_materials = '';
      $field_custom_boost_values_p = array();

      // Define vars for imported values.
      $title = $ssrecord['title'];

      if (!empty($ssrecord['field_alternate_search_string'])) {
        $field_alternate_search_string = $ssrecord['field_alternate_search_string']['und'][0]['value'];
      }
      if (!empty($ssrecord['field_custom_boost_values_p'])) {
        $field_custom_boost_values_p = $ssrecord['field_custom_boost_values_p']['und'];
      }
      if (!empty($ssrecord['field_sss_boost_materials'])) {
        $field_sss_boost_materials = $ssrecord['field_sss_boost_materials']['und'];
      }
      if (!empty($ssrecord['field_status'])) {
        $field_status = $ssrecord['field_status']['und'][0]['value'];
      }
      if (empty($title)) {
        drupal_set_message(t('Key fields are missing from array @ssrecordid. Check the file and try again.', array(
            '@ssrecordid' => $ssrecord['id'],
        )));
      } else {
        $update = FALSE;
        // Find the matching entity and assign the values from import.
        $ssquery = new EntityFieldQuery();

        $ssquery->entityCondition('entity_type', 'ting_type')
                ->entityCondition('bundle', 'smart_search_string')
                ->propertyCondition('title', $title, '=');

        $result = $ssquery->execute();

        if (isset($result['ting_type'])) {
          $update = TRUE;
          $string_items_nids = array_keys($result['ting_type']);
          $raw_entity = entity_load('ting_type', array($string_items_nids[0]));
          $string_item = entity_metadata_wrapper('ting_type', $string_items_nids[0]);
        } else {
          // Create a new node and assign the data.
          $values = array(
              'type' => 'smart_search_string',
              'uid' => 1,
              'status' => 1,
          );
          $raw_entity = entity_create('ting_type', $values);
          $string_item = entity_metadata_wrapper('ting_type', $raw_entity);
          $string_item->title->set($title);
        }

        // Update alternate search string from import.
        $string_item->field_alternate_search_string->set($field_alternate_search_string);

        // Empty boost materials before updating.
        $string_item->field_sss_boost_materials->set(NULL);

        // Update boost materials from import.
        if (is_array($field_sss_boost_materials)) {
          foreach ($field_sss_boost_materials as $boost_material) {
            $string_item->field_sss_boost_materials[] = $boost_material['value'];
          }
        }

        // Empty paragraphs custom boost values before updating.
        $string_item->field_custom_boost_values_p->set(NULL);

        // Get to each paragraph and assign values.
        foreach ($field_custom_boost_values_p as $custom_boost_value) {
          // Create the paragraph entity and set it's "host".

          $collection = new ParagraphsItemEntity(array('field_name' => 'field_custom_boost_values_p', 'bundle' => 'custom_boost_values'));
          $collection->is_new = TRUE;
          if ($update) {
              $collection->setHostEntity('ting_type', $raw_entity[$string_items_nids[0]]);
          }
          else {
            $collection->setHostEntity('ting_type', $raw_entity);
          }


          // Now define the collection parameters.
          $cwrapper = entity_metadata_wrapper('paragraphs_item', $collection);

          $cwrapper->field_field_name->set($custom_boost_value['field_field_name']['und'][0]['value']);
          $cwrapper->field_field_boost_value->set($custom_boost_value['field_field_boost_value']['und'][0]['value']);
          $cwrapper->field_field_boost_weight->set($custom_boost_value['field_field_boost_weight']['und'][0]['value']);

          $cwrapper->save();
        }

        // Update field_status from import.
        $string_item->field_status->set($field_status);

        // Save.
        $string_item->save(true);
      }
    }
  }
}
