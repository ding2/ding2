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

  $search_context = $_POST['search_context'];
  $nodes = ting_search_context_get_related_content($search_context);
  $output = '';
  if (!empty($nodes)) {
    foreach ($nodes as $node) {
      $output .= theme('ting_search_context_content', array('node' => $node));
    }
  }
  return drupal_json_output($output);
}
