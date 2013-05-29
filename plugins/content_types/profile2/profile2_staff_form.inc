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
function ding_staff_profile2_form_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();

  // staff is the profile2 type name for staff profiles
  //$block->content = entity_ui_get_form('profile2', 'staff');
  $block->content = 'hejsa';

  return $block;
}

function ding_staff_profile2_form_content_type_admin_title($subtype, $conf, $context) {
  return t('Provider edit form.');
}

/**
 * Plugin settings form
 */
function ding_staff_profile2_form_content_type_edit_form($form, &$form_state) {
  return $form;
}
