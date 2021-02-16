<?php

/**
 * @file
 * The search help pane.
 */

$plugin = array(
  'title' => t('Ting search - search help'),
  'description' => t("Show help for searching."),
  'single' => TRUE,
  'content_types' => array('search_help'),
  'category' => t('Ting'),
);

/**
 * Render the ting search results amount block.
 */
function ting_search_search_help_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('Found what you where looking for?');
  $block->content = t('Ask us at the library or get help at <a href="http://biblioteksvagten.dk">biblioteksvagten.dk</a><br />
Or you can keep looking at <a href="https://bibliotek.dk">bibliotek.dk</a>');

  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_search_search_help_content_type_edit_form($form, &$form_state) {
  return $form;
}
