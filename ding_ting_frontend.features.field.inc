<?php
/**
 * @file
 * ding_ting_frontend.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function ding_ting_frontend_field_default_fields() {
  $fields = array();

  // Exported field: 'ting_collection-ting_collection-ting_collection_types'.
  $fields['ting_collection-ting_collection-ting_collection_types'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_collection_types',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ting_collection_types',
    ),
    'field_instance' => array(
      'bundle' => 'ting_collection',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity_collection',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
        'teaser' => array(
          'label' => 'inline',
          'module' => 'ding_availability',
          'settings' => array(
            'link' => 1,
          ),
          'type' => 'ding_availability_types',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'ting_collection',
      'field_name' => 'ting_collection_types',
      'label' => 'Ting collection object types',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
  );

  // Exported field: 'ting_collection-ting_collection-ting_entities'.
  $fields['ting_collection-ting_collection-ting_entities'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_entities',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ting_entities',
    ),
    'field_instance' => array(
      'bundle' => 'ting_collection',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity_collection',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'hide_primary' => 0,
            'view_mode' => 'collection_list',
          ),
          'type' => 'ting_entities_default',
          'weight' => '0',
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
      ),
      'entity_type' => 'ting_collection',
      'field_name' => 'ting_entities',
      'label' => 'All materials',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
  );

  // Exported field: 'ting_collection-ting_collection-ting_primary_object'.
  $fields['ting_collection-ting_collection-ting_primary_object'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_primary_object',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ting_primary_object',
    ),
    'field_instance' => array(
      'bundle' => 'ting_collection',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity_collection',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '2',
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'view_mode' => 'search_result',
          ),
          'type' => 'ting_primary_object_default',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'ting_collection',
      'field_name' => 'ting_primary_object',
      'label' => 'Ting collection primary object',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ding_availability_holdings'.
  $fields['ting_object-ting_object-ding_availability_holdings'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ding_availability_holdings',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ding_availability',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
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
          'weight' => '8',
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ding_availability',
          'settings' => array(),
          'type' => 'ding_availability_default',
          'weight' => '11',
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
          'weight' => '8',
        ),
        'user_list' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '8',
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
        'weight' => '7',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ding_entity_buttons'.
  $fields['ting_object-ting_object-ding_entity_buttons'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ding_entity_buttons',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ding_entity',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ding_entity_buttons',
    ),
    'field_instance' => array(
      'bundle' => 'ting_object',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'ding_entity_type' => 'ding_entity',
      'display' => array(
        'collection_list' => array(
          'label' => 'hidden',
          'module' => 'ding_entity',
          'settings' => array(),
          'type' => 'ding_entity_buttons_default',
          'weight' => '6',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ding_entity',
          'settings' => array(),
          'type' => 'ding_entity_buttons_default',
          'weight' => '6',
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
          'weight' => 0,
        ),
        'user_list' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '6',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ding_entity_buttons',
      'label' => 'Action buttons',
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

  // Exported field: 'ting_object-ting_object-ding_periodical_issues'.
  $fields['ting_object-ting_object-ding_periodical_issues'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ding_periodical_issues',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ding_periodical',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ding_periodical_issues',
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
          'weight' => '8',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'default' => array(
          'label' => 'above',
          'module' => 'ding_periodical',
          'settings' => array(),
          'type' => 'ding_periodical_issues_default',
          'weight' => '9',
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
          'weight' => 0,
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '5',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ding_periodical_issues',
      'label' => 'Issues',
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

  // Exported field: 'ting_object-ting_object-ting_abstract'.
  $fields['ting_object-ting_object-ting_abstract'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_abstract',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
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
        'collection_list' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_abstract_default',
          'weight' => '4',
        ),
        'collection_primary' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_abstract_default',
          'weight' => '4',
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_abstract_default',
          'weight' => '4',
        ),
        'search_result' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_abstract_default',
          'weight' => '3',
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_abstract_default',
          'weight' => '3',
        ),
        'user_list' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '11',
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
        'weight' => '3',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_author'.
  $fields['ting_object-ting_object-ting_author'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_author',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
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
        'collection_list' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_author_default',
          'weight' => '3',
        ),
        'collection_primary' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_author_default',
          'weight' => '3',
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_author_default',
          'weight' => '3',
        ),
        'search_result' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_author_default',
          'weight' => '2',
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_author_default',
          'weight' => '2',
        ),
        'user_list' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_author_default',
          'weight' => '3',
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
        'weight' => '4',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_cover'.
  $fields['ting_object-ting_object-ting_cover'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_cover',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
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
        'collection_list' => array(
          'label' => 'hidden',
          'module' => 'ting_covers',
          'settings' => array(
            'image_style' => 'ding_medium',
          ),
          'type' => 'ting_cover_default',
          'weight' => '0',
        ),
        'collection_primary' => array(
          'label' => 'hidden',
          'module' => 'ting_covers',
          'settings' => array(
            'image_style' => 'ding_large',
          ),
          'type' => 'ting_cover_default',
          'weight' => '0',
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting_covers',
          'settings' => array(
            'image_style' => 'ding_large',
          ),
          'type' => 'ting_cover_default',
          'weight' => '0',
        ),
        'search_result' => array(
          'label' => 'hidden',
          'module' => 'ting_covers',
          'settings' => array(
            'image_style' => 'ding_medium',
          ),
          'type' => 'ting_cover_default',
          'weight' => '1',
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'ting_covers',
          'settings' => array(
            'image_style' => 'ding_medium',
          ),
          'type' => 'ting_cover_default',
          'weight' => '0',
        ),
        'user_list' => array(
          'label' => 'hidden',
          'module' => 'ting_covers',
          'settings' => array(
            'image_style' => 'ding_small',
          ),
          'type' => 'ting_cover_default',
          'weight' => '0',
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
        'weight' => '0',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_reference_reverse'.
  $fields['ting_object-ting_object-ting_reference_reverse'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_reference_reverse',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting_reference',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ting_reference_reverse',
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
          'weight' => 0,
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'default' => array(
          'label' => 'above',
          'module' => 'ting_reference',
          'settings' => array(),
          'type' => 'ting_reference_reverse_default',
          'weight' => '8',
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
          'weight' => 0,
        ),
        'user_list' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_reference_reverse',
      'label' => 'On this site',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '11',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_relations'.
  $fields['ting_object-ting_object-ting_relations'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_relations',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting_relation',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ting_relations',
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
          'weight' => '7',
        ),
        'collection_primary' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting_relation',
          'settings' => array(),
          'type' => 'ting_relations_default',
          'weight' => '12',
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
          'weight' => 0,
        ),
        'user_list' => array(
          'label' => 'hidden',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '9',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_relations',
      'label' => 'Ting relations.',
      'required' => FALSE,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '12',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_series'.
  $fields['ting_object-ting_object-ting_series'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_series',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
      'translatable' => '0',
      'type' => 'ting_series',
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
          'weight' => 0,
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_series_default',
          'weight' => '10',
        ),
        'search_result' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_series_default',
          'weight' => '4',
        ),
        'teaser' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_series_default',
          'weight' => '2',
        ),
        'user_list' => array(
          'label' => 'inline',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '7',
        ),
      ),
      'entity_type' => 'ting_object',
      'field_name' => 'ting_series',
      'label' => 'Series',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => '10',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_subjects'.
  $fields['ting_object-ting_object-ting_subjects'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_subjects',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
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
        'collection_list' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_subjects_default',
          'weight' => '5',
        ),
        'collection_primary' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_subjects_default',
          'weight' => '5',
        ),
        'default' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_subjects_default',
          'weight' => '5',
        ),
        'search_result' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_subjects_default',
          'weight' => '5',
        ),
        'teaser' => array(
          'label' => 'inline',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_subjects_default',
          'weight' => '4',
        ),
        'user_list' => array(
          'label' => 'inline',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '10',
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
        'weight' => '5',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_title'.
  $fields['ting_object-ting_object-ting_title'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_title',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
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
        'collection_list' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'link_type' => 'object',
          ),
          'type' => 'ting_title_default',
          'weight' => '2',
        ),
        'collection_primary' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'link_type' => 'object',
          ),
          'type' => 'ting_title_default',
          'weight' => '2',
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'link_type' => 'object',
          ),
          'type' => 'ting_title_default',
          'weight' => '2',
        ),
        'search_result' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'link_type' => 'collection',
          ),
          'type' => 'ting_title_default',
          'weight' => '0',
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'link_type' => 'collection',
          ),
          'type' => 'ting_title_default',
          'weight' => '1',
        ),
        'user_list' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(
            'link_type' => 'object',
          ),
          'type' => 'ting_title_default',
          'weight' => '1',
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
        'weight' => '1',
      ),
    ),
  );

  // Exported field: 'ting_object-ting_object-ting_type'.
  $fields['ting_object-ting_object-ting_type'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'ting_type',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '1',
      'module' => 'ting',
      'settings' => array(),
      'storage' => array(
        'active' => '1',
        'module' => 'blackhole',
        'settings' => array(),
        'type' => 'blackhole',
      ),
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
        'collection_list' => array(
          'label' => 'hidden',
          'module' => 'ding_availability',
          'settings' => array(),
          'type' => 'ding_availability_type',
          'weight' => '1',
        ),
        'collection_primary' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_type_default',
          'weight' => '1',
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'ding_availability',
          'settings' => array(),
          'type' => 'ding_availability_type',
          'weight' => '1',
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
          'weight' => '5',
        ),
        'user_list' => array(
          'label' => 'hidden',
          'module' => 'ting',
          'settings' => array(),
          'type' => 'ting_type_default',
          'weight' => '2',
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
        'weight' => '2',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Action buttons');
  t('All materials');
  t('Cover');
  t('Holdings information');
  t('Issues');
  t('On this site');
  t('Series');
  t('Subjects');
  t('Ting collection object types');
  t('Ting collection primary object');
  t('Ting object abstract');
  t('Ting object author');
  t('Ting object title');
  t('Ting object type');
  t('Ting relations.');

  return $fields;
}
