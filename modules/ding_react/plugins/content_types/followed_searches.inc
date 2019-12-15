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
    'material-url' => '/ting/object/:pid',
    'author-url' => '/search/ting/phrase.creator=":author"',
    'new-button-text' => t('See new materials'),
    'remove-button-text' => t('Remove search'),
    'new-window-text' => t('Opens in a new window'),
    'status-text' => t(':hit_count new materials since'),
    'go-to-search-text' => t('Show search result'),
  ];

  $block->content = ding_react_app('searchlist', $data);

  return $block;
}
