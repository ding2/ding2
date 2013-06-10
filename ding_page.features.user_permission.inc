<?php
/**
 * @file
 * ding_page.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_page_user_default_permissions() {
  $permissions = array();

  // Exported permission: create ding_page content.
  $permissions['create ding_page content'] = array(
    'name' => 'create ding_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any ding_page content.
  $permissions['delete any ding_page content'] = array(
    'name' => 'delete any ding_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own ding_page content.
  $permissions['delete own ding_page content'] = array(
    'name' => 'delete own ding_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any ding_page content.
  $permissions['edit any ding_page content'] = array(
    'name' => 'edit any ding_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own ding_page content.
  $permissions['edit own ding_page content'] = array(
    'name' => 'edit own ding_page content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  return $permissions;
}
