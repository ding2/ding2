<?php

/**
 * @file
 * API Documentation.
 */

/**
 * Hook to define a serendipity "action".
 *
 * @return array
 *   An array of serendipity definitions, each of which describe a serendipity
 *   function with name: module_name . '_' . machine_name . '_serendipity_add'
 *   The definition is required to have the following values:
 *   - "title": The title of the serendipity function
 *   - "description": A description of what is provides and when it is applied.
 *   - "keys": Array of context keys, which define the context required
 *      before the function is called by the serendipity module.
 *   The definition can also include the following values:
 *   - "callback": An alternative callback which replaces the default:
 *     "module_name . '_' . machine_name . '_serendipity_add'".
 *   - "access callback": An alternate access callback function, default:
 *     "ding_serendipity_access".
 *     The access function determines when the serendipity function is applied.
 *   - "file": Path to a file where the serendipity function is written.
 *   - "settings": Name of a form with settings for the serendipity function.
 *   - "weight": The default weight for this plugin.
 */
function hook_serendipity_info() {
  return array(
    'machine_name' => array(
      'title' => 'some title',
      'description' => 'A nice informative description',
      'keys' => array('key 1', 'key2', 'key3', '...'),
      'callback' => NULL,
      'access callback' => NULL,
      'file' => NULL,
      'settings' => NULL,
      'weight' => 10,
    ),
  );
}

/**
 * Alter the content of serendipity context before content is gathered.
 *
 * @param array $context
 *   The context to get the serendipity from.
 */
function hook_serendipity_context_alter(array &$context) {
  // Alter the context.
}

/**
 * Alter the content of the serendipity results after processing has finished.
 *
 * @param array $results
 *   The serendipity results.
 * @param array $context
 *   The context to get the serendipity from.
 */
function hook_serendipity_results_alter(array &$results, array &$context) {
  // Alter results.
}

/**
 * Add results to the serendipity result to prevent empty lists.
 *
 * @param array $context
 *   The context to get the serendipity from.
 */
function hook_serendipity_fallback(array $context) {
  // Add fallback content based on the context.
}
