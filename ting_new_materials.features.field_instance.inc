<?php
/**
 * @file
 * ting_new_materials.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ting_new_materials_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-new_materials-field_ting_new_materials_items'
  $field_instances['node-new_materials-field_ting_new_materials_items'] = array(
    'bundle' => 'new_materials',
    'default_value' => array(
      0 => array(
        'value' => 10,
      ),
    ),
    'deleted' => 0,
    'description' => 'The number of items to display on each page, if the number of results are grater than this a pager will be used. ',
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
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ting_new_materials_items',
    'label' => 'Number of items',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => 5,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 33,
    ),
  );

  // Exported field_instance: 'node-new_materials-field_ting_new_materials_limit'
  $field_instances['node-new_materials-field_ting_new_materials_limit'] = array(
    'bundle' => 'new_materials',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Limits how the number of months worth of new materials there are shown. E.g. value of 3  means results from current month and the last three are shown. If left empty users can see all results of a query sorted newest first',
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
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ting_new_materials_limit',
    'label' => 'Limit period',
    'required' => 0,
    'settings' => array(
      'max' => 12,
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 32,
    ),
  );

  // Exported field_instance: 'node-new_materials-field_ting_new_materials_search'
  $field_instances['node-new_materials-field_ting_new_materials_search'] = array(
    'bundle' => 'new_materials',
    'default_value' => NULL,
    'deleted' => 0,
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
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_ting_new_materials_search',
    'label' => 'Search query',
    'required' => 1,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Limit period');
  t('Limits how the number of months worth of new materials there are shown. E.g. value of 3  means results from current month and the last three are shown. If left empty users can see all results of a query sorted newest first');
  t('Number of items');
  t('Search query');
  t('Search query used to get new materials. In order to get rid of non relevant posts use following syntax: query AND NOT (id OR id) where faustnumber is the id of the posts to exclude. E.g. "krimi bog engelsk AND NOT  (25863690 OR 29258341)"');
  t('The number of items to display on each page, if the number of results are grater than this a pager will be used. ');

  return $field_instances;
}
