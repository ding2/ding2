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

  $data = [
    'search-url' => '/search/ting/:query',
    'empty-list-text' => t('List is empty.'),
    'error-text' => t('An error occurred while trying to fetch list.'),
    'go-to-search-text' => t('Show search result'),
    'remove-button-text' => t('Remove search'),
  ];

  $block->content = ding_react_app('searchlist', $data);

  return $block;
}
