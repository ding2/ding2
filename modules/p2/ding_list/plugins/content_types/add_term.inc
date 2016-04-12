<?php

/**
 * @file
 * Add term to list form pane.
 */

$plugin = array(
  'title' => t('Add term to list'),
  'description' => t('Add term to list.'),
  'single' => TRUE,
  'content_types' => array('taxonomy_term'),
  'required context' => new ctools_context_required(t('Term'), 'taxonomy_term'),
  'category' => t('Ding!'),
  'render callback' => 'ding_list_add_term_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_add_term_content_type_render($subtype, $conf, $panel_args, $context) {
  $term = $context->data;

  $block = new stdClass();
  $block->content = drupal_get_form('ding_list_add_element_form', 'taxonomy_term', $term->tid, 'Add to @list');

  return $block;
}
