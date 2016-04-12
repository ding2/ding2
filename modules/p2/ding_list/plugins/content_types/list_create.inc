<?php

/**
 * @file
 * Create list form pane.
 */

$plugin = array(
  'title' => t('Create list'),
  'description' => t('Create list'),
  'single' => TRUE,
  'content_types' => array('list'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_create_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_create_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('Create new list');

  $block->content = array();
  $block->content[] = array(
    '#markup' => t('Create your own lists and collect books and other materials as you browse the library.'),
  );
  $block->content[] = drupal_get_form('ding_list_create_list_form');

  return $block;
}
