<?php
/**
 * @file
 * Current username panels content type.
 */

$plugin = array(
  'title' => t('Current user name.'),
  'description' => t('The current user name.'),
  'single' => TRUE,
  'category' => t('User'),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_user_frontend_current_user_name_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  global $user;

  $block = new stdClass();
  $block->title = t('Logged in user');
  $block->content = format_username($user);

  return $block;
}
