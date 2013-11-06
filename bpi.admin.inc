<?php
/**
 * @file
 * Admin related things here.
 */

/**
 * Creates an administrative block on the configuration page
 * for grouping various settings.
 *
 * @return type
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
    '#default_value' => variable_get('bpi_agency_id', ''),
    '#required' => TRUE,
  );

  $form['bpi_service_settings']['bpi_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#default_value' => variable_get('bpi_service_url', ''),
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
    '#title' => t('API key'),
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


  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';
  $form['#validate'][] = 'bpi_admin_settings_form_validate';

  return system_settings_form($form);
}

/**
 * Custom validate handler for common settings form.
 *
 * Used for url validation, for now.
 *
 * @see bpi_admin_settings_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @ingroup forms
 */
function bpi_admin_settings_form_validate(&$form, &$form_state) {
  $url = $form_state['values']['bpi_service_url'];

  // Check if ting agency matches bpi agency.
  if (module_exists('ting') && variable_get('ting_agency', FALSE) != $form_state['values']['bpi_agency_id']) {
    drupal_set_message(t('T!NG agency ID %id does not match BPI agency ID', array('%id' => variable_get('ting_agency', FALSE))), 'warning');
  }

  if (!valid_url($url, TRUE)) {
    form_set_error('bpi_service_url', t('Please enter a valid url.'));
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
 * @return array
 *   Form structure prepared for admin settings.
 *
 * @ingroup forms
 */
function bpi_admin_content_mapping_form($form, $form_state) {
  $node_types = bpi_get_node_types();
  $node_types_names = array_keys($node_types);
  $field_instances = array();

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
    '#description' => t('Assign to body field, if it has summary enabled.'),
    '#options' => $field_instances,
    '#default_value' => variable_get('bpi_field_teaser', ''),
  );

  $form['bpi_mapper']['bpi_field_body'] = array(
    '#type' => 'select',
    '#title' => t('BPI body'),
    '#description' => '',
    '#options' => $field_instances,
    '#default_value' => variable_get('bpi_field_body', ''),
  );

  $form['bpi_mapper']['bpi_field_materials'] = array(
    '#type' => 'select',
    '#title' => t('BPI materials'),
    '#description' => '',
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
 * @return array
 *   Element to be altered via AJAX.
 *
 * @ingroup forms
 */
function _bpi_content_mapper_ctype_fields(&$form, &$form_state) {
  return $form['bpi_mapper'];
}

/**
 * Get a list of available node types in the system.
 *
 * Simplifies the output returned by the core node_type_get_types()
 * function.
 *
 * @return array
 *   An associative array containing:
 *     - Node type machine name: Node type human name.
 */
function bpi_get_node_types() {
  $node_types = node_type_get_types();
  $types = array();

  foreach ($node_types as $type) {
    $types[$type->type] = $type->name;
  }

  return $types;
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
 * @return array
 *   An array with the fields, for the specified node type.
 */
function bpi_get_field_instances($node_type) {
  $fields = array();
  $allowed_widgets = array(
    'text_textfield',
    'text_textarea',
    'text_textarea_with_summary',
    'ting_reference_simple',
  );

  if (!empty($node_type)) {
    $field_instances = field_info_instances('node', $node_type);

    foreach ($field_instances as $instance) {
      if (in_array($instance['widget']['type'], $allowed_widgets)) {
        $fields[$instance['field_name']] = $instance['label'];
      }
    }
  }

  return $fields;
}
