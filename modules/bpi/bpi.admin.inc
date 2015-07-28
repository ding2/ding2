<?php
/**
 * @file
 * Admin related things here.
 */

/**
 * Creates an administrative block on the configuration page for grouping
 * various settings.
 *
 * @return string
 *   HTML for the block.
 */
function bpi_admin_menu_block_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  if ($content) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }

  return $output;
}

/**
 * Administrative settings form.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @return array
 *   Form structure prepared for admin settings.
 *
 * @ingroup forms
 */
function bpi_admin_settings_form($form, $form_state) {
  $form['bpi_service_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('BPI Service settings'),
  );

  $form['bpi_service_settings']['bpi_agency_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Agency ID'),
    '#description' => t('The 6-digit code representing the library organization'),
    '#default_value' => variable_get('bpi_agency_id', variable_get('ting_agency', '')),
    '#required' => TRUE,
  );

  $form['bpi_service_settings']['bpi_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('The location of the web-service (http://bpi1.inlead.dk)'),
    '#default_value' => variable_get('bpi_service_url', 'http://bpi1.inlead.dk'),
    '#required' => TRUE,
  );

  $form['bpi_service_settings']['bpi_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#default_value' => variable_get('bpi_secret_key', ''),
    '#required' => TRUE,
  );

  $form['bpi_service_settings']['bpi_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Public key'),
    '#default_value' => variable_get('bpi_api_key', ''),
    '#required' => TRUE,
  );

  $form['bpi_general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );

  $form['bpi_general_settings']['bpi_content_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Content per page'),
    '#options' => array_combine(range(10, 100, 10), range(10, 100, 10)),
    '#default_value' => variable_get('bpi_content_per_page', BPI_CONTENT_PER_PAGE),
  );

  return system_settings_form($form);
}

/**
 * Implements hook_FROM_ID_validate().
 */
function bpi_admin_settings_form_validate(&$form, &$form_state) {
  // Check if ting agency matches BPI agency, if not give a warning message.
  if (module_exists('ting') && variable_get('ting_agency', FALSE) != $form_state['values']['bpi_agency_id']) {
    drupal_set_message(t('T!NG agency ID %id does not match BPI agency ID', array('%id' => variable_get('ting_agency', FALSE))), 'warning');
  }

  // Check that the service URL is a valid URL.
  $url = $form_state['values']['bpi_service_url'];
  if (!valid_url($url, TRUE)) {
    form_set_error('bpi_service_url', t('Please enter a valid url.'));
  }
  else {
    // Check that the client can connect to the service.
    try {
      $values = $form_state['values'];
      new Bpi($values['bpi_service_url'], $values['bpi_agency_id'], $values['bpi_api_key'], $values['bpi_secret_key']);;
    }
    catch (\Guzzle\Http\Exception\CurlException $exception) {
      // Communication error e.i. not correct end-point.
      form_set_error('bpi_service_url', t($exception->getError()));
    }
    catch (Exception $exception) {
      // Unknown error.
      drupal_set_message(t('Communication with the servies failed. Check the log for more information.'), 'error');
      watchdog_exception('bpi', $exception);
    }

  }
}

/**
 * Map BPI fields to local node fields when syndicating and/or pushing.
 *
 * Since on different installations it's most likely possible that
 * fields will differ from what is to be expected, field mapping
 * functionality is required.
 *
 * The mapping settings from here are used both when syndicating
 * and when pushing content from/to BPI.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @return array
 *   Form structure prepared for admin settings.
 *
 * @ingroup forms
 */
function bpi_admin_content_mapping_form($form, $form_state) {
  $node_types = node_type_get_names();
  $node_types_names = array_keys($node_types);

  $form['bpi_content_type'] = array(
    '#type' => 'select',
    '#title' => t('Content type'),
    '#description' => t('Select a content type into which content from BPI will be syndicated.'),
    '#options' => $node_types,
    '#default_value' => variable_get('bpi_content_type', reset($node_types_names)),
    '#ajax' => array(
      'callback' => '_bpi_content_mapper_ctype_fields',
      'wrapper' => 'bpi-field-mapper-wrapper',
      'effect' => 'fade',
      'method' => 'replace',
    ),
  );

  // Get filter list of field instances.
  $selected_node_type = $form['bpi_content_type']['#default_value'];

  if (isset($form_state['values']['bpi_content_type'])) {
    $selected_node_type = $form_state['values']['bpi_content_type'];
  }

  $field_instances = bpi_get_field_instances($selected_node_type);

  $form['bpi_mapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field mapping'),
    '#description' => t('Define you custom mapping rules. Each dropdown maps BPI related fields to your content fields.'),
    '#prefix' => '<div id="bpi-field-mapper-wrapper">',
    '#suffix' => '</div>',
  );

  $form['bpi_mapper']['bpi_field_title'] = array(
    '#type' => 'select',
    '#title' => t('BPI title'),
    '#description' => t('Titles are automatically assigned.'),
    '#options' => array('title' => t('Title')),
    '#default_value' => variable_get('bpi_field_title', 'title'),
    '#disabled' => TRUE,
  );

  $form['bpi_mapper']['bpi_field_teaser'] = array(
    '#type' => 'select',
    '#title' => t('BPI teaser'),
    '#description' => t('The field to extract the teaser from. If the content type have a body summary, assign it to the body field.'),
    '#options' => $field_instances,
    '#default_value' => variable_get('bpi_field_teaser', ''),
  );

  $form['bpi_mapper']['bpi_field_body'] = array(
    '#type' => 'select',
    '#title' => t('BPI body'),
    '#description' => t('Field to extract the main cotenten from (body field).'),
    '#options' => $field_instances,
    '#default_value' => variable_get('bpi_field_body', ''),
  );

  $form['bpi_mapper']['bpi_field_materials'] = array(
    '#type' => 'select',
    '#title' => t('BPI materials'),
    '#description' => t('Field used to get reference to the T!NG data well.'),
    '#options' => $field_instances,
    '#default_value' => variable_get('bpi_field_materials', ''),
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';

  return system_settings_form($form);
}

/**
 * Custom form AJAX callback.
 *
 * @see bpi_admin_content_mapping_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @return array
 *   Element to be altered via AJAX.
 *
 * @ingroup forms
 */
function _bpi_content_mapper_ctype_fields(&$form, &$form_state) {
  return $form['bpi_mapper'];
}

/**
 * Get a list of fields, for a certain node type.
 *
 * Simplifies and filters the output of the core field_info_instances()
 * function.
 *
 * Filtering means that we do not want text values into image fields, etc.
 *
 * @param string $node_type
 *   Node type machine name, whose fields list is expected.
 *
 * @return array
 *   An array with the fields, for the specified node type.
 */
function bpi_get_field_instances($node_type) {
  if (empty($node_type)) {
    return array();
  }

  $fields = array();
  $allowed_widgets = array(
    'text_textfield',
    'text_textarea',
    'text_textarea_with_summary',
    'ting_reference_simple',
    'ting_reference_advanced',
  );

  $field_instances = field_info_instances('node', $node_type);

  foreach ($field_instances as $instance) {
    if (in_array($instance['widget']['type'], $allowed_widgets)) {
      $fields[$instance['field_name']] = $instance['label'];
    }
  }

  return $fields;
}
