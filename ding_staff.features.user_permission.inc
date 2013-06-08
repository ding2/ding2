<?php
/**
 * @file
 * ding_staff.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_staff_user_default_permissions() {
  $permissions = array();

  // Exported permission: delete terms in 6.
  $permissions['delete terms in 6'] = array(
    'name' => 'delete terms in 6',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit any staff profile.
  $permissions['edit any staff profile'] = array(
    'name' => 'edit any staff profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit own staff profile.
  $permissions['edit own staff profile'] = array(
    'name' => 'edit own staff profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit terms in 6.
  $permissions['edit terms in 6'] = array(
    'name' => 'edit terms in 6',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: view any staff profile.
  $permissions['view any staff profile'] = array(
    'name' => 'view any staff profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view own staff profile.
  $permissions['view own staff profile'] = array(
    'name' => 'view own staff profile',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'profile2',
  );

  return $permissions;
}
