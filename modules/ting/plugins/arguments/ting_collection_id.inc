<?php
/**
 * @file
 * Define context for the ting collection pane.
 */

$plugin = array(
  'title' => t('Ting collection: ID'),
  'keyword' => 'ting_collection_id',
  'description' => t('Show a ting collection'),
  'context' => 'ting_tasks_ting_collection_id_context',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter a Ting collection ID for this argument'),
  ),
);

function ting_tasks_ting_collection_id_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  // If unset it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('ting_collection');
  }
  // We can accept either a ting_collection or a pure ting_collection_id.
  if (is_object($arg)) {
    return ctools_context_create('ting_collection', $arg);
  }

  if (empty($arg)) {
    // TODO: Can we do a better job of validating collection IDs?
    return FALSE;
  }
  module_load_include('client.inc', 'ting');
  $collection = ting_get_collection($arg);
  if (!($collection instanceOf TingClientcollection)) {
    return FALSE;
  }

  return ctools_context_create('ting_collection', $collection);

}

