<?php
/**
 * @file
 * ting_new_materials.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function ting_new_materials_field_default_fields() {
  $fields = array();

  // Exported field: 'node-new_materials-field_limit_period'.
  $fields['node-new_materials-field_limit_period'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_limit_period',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'number',
      'settings' => array(
        'profile2_private' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'number_integer',
    ),
    'field_instance' => array(
      'bundle' => 'new_materials',
      'default_value' => array(
        0 => array(
          'value' => '3',
        ),
      ),
      'deleted' => '0',
      'description' => 'Limits how the number of months worth of new materials there are shown. E.g. value of 3  means results from current month and the last three are shown. If left empty users can see all results of a query sorted newest first.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'number',
          'settings' => array(
            'decimal_separator' => '.',
            'prefix_suffix' => TRUE,
            'scale' => 0,
            'thousand_separator' => ' ',
          ),
          'type' => 'number_integer',
          'weight' => 2,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_limit_period',
      'label' => 'Limit period',
      'required' => 0,
      'settings' => array(
        'max' => '12',
        'min' => '',
        'prefix' => '',
        'suffix' => '',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'number',
        'settings' => array(),
        'type' => 'number',
        'weight' => '33',
      ),
    ),
  );

  // Exported field: 'node-new_materials-field_search_string'.
  $fields['node-new_materials-field_search_string'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_search_string',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'max_length' => '255',
        'profile2_private' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'new_materials',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'Search query used to get new materials. In order to get rid of non relevant posts use following syntax: query AND NOT (id OR id) where faustnumber is the id of the posts to exclude. E.g. "krimi bog engelsk AND NOT  (25863690 OR 29258341)"',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_search_string',
      'label' => 'Search string',
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'size' => '60',
        ),
        'type' => 'text_textfield',
        'weight' => '31',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Limit period');
  t('Limits how the number of months worth of new materials there are shown. E.g. value of 3  means results from current month and the last three are shown. If left empty users can see all results of a query sorted newest first.');
  t('Search query used to get new materials. In order to get rid of non relevant posts use following syntax: query AND NOT (id OR id) where faustnumber is the id of the posts to exclude. E.g. "krimi bog engelsk AND NOT  (25863690 OR 29258341)"');
  t('Search string');

  return $fields;
}
