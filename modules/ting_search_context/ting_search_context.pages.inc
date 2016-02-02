<?php
/**
 * @file
 * Handles search context pages data.
 */

/**
 * AJAX callback to retrieve nodes related to search context.
 */
function ting_search_context_content() {
  $content = FALSE;

  $context_id = $_POST['context_id'];
  $nodes = ting_search_context_get_nodes($context_id, 15);
  $output = '';
  if (!empty($nodes)) {
    foreach ($nodes as $node) {
      $output .= theme('ting_search_context_content', array('node' => $node));
    }
  }
  return drupal_json_output($output);
}
