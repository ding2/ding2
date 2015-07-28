<?php
/**
 * @file
 * Panels pane to display a ting collection.
 */

$plugin = array(
  'title' => t('Ting collection'),
  'description' => t('Ting collection content type'),
  'single' => TRUE,
  'content_types' => array('ting_collection'),
  'render callback' => 'ting_collection_content_type_render',
  'required context' => new ctools_context_required(t('Ting collection'), 'ting_collection'),
  'category' => t('Ting'),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ting_collection_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $object = isset($context->data) ? ($context->data) : NULL;
  if ($object instanceOf TingCollection) {
    if (count($object->entities) < 2) {
      drupal_goto('ting/object/' . $object->id);
    }

    // Add search overlay trigger.
    drupal_add_js(drupal_get_path('module', 'ting') . '/js/ting.js');

    $block->title = check_plain($object->title);
    $block->content = ting_collection_view($object);
  }

  return $block;
}

/**
 * Implements hook_ID_content_type_edit_form().
 */
function ting_ting_collection_content_type_edit_form($form, &$form_state) {
  return $form;
}
