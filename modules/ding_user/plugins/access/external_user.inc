<?php

/**
 * @file
 * Ctools access plugin to provide access if user is an external provided user.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User: is handled by external user'),
  'description' => t('Check if user is handled by an external user authentication service.'),
  'callback' => 'ding_user_external_user_access_check',
  'summary' => 'ding_user_external_user_access_summary',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
);

/**
 * Check the access.
 */
function ding_user_external_user_access_check($conf, $context) {
  if (empty($context) || empty($context[0]->data) || !user_is_logged_in()) {
    return FALSE;
  }
  return (user_get_authmaps($context[0]->data->init) xor $conf);
}

/**
 * Describe an instance of this plugin.
 */
function ding_user_external_user_access_summary($conf, $context) {
  return t('User is an external user');
}
