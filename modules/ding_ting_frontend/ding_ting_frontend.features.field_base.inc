<?php
/**
 * @file
 * ding_ting_frontend.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ding_ting_frontend_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'ding_availability_holdings'
  $field_bases['ding_availability_holdings'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ding_availability_holdings',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ding_availability',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ding_availability_holdings',
  );

  // Exported field_base: 'ding_entity_buttons'
  $field_bases['ding_entity_buttons'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ding_entity_buttons',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ding_entity',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ding_entity_buttons',
  );

  // Exported field_base: 'ding_periodical_issues'
  $field_bases['ding_periodical_issues'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ding_periodical_issues',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ding_periodical',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ding_periodical_issues',
  );

  // Exported field_base: 'ting_abstract'
  $field_bases['ting_abstract'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_abstract',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_abstract',
  );

  // Exported field_base: 'ting_author'
  $field_bases['ting_author'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_author',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_author',
  );

  // Exported field_base: 'ting_collection_types'
  $field_bases['ting_collection_types'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_collection_types',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_collection_types',
  );

  // Exported field_base: 'ting_cover'
  $field_bases['ting_cover'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_cover',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_covers',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'ting_cover',
  );

  // Exported field_base: 'ting_entities'
  $field_bases['ting_entities'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_entities',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_entities',
  );

  // Exported field_base: 'ting_primary_object'
  $field_bases['ting_primary_object'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_primary_object',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_primary_object',
  );

  // Exported field_base: 'ting_reference_reverse'
  $field_bases['ting_reference_reverse'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_reference_reverse',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_reference',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_reference_reverse',
  );

  // Exported field_base: 'ting_relations'
  $field_bases['ting_relations'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_relations',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_relation',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_relations',
  );

  // Exported field_base: 'ting_series'
  $field_bases['ting_series'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_series',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_series',
  );

  // Exported field_base: 'ting_subjects'
  $field_bases['ting_subjects'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_subjects',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_subjects',
  );

  // Exported field_base: 'ting_title'
  $field_bases['ting_title'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_title',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_title',
  );

  // Exported field_base: 'ting_type'
  $field_bases['ting_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_type',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_type',
  );

  return $field_bases;
}
