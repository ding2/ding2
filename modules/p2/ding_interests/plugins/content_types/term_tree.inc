<?php

/**
 * @file
 * To-do: doc here.
 */

$plugin = array(
  'title' => t('Ding interests: Term tree'),
  'description' => '',
  'single' => TRUE,
  // 'content_types' => array('list'),
  'content_types' => array('taxonomy_term'),
  'required context' => new ctools_context_required(t('Term'), 'taxonomy_term'),
  'category' => t('Ding!'),
  'render callback' => 'ding_interests_term_tree_content_type_render',
);

/**
 * To-do: doc here.
 */
function ding_interests_term_tree_content_type_render($subtype, $conf, $panel_args, $context) {
  $term = $context->data;

  $block = new stdClass();
  $block->content = theme('ding_interests_tree', array('root' => $term->tid));

  return $block;
}
