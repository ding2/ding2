<?php
/**
 * @file
 * ding_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer fe promote'.
  $permissions['administer fe promote'] = array(
    'name' => 'administer fe promote',
    'roles' => array(
      'administrators' => 'administrators',
      'local administrator' => 'local administrator',
    ),
    'module' => 'ding_frontend',
  );

  return $permissions;
}
