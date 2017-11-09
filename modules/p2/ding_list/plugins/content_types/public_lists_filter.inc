<?php

/**
 * @file
 * Public lists filter
 */

$plugin = array(
  'title' => t('Public lists filter'),
  'description' => t('Public lists filter.'),
  'single' => TRUE,
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_public_lists_filter_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_public_lists_filter_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('Lists');
  $block->content = array(
    '#theme' => 'links',
    '#links' => array(),
  );

  foreach (array_intersect(user_roles(), array('provider', 'staff')) as $rid => $role) {
    $block->content['#links'][] = array(
      // The user_roles function only translate the built in role names, which
      // is why the role variable is run through the t() function.
      'title' => t($role),
      'href' => 'public-lists/' . $rid,
    );
  }
  $block->content['#links'][] = array(
    'title' => t('All'),
    'href' => 'public-lists',
  );

  return $block;
}
