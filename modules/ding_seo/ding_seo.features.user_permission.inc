<?php
/**
 * @file
 * ding_seo.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_seo_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'configure seo'.
  $permissions['configure seo'] = array(
    'name' => 'configure seo',
    'roles' => array(
      'administrators' => 'administrators',
      'local administrator' => 'local administrator',
    ),
    'module' => 'ding_seo',
  );

  return $permissions;
}