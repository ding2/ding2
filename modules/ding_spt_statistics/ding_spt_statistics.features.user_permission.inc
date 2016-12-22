<?php
/**
 * @file
 * ding_spt_statistics.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_spt_statistics_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'view spt statistics'.
  $permissions['view spt statistics'] = array(
    'name' => 'view spt statistics',
    'roles' => array(
      'administrators' => 'administrators',
      'local administrator' => 'local administrator',
    ),
    'module' => 'ding_spt_statistics',
  );

  return $permissions;
}
