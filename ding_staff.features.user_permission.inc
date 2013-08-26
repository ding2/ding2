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

  // Exported permission: assign all roles.
  $permissions['assign all roles'] = array(
    'name' => 'assign all roles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: assign formidler role.
  $permissions['assign formidler role'] = array(
    'name' => 'assign formidler role',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: assign gæsteblogger role.
  $permissions['assign gæsteblogger role'] = array(
    'name' => 'assign gæsteblogger role',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: assign lokalredaktør role.
  $permissions['assign lokalredaktør role'] = array(
    'name' => 'assign lokalredaktør role',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: assign redaktør role.
  $permissions['assign redaktør role'] = array(
    'name' => 'assign redaktør role',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: assign staff role.
  $permissions['assign staff role'] = array(
    'name' => 'assign staff role',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: edit any ding_staff_profile profile.
  $permissions['edit any ding_staff_profile profile'] = array(
    'name' => 'edit any ding_staff_profile profile',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'profile2',
  );

  // Exported permission: edit own ding_staff_profile profile.
  $permissions['edit own ding_staff_profile profile'] = array(
    'name' => 'edit own ding_staff_profile profile',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view any ding_staff_profile profile.
  $permissions['view any ding_staff_profile profile'] = array(
    'name' => 'view any ding_staff_profile profile',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'profile2',
  );

  // Exported permission: view own ding_staff_profile profile.
  $permissions['view own ding_staff_profile profile'] = array(
    'name' => 'view own ding_staff_profile profile',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'profile2',
  );

  return $permissions;
}
