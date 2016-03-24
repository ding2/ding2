<?php
/**
 * @file
 * ding_dashboard_comments.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_dashboard_comments_user_default_permissions() {
  $permissions = array();

  // Exported permission: access dashboard comments.
  $permissions['access dashboard comments'] = array(
    'name' => 'access dashboard comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
      2 => 'journalist',
      3 => 'local administrator',
    ),
    'module' => 'ding_dashboard_comments',
  );

  // Exported permission: administer dashboard comments.
  $permissions['administer dashboard comments'] = array(
    'name' => 'administer dashboard comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'editor',
      2 => 'journalist',
      3 => 'local administrator',
    ),
    'module' => 'ding_dashboard_comments',
  );

  return $permissions;
}
