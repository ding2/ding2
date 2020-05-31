<?php

/**
 * @file
 * Panels pane to display the smart search form
 */

$plugin = array(
  'title' => t('Ting smart search content'),
  'description' => t("Display referenced content on search result page"),
  'single' => TRUE,
  'content_types' => array('smart_search_content'),
  'render callback' => 'ting_smart_search_content_type_render',
  'category' => t('Ting'),
  'render last' => TRUE,
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
);

/**
 * Render the smart search form block.
 */
function ting_smart_search_content_type_render($subtype, $conf, $panel_args, $context) {
  $path = drupal_get_path('module', 'ting_smart_search');
  drupal_add_css($path . '/css/smart_search_content.css');

  $search_string = $context->data;

  module_load_include('inc', 'eck', 'eck.entity');
  // Create the block class.
  $block = new stdClass();
  $block->content = '';

  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'ting_type')
    ->entityCondition('bundle', 'smart_search_string')
    ->propertyCondition('title', $search_string, '=');

  $result = $query->execute();

  if (isset($result['ting_type'])) {
    $string_items_nids = array_keys($result['ting_type']);
    $new_string_item = entity_metadata_wrapper('ting_type', $string_items_nids[0]);
    $referenced = $new_string_item->field_content_reference->value();
    if (isset($referenced)) {
      $ref_node = entity_metadata_wrapper('node', $referenced->nid);
      $view_mode = $ref_node->field_view_mode->value();
      $node_view = node_view($referenced, $view_mode);
      $block->content = $node_view;
    }
  }

  return $block;

}
