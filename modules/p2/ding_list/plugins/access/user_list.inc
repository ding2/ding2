<?php

/**
 * @file
 * Plugin to provide access control based on user lists.
 */

$plugin = array(
  'title' => t("User: list"),
  'description' => t('Control access by to user lists.'),
  'callback' => 'ding_list_user_list_ctools_access_check',
  'settings form' => 'ding_list_user_list_ctools_access_settings',
  'summary' => 'ding_list_user_list_ctools_access_summary',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
    new ctools_context_required(t('Dinglist'), 'ding_type'),
  ),
  'defaults' => array(
    'visibility_settings' => 'view',
  ),
);

/**
 * Settings form for the 'by perm' access plugin.
 */
function ding_list_user_list_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['visibility_settings'] = array(
    '#type' => 'radios',
    '#title' => t('Visibility settings for the list'),
    '#options' => array(
      DING_LIST_PERMISSION_VIEW => t('View'),
      DING_LIST_PERMISSION_EDIT => t('Edit'),
      DING_LIST_PERMISSION_OWNER => t('Owner'),
    ),
    '#default_value' => $conf['visibility_settings'],
  );

  return $form;
}

/**
 * Check for access.
 */
function ding_list_user_list_ctools_access_check($conf, $context) {
  if (empty($context)) {
    return FALSE;
  }

  $account = $context[0]->data;
  $list = $context[1]->data;

  // Reload the entity if the uid is missing.
  if ($list->uid == 0) {
    $tmp = entity_load('ding_type', array($list->id), array(), TRUE);
    $list = reset($tmp);
  }

  $token = isset($_GET['token']) ? $_GET['token'] : FALSE;

  if ($token === FALSE) {
    // Try to get the token from the destination.
    $destination = drupal_get_destination();
    if (!empty($destination['destination'])) {
      $destination = drupal_parse_url($destination['destination']);
      if (isset($destination['query']['token'])) {
        $token = $destination['query']['token'];
      }
    }
  }

  $result = ding_list_user_has_access($list, $conf['visibility_settings'], $account, $token);

  if (!$result) {
    drupal_set_message(t('The list is no longer public or shared.'));
  }

  // Prevent back button from displaying the pages.
  if (arg(0) === 'list' && user_is_logged_in()) {
    drupal_add_http_header('Cache-Control', 'no-store, must-revalidate');
    drupal_add_http_header('Pragma', 'no-cache');
  }

  return $result;
}

/**
 * Provide a summary description based upon the checked roles.
 */
function ding_list_user_list_ctools_access_summary($conf, $context) {
  return t('@identifier @setting', array('@identifier' => $context[0]->identifier, '@setting' => $conf['visibility_settings']));
}
