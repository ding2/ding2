<?php
/**
 * @file
 * fbs.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function fbs_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_fbs_address'
  $field_bases['field_fbs_address'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_address',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
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
    'type' => 'fbs_address',
  );

  // Exported field_base: 'field_fbs_mail'
  $field_bases['field_fbs_mail'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_mail',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
    'settings' => array(
      'max_length' => 255,
      'profile2_private' => 0,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'fbs_mail',
  );

  // Exported field_base: 'field_fbs_mail_notification'
  $field_bases['field_fbs_mail_notification'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_mail_notification',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
    'settings' => array(
      'profile2_private' => 0,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'fbs_mail_notification',
  );

  // Exported field_base: 'field_fbs_name'
  $field_bases['field_fbs_name'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_name',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
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
    'type' => 'fbs_name',
  );

  // Exported field_base: 'field_fbs_on_hold'
  $field_bases['field_fbs_on_hold'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_on_hold',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
    'settings' => array(
      'profile2_private' => 0,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'fbs_on_hold',
  );

  // Exported field_base: 'field_fbs_phone'
  $field_bases['field_fbs_phone'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_phone',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
    'settings' => array(
      'max_length' => 255,
      'profile2_private' => 0,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'fbs_phone',
  );

  // Exported field_base: 'field_fbs_phone_notification'
  $field_bases['field_fbs_phone_notification'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_phone_notification',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
    'settings' => array(
      'profile2_private' => 0,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'fbs_phone_notification',
  );

  // Exported field_base: 'field_fbs_preferred_branch'
  $field_bases['field_fbs_preferred_branch'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_preferred_branch',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'fbs',
    'settings' => array(
      'profile2_private' => 0,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'virtual_field',
    ),
    'translatable' => 0,
    'type' => 'fbs_preferred_branch',
  );

  return $field_bases;
}
