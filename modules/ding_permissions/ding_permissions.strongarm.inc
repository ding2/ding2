<?php
/**
 * @file
 * ding_permissions.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_permissions_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'secure_permissions_active';
  $strongarm->value = 1;
  $export['secure_permissions_active'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'secure_permissions_disable_forms';
  $strongarm->value = 1;
  $export['secure_permissions_disable_forms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'secure_permissions_show_permissions_page';
  $strongarm->value = 1;
  $export['secure_permissions_show_permissions_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'secure_permissions_show_roles_page';
  $strongarm->value = 1;
  $export['secure_permissions_show_roles_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'secure_permissions_use_default';
  $strongarm->value = 0;
  $export['secure_permissions_use_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'secure_permissions_verbose';
  $strongarm->value = 0;
  $export['secure_permissions_verbose'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_node_access_strict';
  $strongarm->value = 0;
  $export['og_node_access_strict'] = $strongarm;

  return $export;
}
