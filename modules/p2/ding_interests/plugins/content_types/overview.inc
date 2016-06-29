<?php

/**
 * @file
 * To-do: doc here.
 */

$plugin = array(
  'title' => t('Ding interests: Overview'),
  'description' => '',
  'single' => TRUE,
  'category' => t('Ding!'),
  'render callback' => 'ding_interests_overview_content_type_render',
);

/**
 * To-do: doc here.
 */
function ding_interests_overview_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->content = theme('ding_interests_tree');

  return $block;
}
