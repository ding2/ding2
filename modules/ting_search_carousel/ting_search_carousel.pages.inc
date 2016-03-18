<?php
/**
 * @file
 * Handles search carousel pages data.
 */

/**
 * AJAX callback to retrieve carousel items.
 *
 * @param $index
 *   Configuration index.
 * @param $offset
 *   Offset into result to fetch from.
 */
function ting_search_carousel_result($index, $offset) {
  $content = FALSE;

  // Set default return values.
  // $collections = _ting_search_carousel_get_content($index);
  // $count = count($collections);
  // $subtitle = '';

  // Get configuration.
  $ting_seach_queries = variable_get('ting_carousel_search_queries', array());
  // if (isset($ting_seach_queries[$index])) {
  //   $subtitle = $ting_seach_queries[$index]['subtitle'];

  //   // If cache have been found theme search carousel pages.
  //   if (!empty($collections)) {
  //     $collections = array_slice($collections, $offset * TING_SEARCH_CAROUSEL_CHUNK_SIZE, TING_SEARCH_CAROUSEL_CHUNK_SIZE);
  //     foreach ($collections as $collection) {
  //       $content .= theme('ting_search_carousel_collection', array('collection' => $collection));
  //     }
  //   }
  // }

  $content = '';
  $chunk = _ting_search_carousel_get_frontpage_covers($index, $offset, TING_SEARCH_CAROUSEL_CHUNK_SIZE);
  foreach ($chunk['collections'] as $collection) {
    $content .= theme('ting_search_carousel_collection', array('collection' => $collection));
  }
  $offset = $chunk['next_offset'];

  // Return JSON output.
  drupal_json_output(array(
    'content' => $content,
    'index' => $index,
    'offset' => $offset,
    //'offset' => ($offset * TING_SEARCH_CAROUSEL_CHUNK_SIZE) > $count ? -1 : $offset,
  ));
}
