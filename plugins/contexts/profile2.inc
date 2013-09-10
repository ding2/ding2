<?php

/**
 * @file
 * Plugin to provide a profile2 type context
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Profile2 type"),
  'description' => t('Detect profile 2 type (edit form).'),
  'context' => 'ding_user_contexts_profile2',
  'edit form' => 'ding_user_contexts_profile2_settings_form',
  'keyword' => 'user',
  'context name' => 'profile2_type',
  'convert list' => 'ding_user_contexts_profile2_convert_list',
  'convert' => 'ding_user_contexts_profile2_convert',
);

/**
 * Create context based on the path and the configuration settings.
 */
function ding_user_contexts_profile2($empty, $data = NULL, $conf = FALSE) {
  // Create context object.
  $context = new ctools_context(array('profile2_type', 'entity:profile2_type'));
  $context->plugin = 'profile2_type';

  if (!$empty) {
    if (!empty($data)) {
      // Create data object.
      $context->data = new stdClass();
    }

    // Try the load profile based on path.
    $args = arg();
    $type = array_pop($args);
    $profile_type = profile2_type_load($type);

    // If profile was not load try loading the default provider profile.
    global $user;
    if (!$profile_type && ding_user_is_provider_user($user)) {
      $profile_type = ding_user_get_provider_profile_type();
    }

    // Set the context if profile type was loaded.
    if ($profile_type) {
      $context->data->profile_name = $profile_type->type;
      $context->data->profile_type = $profile_type;
    }
  }

  return $context;
}

/**
 * Setting form for the context.
 */
function ding_user_contexts_profile2_settings_form($form, &$form_state) {
  // Provide a blank form so we have a place to override title
  // and stuff.
  return $form;
}

/**
 * Provide a list of replacements.
 */
function ding_user_contexts_profile2_convert_list() {
  return array(
    'profile_name' => t('Profile type name'),
    'profile_type' => t('Profile type object'),
  );
}

/**
 * Convert a context into a string.
 */
function ding_user_contexts_profile2_convert($context, $type) {
  return $context->$type;
}
