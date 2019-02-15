<?php
/**
 * @file
 * ding_place2book.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_place2book_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer place2book settings'.
  $permissions['administer place2book settings'] = array(
    'name' => 'administer place2book settings',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'ding_place2book',
  );

  return $permissions;
}
