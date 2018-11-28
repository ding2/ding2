<?php
/**
 * @file
 * ding_list.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ding_list_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ding_list_in_public_lists'.
  $field_bases['field_ding_list_in_public_lists'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'ting_object',
    ),
    'field_name' => 'field_ding_list_in_public_lists',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ding_list',
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
    'type' => 'ding_list_in_public_lists',
  );

  return $field_bases;
}
