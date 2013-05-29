<?php
/**
 * @file
 * ding_staff.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ding_staff_user_default_roles() {
  $roles = array();

  // Exported role: staff.
  $roles['staff'] = array(
    'name' => 'staff',
    'weight' => 7,
  );

  return $roles;
}
