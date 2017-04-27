<?php

/**
 * @file
 * List manager pnae.
 */

$plugin = array(
  'title' => t('List manager'),
  'description' => t('List manger'),
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_manager_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_manager_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = $context->data;

  $block = new stdClass();
  module_load_include('inc', 'ding_list', 'ding_list.pages');
  $block->content = ding_list_manage_page($account);

  return $block;
}

/**
 * Returns an edit form for the content type.
 */
function ding_list_manager_content_type_edit_form($form, &$form_state) {
  return $form;
}
