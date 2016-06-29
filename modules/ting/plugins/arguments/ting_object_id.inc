<?php

$plugin = array(
  'title' => t('Ting object: ID'),
  'keyword' => 'ting_object_id',
  'description' => t('Show a ting object'),
  'context' => 'ting_tasks_ting_object_id_context',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter a Ting object ID for this argument'),
  ),
);

function ting_tasks_ting_object_id_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  // If unset it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('ting_object');
  }

  // We can accept either a ting_object or a pure ting_object_id.
  if (is_object($arg)) {
    return ctools_context_create('ting_object', $arg);
  }

  if (empty($arg)) {
    // TODO: Can we do a better job of validating object IDs?
    return FALSE;
  }
  module_load_include('client.inc', 'ting');
  $object = ding_entity_load($arg, 'ting_object');
  if (!$object) {
    return FALSE;
  }

  return ctools_context_create('ting_object', $object);

}
