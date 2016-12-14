<?php
/**
 * @file
 * ding_entity_rating.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ding_entity_rating_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'ding_entity_rating_action'
  $field_bases['ding_entity_rating_action'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ding_entity_rating_action',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'ding_entity_rating',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ding_entity_rating_action',
  );

  // Exported field_base: 'ding_entity_rating_result'
  $field_bases['ding_entity_rating_result'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'ding_entity_rating_result',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 1,
    'module' => 'ding_entity_rating',
    'settings' => array(),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'ding_entity_rating_result',
  );

  return $field_bases;
}
