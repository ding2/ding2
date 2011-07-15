<?php

$plugin = array(
  'title' => t('Ting collection'),
  'description' => t('Ting collection content type'),
  'single' => TRUE,
  'content_types' => array('ting_collection'),
  'render callback' => 'ting_collection_content_type_render',
  'required context' => new ctools_context_required(t('Ting collection'), 'ting_collection'),
  'category' => t('Ting'),
);

function ting_ting_collection_content_type_edit_form($form, &$form_state) {
  return $form;
}

function ting_collection_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $object = isset($context->data) ? ($context->data) : NULL;
  if ($object instanceOf TingCollection) {
    if (sizeof($object->entities) < 2) {
      drupal_goto('ting/object/' . $object->id);
    }

    $block->title = check_plain($object->title);
    $block->content = ting_collection_view($object);
  }

  return $block;
}

