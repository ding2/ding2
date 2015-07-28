<?php
/**
 * @file
 * Wraps the provider profile2 edit form in a panel pane.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User edit form (with profile2 support)'),
  'icon' => 'icon_form.png',
  'description' => t('User edit form that have support for profile2 forms.'),
  'render callback' => 'ding_user_profile2_form_content_type_render',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
    new ctools_context_optional(t("Profile2 type"), 'profile2_type'),
  ),
  'category' => t('Form'),
);

/**
 * Implements render for the pane and loads the profile2 profile edit form.
 */
function ding_user_profile2_form_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $form = array();

  // If profile context exists, try getting the form for that profile.
  if (isset($context[1]->data->profile_name)) {
    $profile_type = $context[1]->data;

    // Try to load profile if one exists for the current user.
    $profile = profile2_load_by_user($context[0]->data, $profile_type->profile_name);
    if ($profile) {
      // Get form with the load profile information filled in.
      $form = entity_ui_get_form('profile2', $profile);
    }
    else {
      // Create new empty profile with the profile type.
      $profile = profile2_create(array(
        'user' => $context[0]->data,
        'type' => $profile_type->profile_type,
        'label' => $profile_type->profile_type->label,
      ));

      // Build form based on the empty profile.
      $form = entity_ui_get_form('profile2', $profile);
    }

    // Set block delta and title.
    $block->title = $profile_type->profile_type->label;
    $block->delta = $form['#form_id'];
  }
  else {
    // Build the default user edit form (reused form the ctools form plugin).
    if (isset($context[0]->form)) {
      if (isset($context[0]->form['#pre_render'])) {
        foreach ($context[0]->form['#pre_render'] as $function) {
          if (function_exists($function)) {
            $context[0]->form = $function($context[0]->form);
          }
        }
        unset($context[0]->form['#pre_render']);
      }

      foreach (element_children($context[0]->form) as $element) {
        $form[$element] = $context[0]->form[$element];
        unset($context[0]->form[$element]);
      }

      // Set block delta and title.
      $block->title = $context[0]->form_title;
      $block->delta = $context[0]->form_id;
    }
  }

  $block->content = $form;
  return $block;
}

/**
 * Set administration title for the UI.
 */
function ding_user_profile2_form_content_type_admin_title($subtype, $conf, $context) {
  return t('User edit form (with profile2 support).');
}

/**
 * Default edit form for the administration form.
 */
function ding_user_profile2_form_content_type_edit_form($form, &$form_state) {
  // Provide a blank form so we have a place to override title
  // and stuff.
  return $form;
}
