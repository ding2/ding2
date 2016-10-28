<?php
/**
 * @file
 * connie.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function connie_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'connie_preferred_branch'
  $field_bases['connie_preferred_branch'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'connie_preferred_branch',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(),
      'allowed_values_function' => 'connie_allowed_branches',
      'profile2_private' => 0,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
