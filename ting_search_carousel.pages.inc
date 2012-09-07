<?php
/**
 * @file
 * Handles search carousel pages data.
 */

/**
 * AJAX callback to retrieve carousel items.
 *
 * @param $index
 *   Array index storing specific data.
 */
function ting_search_carousel_result($index) {
  $cache = FALSE;

  // Check if there is a cached search result.
  if ($cache = cache_get('ting_search_carousel_result')) {
    $cache_ting_search_result = $cache->data;
  }
  else {
    // No cache found so we need to do a search.
    ting_search_carousel_do_request(TRUE);
    if ($cache = cache_get('ting_search_carousel_result')) {
      $cache_ting_search_result = $cache->data;
    }
  }

  // Set default return values.
  $result = '';
  $subtitle = '';

  // If cache have been found theme search carousel pages.
  if ($cache) {
    $ting_seach_queries = variable_get('ting_carousel_search_queries', array());
    if (isset($ting_seach_queries[$index])) {
      $subtitle = $ting_seach_queries[$index]['subtitle'];
      if (isset($cache_ting_search_result[$index]) && !empty($cache_ting_search_result[$index])) {
        foreach ($cache_ting_search_result[$index] as $collection) {
          $result .= theme('ting_search_carousel_collection', array('collection' => $collection));
        }
      }
    }
  }

  // Return JSON output.
  drupal_json_output(array('subtitle' => $subtitle, 'content' => $result));
  exit();
}
