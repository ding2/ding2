<?php
/**
 * @file
 * Wraps profile2 staff profile into a panels pane.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Staff profile'),
  'description' => t('Profile2 staff profile currently attached to the user.'),
  'single' => TRUE,
  'content_types' => array('profile2'),
  'render callback' => 'ding_staff_profile2_type_render',
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render callback function
 */
function ding_staff_profile2_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if (isset($context->data)) {
    $account = $context->data;
    $block->content = $account; // Does this show what we need?
  }

  return $block;
}

/**
 * Plugin settings form
 */
function ding_staff_profile2_content_type_edit_form($form, &$form_state) {
  return $form;
}
