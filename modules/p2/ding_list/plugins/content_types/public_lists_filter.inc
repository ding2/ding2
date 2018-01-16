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
  'required context' => array(
    new ctools_context_required(t('String'), 'string'),
    new ctools_context_required(t('Taxonomy term'), 'taxonomy_term'),
  )
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_public_lists_filter_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $term = !empty($context[1]->data) ? $context[1]->data : FALSE;

  if ($term === FALSE) {
    $block->title = t('Lists');
  }
  else {
    $block->title = t('Lists tagged with %tag', array('%tag' => $term->name));
  }
  $block->content = array(
    '#theme' => 'links',
    '#links' => array(),
  );

  $roles = array(
    'staff' => t('Librarians'),
    'provider' => t('Loaners'),
  );
  foreach (array_intersect(user_roles(), array_keys($roles)) as $rid => $role) {
    $block->content['#links'][$rid] = array(
      'title' => $roles[$role],
      'href' => 'public-lists/' . $rid . ($term ? '/' . $term->tid : ''),
    );
  }
  $block->content['#links']['all'] = array(
    'title' => t('All'),
    'href' => 'public-lists/all' . ($term ? '/' . $term->tid : ''),
  );

  if (!empty($context[0]->data) && $context[0]->data === 'all') {
    $block->content['#links']['all']['attributes']['class'][] = 'active';
  }

  return $block;
}
