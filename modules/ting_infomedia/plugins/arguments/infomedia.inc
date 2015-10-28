<?php

/**
 * @file
 * Plugin to provide an argument handler for infomedia.
 */
$plugin = array(
  'title' => t("infomedia: ID"),
  'keyword' => 'infomedia',
  'description' => t('Creates a "infomedia article" from the ID.'),
  'context' => 'infomedia_arguments_context',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the infomedia ID'),
  ),
);

/**
 * Get the infomedia context using the arg.
 *
 * In this case we're just going to manufacture the context from the data in the
 * arg, but normally it would be an API call, db lookup, etc.
 */
function infomedia_arguments_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  // If $empty is TRUE it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('infomedia');
  }

  // Do whatever error checking is required
  if (empty($arg)) {
    return FALSE;
  }

  return ctools_context_create('infomedia', $arg);
}
