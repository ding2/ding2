<?php

/**
 * @file
 * List ID argument plugin.
 */

$plugin = array(
  'title' => t('Ding list: List ID'),
  'keyword' => 'ding_list_list_id',
  'description' => t('Ding list object id.'),
  'context' => 'ding_list_list_id_argument_context',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter a ding list object ID for this argument'),
  ),
);

/**
 * Argument context callback.
 */
function ding_list_list_id_argument_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  if ($empty) {
    return ctools_context_create_empty('ding_list_list');
  }

  if (is_object($arg)) {
    return ctools_context_create('ding_list_list', $arg);
  }

  if (empty($arg)) {
    return FALSE;
  }

  $object = ding_list_get_list($arg);

  if ($object === FALSE) {
    return FALSE;
  }

  return ctools_context_create('ding_list_list', $object);

}
