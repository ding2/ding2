<?php

$plugin = array(
  'title' => t('Ting field search profile: name'),
  'keyword' => 'ting_field_search_profile',
  'description' => t('Creates a Ting field search profile from a profile machine-name argument.'),
  'context' => 'ting_field_search_argument_profile_name_context',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter a Ting object ID for this argument'),
  ),
);

function ting_field_search_argument_profile_name_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  if ($empty) {
    return ctools_context_create_empty('ting_field_search_profile');
  }

  // We can accept either a node object or a pure nid.
  if (is_object($arg)) {
    return ctools_context_create('ting_field_search_profile', $arg);
  }

  if (!is_string($arg)) {
    return FALSE;
  }

  $profile = ting_field_search_profiles_load($arg);
  if (!$profile) {
    return FALSE;
  }

  return ctools_context_create('ting_field_search_profile', $profile);
}
