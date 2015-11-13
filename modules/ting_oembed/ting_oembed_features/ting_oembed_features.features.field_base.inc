<?php
/**
 * @file
 * ting_oembed_features.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ting_oembed_features_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ting_oembed_oembed'
  $field_bases['field_ting_oembed_oembed'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'ting_object',
    ),
    'field_name' => 'field_ting_oembed_oembed',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_oembed',
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
    'type' => 'ting_oembed',
  );

  return $field_bases;
}
