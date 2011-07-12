<?php
/**
 * @file
 * ding_ting_frontend.features.field.inc
 */

/**
 * Implementation of hook_field_default_fields().
 */
function ding_ting_frontend_field_default_fields() {
  $fields = array();

  // Exported field: 'ting_object-ting_object-ding_availability_holdings'
  $fields['ting_object-ting_object-ding_availability_holdings'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ding_availability_holdings',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ding_availability',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ding_availability_holdings',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'ding_availability',
          'settings' => array(),
          'type' => 'ding_availability_default',
          'weight' => '11',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ding_availability_holdings',
      'label' => 'Holdings information',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '11',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ding_availability_item'
  $fields['ting_object-ting_object-ding_availability_item'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ding_availability_item',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ding_availability',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ding_availability_item',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'ding_availability',
          'settings' => array(),
          'type' => 'ding_availability_default',
          'weight' => '9',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ding_availability_item',
      'label' => 'Availability information',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '9',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_abstract'
  $fields['ting_object-ting_object-ting_abstract'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_abstract',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ting',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ting_abstract',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_abstract_default',
          'weight' => '7',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_abstract',
      'label' => 'Ting object abstract',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '6',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_author'
  $fields['ting_object-ting_object-ting_author'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_author',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ting',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ting_author',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_author_default',
          'weight' => '6',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_author',
      'label' => 'Ting object author',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '7',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_cover'
  $fields['ting_object-ting_object-ting_cover'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_cover',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ting_covers',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ting_cover',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting_covers',
          'settings' => array(
            'image_style' => 'ding_small',
          ),
          'type' => 'ting_cover_default',
          'weight' => '3',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_cover',
      'label' => 'Cover',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '3',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_details'
  $fields['ting_object-ting_object-ting_details'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_details',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ting',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ting_details',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_details_default',
          'weight' => '10',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_details',
      'label' => 'Ting object details',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '10',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_subjects'
  $fields['ting_object-ting_object-ting_subjects'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_subjects',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ting',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ting_subjects',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_subjects_default',
          'weight' => '8',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_subjects',
      'label' => 'Subjects',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '8',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_title'
  $fields['ting_object-ting_object-ting_title'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_title',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ting',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ting_title',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_title_default',
          'weight' => '5',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_title',
      'label' => 'Ting object title',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '4',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_type'
  $fields['ting_object-ting_object-ting_type'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_type',
      'foreign keys' => array(),
      'indexes' => array(),
      'module' => 'ting',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'ting_type',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_type_default',
          'weight' => '4',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_type',
      'label' => 'Ting object type',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '5',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Availability information');
  t('Cover');
  t('Holdings information');
  t('Subjects');
  t('Ting object abstract');
  t('Ting object author');
  t('Ting object details');
  t('Ting object title');
  t('Ting object type');

  return $fields;
}
