<?php

/**
 * @file
 * Add the checklist app content type.
 */

$plugin = [
  'title' => t('Checklist app'),
  'single' => TRUE,
  'description' => t('Display current users checklist.'),
  'category' => t('DDB React'),
];

/**
 * Return pane content.
 */
function ding_react_checklist_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('My checklist');

  $block->content = ddb_react_app('checklist');

  return $block;
}
