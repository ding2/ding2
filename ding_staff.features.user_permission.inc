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
