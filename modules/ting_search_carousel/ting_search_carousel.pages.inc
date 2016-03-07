<?php
/**
 * @file
 * Handles search carousel pages data.
 */

/**
 * AJAX callback to retrieve carousel items.
 *
 * @param string $hash
 *   Search carousel searches hash.
 *
 * @param array $index
 *   Array index storing specific data.
 */
function ting_search_carousel_result($hash, $index) {
  $content = FALSE;

  // Set default return values.
  $collections = _ting_search_carousel_get_content($hash, $index);
  $subtitle = '';

  $search_conf_cache = cache_get('ting_search_carousel_conf_' . $hash);
  $search_conf = (!empty($search_conf_cache->data)) ? reset($search_conf_cache->data) : array();

  // Get configuration.
  $ting_search_queries = (!empty($search_conf['searches'])) ? $search_conf['searches'] : array();
  if (isset($ting_search_queries[$index])) {
    $subtitle = $ting_search_queries[$index]['subtitle'];

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
