<?php
/**
 * @file
 * This panels content type defines panes that can be used to add a user
 * sub-menu base on the tabs on the user page.
 */

$plugin = array(
  'title' => t('User sub-menu'),
  'description' => t('The current users sub-menu'),
  'edit form' => 'ding_user_frontend_user_menu_edit_form',
  'render callback' => 'ding_user_frontend_user_menu_content_type_render',
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_user_frontend_user_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();

  $block->title = t('My account');
  $block->content = ding_user_frontend_build_menu();

  return $block;
}

/**
 * Edit form callback for the content type.
 */
function ding_user_frontend_user_menu_edit_form($form, &$form_state) {
  return $form;
}
