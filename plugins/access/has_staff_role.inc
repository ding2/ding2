<?php
/**
 * @file
 * Ctools access plugin to provide access if user has role: staff.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User: has staff role'),
  'description' => t('Check if user has the staff role.'),
  'callback' => 'ding_staff_user_has_staff_role_access_check',
  'summary' => 'ding_staff_user_has_staff_role_access_summary',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
);

/**
 * Check the access.
 */
function ding_staff_user_has_staff_role_access_check($conf, $context) {
  if (empty($context) || empty($context[0]->data)) {
    return FALSE;
  }
  $roles = $context[0]->data->roles;
  return in_array('staff', $roles);
}

/**
 * Describe an instance of this plugin.
 */
function ding_staff_user_has_staff_role_access_summary($conf, $context) {
  return t('User has the staff role');
}
