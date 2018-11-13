<?php

/**
 * @file
 * Plugin to provide access control based on user lists.
 */

$plugin = array(
  'title' => t("User: reset list"),
  'description' => t('Control list resets.'),
  'callback' => 'ding_list_reset_lists_ctools_access_check',
  'settings form' => 'ding_list_reset_lists_ctools_access_settings',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
  ),
);

/**
 * Settings form for the 'by perm' access plugin.
 */
function ding_list_reset_lists_ctools_access_settings($form, &$form_state, $conf) {
  return $form;
}

/**
 * Check for access.
 */
function ding_list_reset_lists_ctools_access_check($conf, $context) {
  return ding_list_reset_lists_access($context[0]->data);
}
