<?php
/**
 * @file
 * Panels pane to display title and number of items in ting collection.
 */

$plugin = array(
  'title' => t('Ting collection title and count'),
  'description' => t('Ting collection title and count'),
  'single' => TRUE,
  'content_types' => array('ting_collection'),
  'render callback' => 'ding_ddbasic_ting_collection_title_and_count_content_type_render',
  'required context' => new ctools_context_required(t('Ting collection'), 'ting_collection'),
  'category' => t('Ting'),
);

/**
 * Render the block
 */
function ding_ddbasic_ting_collection_title_and_count_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  
  $block->title = t('Material collection');
  
  $object = isset($context->data) ? ($context->data) : NULL;
  if ($object instanceOf TingCollection) {
    $count = count($object->entities);
    $block->content = '<span class="material-title">"' . check_plain($object->title) . '"</span><span class="count"> (' . $count . ' hits)</span>';
  }

  return $block;
}