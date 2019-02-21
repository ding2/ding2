<?php
/**
 * @file
 * ding_sections_og_integration.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function ding_sections_og_integration_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:subscribe without approval'
  $permissions['node:section:subscribe without approval'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  return $permissions;
}
