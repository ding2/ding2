<?php
/**
 * @file
 */

/**
 * AJAX callback to retrieve carousel items.
 */
function ting_search_carousel_result($index) {
  $collections = array();
  $result = '';
  $cache_ting_search_result = cache_get('ting_search_result');
  $ting_seach_queries = variable_get('ting_carousel_search_queries', array());
  $subtitle = '';
  
  if (isset($cache_ting_search_result->data[$index]) && isset($ting_seach_queries[$index]) && count($cache_ting_search_result->data[$index]) > 0) {
    $subtitle = $ting_seach_queries[$index]['subtitle'];
    foreach ($cache_ting_search_result->data[$index] as $k => $v) {
      $result .= theme('ting_search_carousel_collection', array('collection' => $v));
    }
  }

  echo drupal_json_encode(array('subtitle' => $subtitle, 'content' => $result));
  exit();
}
