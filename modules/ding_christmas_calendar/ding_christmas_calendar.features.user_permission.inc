<?php
/**
 * @file
 * ding_christmas_calendar.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_christmas_calendar_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access quiz'.
  $permissions['access quiz'] = array(
    'name' => 'access quiz',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view own quiz results'.
  $permissions['view own quiz results'] = array(
    'name' => 'view own quiz results',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  return $permissions;
}
