<?php

/**
 * @file
 * Plugin to provide access control to a profile page based on whether the
 * page is enabled in profile config.
 */

$plugin = array(
  'title' => t('Profile page'),
  'description' => t('Controls access to profile page based on settings in profile config.'),
  'callback' => 'ting_field_search_profile_page_access_check',
  'settings form' => 'ting_field_search_profile_page_access_settings',
  'summary' => 'ting_field_search_profile_page_access_summary',
  'required context' => new ctools_context_required(t('Ting field search profile'), 'ting_field_search_profile'),
);

function ting_field_search_profile_page_access_check($conf, $context) {
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }

  return $context->data->config['profile_page']['enabled'];
}

function ting_field_search_profile_page_access_settings(&$form, &$form_state, $conf) {
  return $form;
}

function ting_field_search_profile_page_access_summary($conf, $context) {
  return t('Ting field search profile has enabled profile page.');
}
