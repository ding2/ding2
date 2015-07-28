<?php
/**
 * @file
 * ting_material_details.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ting_material_details_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'ting_details_age'
  $field_bases['ting_details_age'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_age',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_age',
  );

  // Exported field_base: 'ting_details_audience'
  $field_bases['ting_details_audience'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_audience',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_audience',
  );

  // Exported field_base: 'ting_details_classification'
  $field_bases['ting_details_classification'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_classification',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_classification',
  );

  // Exported field_base: 'ting_details_contributor'
  $field_bases['ting_details_contributor'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_contributor',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_contributor',
  );

  // Exported field_base: 'ting_details_description'
  $field_bases['ting_details_description'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_description',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_description',
  );

  // Exported field_base: 'ting_details_extent'
  $field_bases['ting_details_extent'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_extent',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_extent',
  );

  // Exported field_base: 'ting_details_format'
  $field_bases['ting_details_format'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_format',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_format',
  );

  // Exported field_base: 'ting_details_genre'
  $field_bases['ting_details_genre'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_genre',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_genre',
  );

  // Exported field_base: 'ting_details_isbn'
  $field_bases['ting_details_isbn'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_isbn',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_isbn',
  );

  // Exported field_base: 'ting_details_ispartof'
  $field_bases['ting_details_ispartof'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_ispartof',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_ispartof',
  );

  // Exported field_base: 'ting_details_language'
  $field_bases['ting_details_language'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_language',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_language',
  );

  // Exported field_base: 'ting_details_musician'
  $field_bases['ting_details_musician'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_musician',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_musician',
  );

  // Exported field_base: 'ting_details_pegi'
  $field_bases['ting_details_pegi'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_pegi',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_pegi',
  );

  // Exported field_base: 'ting_details_publisher'
  $field_bases['ting_details_publisher'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_publisher',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_publisher',
  );

  // Exported field_base: 'ting_details_referenced'
  $field_bases['ting_details_referenced'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_referenced',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_referenced',
  );

  // Exported field_base: 'ting_details_replaced_by'
  $field_bases['ting_details_replaced_by'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_replaced_by',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_replaced_by',
  );

  // Exported field_base: 'ting_details_replaces'
  $field_bases['ting_details_replaces'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_replaces',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_replaces',
  );

  // Exported field_base: 'ting_details_rights'
  $field_bases['ting_details_rights'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_rights',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_rights',
  );

  // Exported field_base: 'ting_details_source'
  $field_bases['ting_details_source'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_source',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_source',
  );

  // Exported field_base: 'ting_details_spatial'
  $field_bases['ting_details_spatial'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_spatial',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_spatial',
  );

  // Exported field_base: 'ting_details_spoken'
  $field_bases['ting_details_spoken'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_spoken',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_spoken',
  );

  // Exported field_base: 'ting_details_subjects'
  $field_bases['ting_details_subjects'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_subjects',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_subjects',
  );

  // Exported field_base: 'ting_details_subtitles'
  $field_bases['ting_details_subtitles'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_subtitles',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_subtitles',
  );

  // Exported field_base: 'ting_details_tracks'
  $field_bases['ting_details_tracks'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_tracks',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_tracks',
  );

  // Exported field_base: 'ting_details_type'
  $field_bases['ting_details_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_type',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_type',
  );

  // Exported field_base: 'ting_details_uri'
  $field_bases['ting_details_uri'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_uri',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_uri',
  );

  // Exported field_base: 'ting_details_version'
  $field_bases['ting_details_version'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ting_details_version',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_material_details',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ting_details_version',
  );

  return $field_bases;
}
