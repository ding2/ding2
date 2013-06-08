<?php
/**
 * @file
 * ding_campaign_ctype.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_campaign_ctype_user_default_permissions() {
  $permissions = array();

  // Exported permission: create ding_campaign content.
  $permissions['create ding_campaign content'] = array(
    'name' => 'create ding_campaign content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any ding_campaign content.
  $permissions['delete any ding_campaign content'] = array(
    'name' => 'delete any ding_campaign content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own ding_campaign content.
  $permissions['delete own ding_campaign content'] = array(
    'name' => 'delete own ding_campaign content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any ding_campaign content.
  $permissions['edit any ding_campaign content'] = array(
    'name' => 'edit any ding_campaign content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own ding_campaign content.
  $permissions['edit own ding_campaign content'] = array(
    'name' => 'edit own ding_campaign content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  return $permissions;
}
