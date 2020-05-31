<?php
/**
 * @file
 * smart_search_string.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function smart_search_string_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'configure smart search'.
  $permissions['configure smart search'] = array(
    'name' => 'configure smart search',
    'roles' => array(
      'administrators' => 'administrators',
    ),
    'module' => 'ting_smart_search',
  );

  return $permissions;
}
