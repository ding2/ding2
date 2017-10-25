<?php
/**
 * @file
 * ting_covers_custom.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ting_covers_custom_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ting_covers_custom_image'
  $field_bases['field_ting_covers_custom_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ting_covers_custom_image',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'profile2_private' => FALSE,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'field_ting_covers_custom_object'
  $field_bases['field_ting_covers_custom_object'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ting_covers_custom_object',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_reference',
    'settings' => array(
      'profile2_private' => FALSE,
      'relation_type' => 'ting_covers_custom_cover',
    ),
    'translatable' => 0,
    'type' => 'ting_reference',
  );

  return $field_bases;
}
