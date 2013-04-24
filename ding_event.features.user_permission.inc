<?php
/**
 * @file
 * ding_event.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_event_user_default_permissions() {
  $permissions = array();

  // Exported permission: create ding_event content.
  $permissions['create ding_event content'] = array(
    'name' => 'create ding_event content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any ding_event content.
  $permissions['delete any ding_event content'] = array(
    'name' => 'delete any ding_event content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own ding_event content.
  $permissions['delete own ding_event content'] = array(
    'name' => 'delete own ding_event content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any ding_event content.
  $permissions['edit any ding_event content'] = array(
    'name' => 'edit any ding_event content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own ding_event content.
  $permissions['edit own ding_event content'] = array(
    'name' => 'edit own ding_event content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
