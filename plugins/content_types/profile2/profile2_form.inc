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
  // only provides a single content type
  'single' => TRUE,
  'render last' => TRUE,
  'title' => t('Provider profile'),
  'icon' => 'icon_form.png',
  'description' => t('Provider profile to update information at the provider.'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Form'),
);

/**
 * Implements render for the pane and loads the profile2 profile edit form.
 */
function ding_user_profile2_form_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();

  // Get provider profile and get edit form for it.
  $profile = ding_user_provider_profile($context->data);
  $block->content = entity_ui_get_form('profile2', $profile);

  return $block;
}

function ding_user_profile2_form_content_type_admin_title($subtype, $conf, $context) {
  return t('Provider edit form.');
}

function ding_user_profile2_form_content_type_edit_form($form, &$form_state) {
  // provide a blank form so we have a place to override title
  // and stuff.
  return $form;
}
