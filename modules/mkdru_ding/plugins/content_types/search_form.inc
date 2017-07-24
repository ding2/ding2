<?php
/**
 * @file
 * Search form pane plugin.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Mkdru DING! search form'),
  'description' => t('Custom search form.'),
  'category' => t('MKDRU'),
  'render callback' => 'mkdru_ding_search_form_render',
  'edit form' => 'mkdru_ding_search_form_edit_form',
);

/**
 * Render callback.
 */
function mkdru_ding_search_form_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = t('Search');

  $form = drupal_get_form('mkdru_ding_search_form');
  $block->content = drupal_render($form);

  return $block;
}

/**
 * Edit form callback.
 */
function mkdru_ding_search_form_edit_form($form, &$form_state) {
  return $form;
}
