<?php

/**
 * @file
 * Add list form pane.
 */

$plugin = array(
  'title' => t('Add list to list'),
  'description' => t('Add list to list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),

  'category' => t('Ding!'),
  'render callback' => 'ding_list_add_list_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_add_list_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;

  // For unknown reasons the $entity->uid is not filled, when it's loaded via
  // the context. Which is why we reload the entity using entity_load_single.
  $list = entity_load_single('ding_type', $context->data->id);

  $block = new stdClass();
  $block->content = array();

  // Users can only add lists they don't own.
  if ($list->uid != $user->uid && user_access('use personalisation')) {
    $block->content = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->id, t('Add to lists I follow'));
  }

  return $block;
}
