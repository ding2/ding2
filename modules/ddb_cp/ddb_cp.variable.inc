<?php
/**
 * @file
 * ddb_cp.variable.inc
 */

/**
 * Implements hook_variable_realm_default_variables().
 */
function ddb_cp_variable_realm_default_variables() {
  $realm_variables = array();
  $realm_variables['environment']['default_environment'] = array();
  $realm_variables['environment']['development'] = array();
  $realm_variables['environment']['staging'] = array();

  return $realm_variables;
}
