<?php
/**
 * @file
 * Handles search carousel pages data.
 */

/**
 * AJAX callback to retrieve carousel items.
 *
 * @param array $index
 *   Array index storing specific data.
 */
function ting_search_carousel_result($index) {
  $content = FALSE;

  // Set default return values.
  $collections = _ting_search_carousel_get_content($index);
  $subtitle = '';

  // Get configuration.
  $ting_seach_queries = variable_get('ting_carousel_search_queries', array());
  if (isset($ting_seach_queries[$index])) {
    $subtitle = $ting_seach_queries[$index]['subtitle'];

    // If cache have been found theme search carousel pages.
    if (!empty($collections)) {
      foreach ($collections as $collection) {
        $content .= theme('ting_search_carousel_collection', array('collection' => $collection));
      }
    }
  }

  // Return JSON output.
  drupal_json_output(array(
    'subtitle' => $subtitle,
    'content' => $content,
    'index' => $index,
  ));
}
