<?php
/**
 * @file
 * ding_news.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_news_user_default_permissions() {
  $permissions = array();

  // Exported permission: create ding_news content.
  $permissions['create ding_news content'] = array(
    'name' => 'create ding_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any ding_news content.
  $permissions['delete any ding_news content'] = array(
    'name' => 'delete any ding_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own ding_news content.
  $permissions['delete own ding_news content'] = array(
    'name' => 'delete own ding_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any ding_news content.
  $permissions['edit any ding_news content'] = array(
    'name' => 'edit any ding_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own ding_news content.
  $permissions['edit own ding_news content'] = array(
    'name' => 'edit own ding_news content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
