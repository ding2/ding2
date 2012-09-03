<?php
/**
 * @file
 *
 */

/**
 * AJAX callback to retrieve carousel items.
 *
 * @param $index
 *   Array index storing specific data.
 */
function ting_search_carousel_result($index) {
  $result = '';
  $cache = cache_get('ting_search_result', 'cache');

  if (!isset($cache)) {
    ting_search_carousel_cron();
    $cache = cache_get('ting_search_result', 'cache');
  }

  $cache_ting_search_result = unserialize($cache->data);
  $ting_seach_queries = variable_get('ting_carousel_search_queries', array());
  $subtitle = '';

  if (isset($ting_seach_queries[$index])) {
    $subtitle = $ting_seach_queries[$index]['subtitle'];
    if (isset($cache_ting_search_result[$index]) && !empty($cache_ting_search_result[$index])) {
      foreach ($cache_ting_search_result[$index] as $collection) {
        $result .= theme('ting_search_carousel_collection', array('collection' => $collection));
      }
    }
  }

  drupal_json_output(array('subtitle' => $subtitle, 'content' => $result));
  exit();
}
