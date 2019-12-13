<?php

/**
 * @file
 * Add the followed searches app content type.
 */

$plugin = [
  'title' => t('Followed searches app'),
  'single' => TRUE,
  'description' => t('Display current users checklist.'),
  'category' => t('DDB React'),
];

/**
 * Return pane content.
 */
function ding_react_followed_searches_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('My followed searches');

  $block->content = ding_react_app('searchlist');

  return $block;
}
