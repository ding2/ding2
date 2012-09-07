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

  // Set default return values.
  $collections = _ting_search_carousel_get_content($index);
  $subtitle = '';

  // If cache have been found theme search carousel pages.
  if (!empty($collections)) {
    $ting_seach_queries = variable_get('ting_carousel_search_queries', array());
    if (isset($ting_seach_queries[$index])) {
      $subtitle = $ting_seach_queries[$index]['subtitle'];
      foreach ($collections as $collection) {
        $content .= theme('ting_search_carousel_collection', array('collection' => $collection));
      }
    }
  }

  // Return JSON output.
  drupal_json_output(array('subtitle' => $subtitle, 'content' => $content));
  exit();
}

function _ting_search_carousel_get_content($index, $search = TRUE) {
  // Utilize the static cache.
  $static = &drupal_static(__FUNCTION__);
  if (isset($static[$index]) && !empty($static[$index])) {
    return $static[$index];
  }

  // Check if there is a database cache of the search results.
  if ($cache = cache_get('ting_search_carousel_result')) {
    // Get cached data and store it in the static cache.
    $data = $cache->data;
    $static = $data;

    // Check if data exists for the index.
    if (isset($data[$index]) && !empty($data[$index])) {
      return $data[$index];
    }
  }

  // No cache found for that index, so try getting information from the
  // data well and cover service.
  if ($search) {
    ting_search_carousel_do_request(TRUE);
    return _ting_search_carousel_get_content($index, FALSE);
  }

  // No form for cached data was found.
  return '';
}