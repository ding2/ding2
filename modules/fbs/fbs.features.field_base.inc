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

  // Exported field_base: 'field_fbs_address'.
  $field_bases['field_fbs_address'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_address',
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

  // Exported field_base: 'field_fbs_interest_period'.
  $field_bases['field_fbs_interest_period'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_fbs_interest_period',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        30 => '1 Month',
        60 => '2 Months',
        90 => '3 Months',
        180 => '6 Months',
        360 => '12 Months',
      ),
      'allowed_values_function' => '',
      'profile2_private' => 0,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_fbs_mail'.
  $field_bases['field_fbs_mail'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_mail',
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

  // Exported field_base: 'field_fbs_mail_notification'.
  $field_bases['field_fbs_mail_notification'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_mail_notification',
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

  // Exported field_base: 'field_fbs_name'.
  $field_bases['field_fbs_name'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_name',
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

  // Exported field_base: 'field_fbs_on_hold'.
  $field_bases['field_fbs_on_hold'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_on_hold',
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

  // Exported field_base: 'field_fbs_phone'.
  $field_bases['field_fbs_phone'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_phone',
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

  // Exported field_base: 'field_fbs_phone_notification'.
  $field_bases['field_fbs_phone_notification'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_phone_notification',
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

  // Exported field_base: 'field_fbs_preferred_branch'.
  $field_bases['field_fbs_preferred_branch'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(
      0 => 'profile2',
    ),
    'field_name' => 'field_fbs_preferred_branch',
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
