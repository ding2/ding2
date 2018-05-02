<?php

/**
 * @file
 * List context.
 */

$plugin = array(
  'title' => t('Ding list'),
  'description' => t('A ding list object'),
  'context' => 'ding_list_list_context',
  'keyword' => 'ding_list_list',
  'context name' => 'ding_list_list',
  'convert list' => array('title' => t('Title')),
  'convert' => 'ding_list_list_context_convert',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the ding list id'),
  ),
);

/**
 * Context callback.
 */
function ding_list_list_context($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('ding_list_list');
  $context->plugin = 'ding_list_list';

  if ($empty) {
    return $context;
  }

  if (!empty($data)) {
    $context->data = $data;
    $context->argument = $data->getId();
    $context->title = $data->getTitle();
  }

  return $context;
}

/**
 * Convert a context into a string.
 */
function ding_list_list_context_convert($context, $type) {
  switch ($type) {
    case 'title':
      return $context->title;
  }
}
