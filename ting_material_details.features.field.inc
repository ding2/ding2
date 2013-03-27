<?php
/**
 * @file
 * ting_material_details.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function ting_material_details_field_default_fields() {
  $fields = array();

  // Exported field: 'ting_object-ting_object-ting_details_age'.
  $fields['ting_object-ting_object-ting_details_age'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_age',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_age',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '27',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '25',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '67',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '23',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_age',
      'label' => 'Age',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '38',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_audience'.
  $fields['ting_object-ting_object-ting_details_audience'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_audience',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_audience',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '26',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '23',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '66',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '22',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_audience',
      'label' => 'Audience',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '37',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_classification'.
  $fields['ting_object-ting_object-ting_details_classification'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_classification',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_classification',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '24',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '24',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '50',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '21',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_classification',
      'label' => 'Classification',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '21',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_contributor'.
  $fields['ting_object-ting_object-ting_details_contributor'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_contributor',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_contributor',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '25',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '29',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '52',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '25',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_contributor',
      'label' => 'Contributor',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '23',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_description'.
  $fields['ting_object-ting_object-ting_details_description'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_description',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_description',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '30',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '30',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '56',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '20',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_description',
      'label' => 'Description',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '27',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_extent'.
  $fields['ting_object-ting_object-ting_details_extent'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_extent',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_extent',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '29',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '35',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '63',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '24',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_extent',
      'label' => 'Extent',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '34',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_format'.
  $fields['ting_object-ting_object-ting_details_format'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_format',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_format',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '33',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '36',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '42',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '26',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_format',
      'label' => 'Format',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '14',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_genre'.
  $fields['ting_object-ting_object-ting_details_genre'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_genre',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_genre',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '35',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '34',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '48',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '29',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_genre',
      'label' => 'Genre',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '19',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_isbn'.
  $fields['ting_object-ting_object-ting_details_isbn'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_isbn',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_isbn',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '36',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '33',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '60',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '27',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_isbn',
      'label' => 'ISBN no.',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '31',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_ispartof'.
  $fields['ting_object-ting_object-ting_details_ispartof'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_ispartof',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_ispartof',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '34',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '31',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '43',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '28',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_ispartof',
      'label' => 'Available in',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '15',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_language'.
  $fields['ting_object-ting_object-ting_details_language'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_language',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_language',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '31',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '32',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '45',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '19',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_language',
      'label' => 'Language',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '16',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_musician'.
  $fields['ting_object-ting_object-ting_details_musician'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_musician',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_musician',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '32',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '37',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '53',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '18',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_musician',
      'label' => 'Musician',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '24',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_pegi'.
  $fields['ting_object-ting_object-ting_details_pegi'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_pegi',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(
        'profile2_private' => FALSE,
      ),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_pegi',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '23',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '22',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '68',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_pegi',
      'label' => 'Pegi mark',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '38',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_publisher'.
  $fields['ting_object-ting_object-ting_details_publisher'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_publisher',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_publisher',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '22',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '12',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '64',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_publisher',
      'label' => 'Publisher',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '35',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_referenced'.
  $fields['ting_object-ting_object-ting_details_referenced'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_referenced',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_referenced',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '13',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '13',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '55',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '7',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_referenced',
      'label' => 'Referenced by',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '26',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_replaced_by'.
  $fields['ting_object-ting_object-ting_details_replaced_by'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_replaced_by',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_replaced_by',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '14',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '59',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '6',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_replaced_by',
      'label' => 'Later title',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '30',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_replaces'.
  $fields['ting_object-ting_object-ting_details_replaces'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_replaces',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_replaces',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '12',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '58',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '3',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_replaces',
      'label' => 'Previous title',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '29',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_rights'.
  $fields['ting_object-ting_object-ting_details_rights'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_rights',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_rights',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '7',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '65',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '4',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_rights',
      'label' => 'Rights',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '36',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_source'.
  $fields['ting_object-ting_object-ting_details_source'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_source',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_source',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '57',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '5',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_source',
      'label' => 'Original title',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '28',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_spatial'.
  $fields['ting_object-ting_object-ting_details_spatial'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_spatial',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_spatial',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '51',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_spatial',
      'label' => 'Spatial',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '22',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_spoken'.
  $fields['ting_object-ting_object-ting_details_spoken'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_spoken',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_spoken',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '15',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '14',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '46',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_spoken',
      'label' => 'Speech',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '17',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_subjects'.
  $fields['ting_object-ting_object-ting_details_subjects'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_subjects',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_subjects',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '16',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '15',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '49',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '16',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_subjects',
      'label' => 'Subject',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '20',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_subtitles'.
  $fields['ting_object-ting_object-ting_details_subtitles'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_subtitles',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_subtitles',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '21',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '20',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '47',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '17',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_subtitles',
      'label' => 'Subtitle',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '18',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_tracks'.
  $fields['ting_object-ting_object-ting_details_tracks'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_tracks',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_tracks',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '20',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '21',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '54',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '15',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_tracks',
      'label' => 'Contains',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '25',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_type'.
  $fields['ting_object-ting_object-ting_details_type'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_type',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_type',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '19',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '19',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '41',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '14',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_type',
      'label' => 'Type',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '13',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_uri'.
  $fields['ting_object-ting_object-ting_details_uri'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_uri',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_uri',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '17',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '18',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '61',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '12',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_uri',
      'label' => 'Host publication',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '32',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details_version'.
  $fields['ting_object-ting_object-ting_details_version'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details_version',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'ting_material_details',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'virtual_field',
      ),
      'translatable' => '0',
      'type' => 'ting_details_version',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '18',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '16',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting_material_details',
          'settings' => array(),
          'type' => 'ting_details_single',
          'weight' => '62',
        ),
        'search_result' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '13',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details_version',
      'label' => 'Version',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'virtual_field',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '33',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Age');
  t('Audience');
  t('Available in');
  t('Classification');
  t('Contains');
  t('Contributor');
  t('Description');
  t('Extent');
  t('Format');
  t('Genre');
  t('Host publication');
  t('ISBN no.');
  t('Language');
  t('Later title');
  t('Musician');
  t('Original title');
  t('Pegi mark');
  t('Previous title');
  t('Publisher');
  t('Referenced by');
  t('Rights');
  t('Spatial');
  t('Speech');
  t('Subject');
  t('Subtitle');
  t('Type');
  t('Version');

  return $fields;
}
