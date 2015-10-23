<?php
/**
 * @file
 * Bookmark pane for ctools.
 */

$plugin = array(
  'title' => t('User bookmarks'),
  'description' => t('User bookmark items'),
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Implements hook_content_type_render().
 *
 * Create block with a list of all the materials currently in the users bookmark
 * list.
 */
function ding_bookmark_bookmarks_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = $context->data;

  $block = new stdClass();
  $block->module = 'ding_bookmark';
  $block->delta = 'bookmark';

  module_load_include('inc', 'ding_bookmark', 'ding_bookmark.pages');
  $block->content = ding_bookmark_user_bookmark_page($account);

  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function ding_bookmark_bookmarks_content_type_edit_form($form, &$form_state) {
  return $form;
}
