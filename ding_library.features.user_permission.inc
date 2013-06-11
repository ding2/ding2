<?php
/**
 * @file
 * ding_library.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_library_user_default_permissions() {
  $permissions = array();

  // Exported permission: create ding_library content.
  $permissions['create ding_library content'] = array(
    'name' => 'create ding_library content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any ding_library content.
  $permissions['delete any ding_library content'] = array(
    'name' => 'delete any ding_library content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own ding_library content.
  $permissions['delete own ding_library content'] = array(
    'name' => 'delete own ding_library content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any ding_library content.
  $permissions['edit any ding_library content'] = array(
    'name' => 'edit any ding_library content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own ding_library content.
  $permissions['edit own ding_library content'] = array(
    'name' => 'edit own ding_library content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  return $permissions;
}
