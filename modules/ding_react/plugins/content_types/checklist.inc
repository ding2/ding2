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

  $data = [
    'material-list-url' => ding_react_material_list_url(),
    // We cannot use url() here as it will encode the colon in the placeholder.
    'material-url' => '/ting/object/:pid',
    'author-url' => '/search/ting/phrase.creator=":author"',
    'remove-button-text' => t('Remove from list'),
    'empty-list-text' => t('List is empty.'),
    'error-text' => t('An error occurred while trying to fetch list.'),
    'of-text' => t('By')
  ];
  $block->content = ding_react_app('checklist', $data);

  return $block;
}
