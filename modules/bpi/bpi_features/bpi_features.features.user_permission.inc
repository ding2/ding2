<?php
/**
 * @file
 * bpi_features.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function bpi_features_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access workflow summary views'.
  $permissions['access workflow summary views'] = array(
    'name' => 'access workflow summary views',
    'roles' => array(),
    'module' => 'workflow_views',
  );

  // Exported permission: 'administer workflow'.
  $permissions['administer workflow'] = array(
    'name' => 'administer workflow',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
      'local editor' => 'local editor',
      'staff' => 'staff',
    ),
    'module' => 'workflow_admin_ui',
  );

  // Exported permission: 'edit workflow comment'.
  $permissions['edit workflow comment'] = array(
    'name' => 'edit workflow comment',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
      'local editor' => 'local editor',
      'staff' => 'staff',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'participate in workflow'.
  $permissions['participate in workflow'] = array(
    'name' => 'participate in workflow',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'guest blogger' => 'guest blogger',
      'local administrator' => 'local administrator',
      'local editor' => 'local editor',
      'provider' => 'provider',
      'staff' => 'staff',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'schedule workflow transitions'.
  $permissions['schedule workflow transitions'] = array(
    'name' => 'schedule workflow transitions',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
      'local editor' => 'local editor',
      'staff' => 'staff',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'show workflow state form'.
  $permissions['show workflow state form'] = array(
    'name' => 'show workflow state form',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'guest blogger' => 'guest blogger',
      'local administrator' => 'local administrator',
      'local editor' => 'local editor',
      'provider' => 'provider',
      'staff' => 'staff',
    ),
    'module' => 'workflow',
  );

  return $permissions;
}
