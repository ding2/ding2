<?php
/**
 * @file
 * Wraps the staff profile2 edit form in a panel pane.
 */


/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  // only provides a single content type
  'single' => TRUE,
  'render last' => TRUE,
  'title' => t('Staff profile'),
  'icon' => 'icon_form.png',
  'description' => t('Staff profile to update information about a staff member'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Form'),
);

/**
 * Implements render for the pane and loads the profile2 profile edit form.
 */
function ding_staff_profile2_staff_form_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $user = $context->data;
  
  $profile2 = profile2_load_by_user($user);

  // staff is the profile2 type name for staff profiles
  if (isset($profile2['staff'])) {
    $block->content = entity_ui_get_form('profile2', $profile2['staff']);
    return $block;
  } 
  // user doesn't have a staff profile, we need to show form for adding new staff profile
  else {
    $profile = profile_create(array(
      'type' => 'staff',
      'uid' => $user->uid,
    ));
    $block->content = entity_ui_get_form('profile2', $profile, 'add');
    return $block;
  } 
}

function ding_staff_profile2_staff_form_content_type_admin_title($subtype, $conf, $context) {
  return t('Staff edit form.');
}

/**
 * Plugin settings form
 */
function ding_staff_profile2_staff_form_content_type_edit_form($form, &$form_state) {
  return $form;
}

