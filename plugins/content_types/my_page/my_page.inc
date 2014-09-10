<?php
/**
 * @file
 * Handles some tabs on the user profile page ?
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('My page'),
  'description' => t('Block in the user profile where we could implement a hook to show tabs with info.'),
  'single' => TRUE,
  'content_types' => array('my_page'),
  'render callback' => 'ding_user_my_page_type_render',
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render callback function.
 */
function ding_user_my_page_type_render($subtype, $conf, $panel_args, $context) {
  $block = array();
  $hook = 'ding_user_mypage_tab';
  foreach (module_implements($hook) as $module) {
    $function = $module . '_' . $hook;
    $block = $function($context->data);
  }
  return $block;
}

/**
 * Plugin settings form.
 */
function ding_user_my_page_content_type_edit_form($form, &$form_state) {
  return $form;
}
