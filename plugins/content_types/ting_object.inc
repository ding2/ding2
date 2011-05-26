<?php

$plugin = array(
  'title' => t('Ting object'),
  'description' => t('Ting object content type'),
  'single' => TRUE,
  'content_types' => array('ting_object'),
  'render callback' => 'ting_object_content_type_render',
  'required context' => new ctools_context_required(t('Ting object'), 'ting_object'),
  'category' => t('Ting'),
);

function ting_ting_object_content_type_edit_form($form, &$form_state) {
  return $form;
}

function ting_object_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $object = isset($context->data) ? ($context->data) : NULL;
  if ($object instanceOf TingEntity) {
    $block->title = check_plain($object->title);
    $block->content = ting_object_view($object);
  }

  return $block;
}
