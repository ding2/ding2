<?php
/**
 * @file
 * AJAX functions bibliotek.dk autocomplete.
 */

/**
 * Auto-complete callback for the ting search block.
 *
 * The function returns JSON and ending execution.
 *
 * @param string $string
 *   The string to search suggestion with.
 * @param bool $reset
 *   If TRUE the cache is reset. Defaults to FALSE.
 */
function ting_search_autocomplete_callback($query = '', $reset = FALSE) {
  $query = check_plain(strtolower($query));
  $settings = variable_get('ting_search_autocomplete_settings', array());

  $minimum_string = (!empty($settings['minimumString'])) ? $settings['minimumString'] : 3;
  if (drupal_strlen($query) < $minimum_string) {
    drupal_json_output(array());
    drupal_exit();
  }

  if (empty($settings['index'])) {
    watchdog('ting_search_autocomplete', 'Autocomplete index not defined ', array(), $severity = WATCHDOG_WARNING);
    drupal_json_output(array());
    drupal_exit();
  }

  // Try to use cache for the search string.
  $cid = md5($query);
  if (!$reset && $cache = cache_get($cid, 'cache_ting_search_autocomplete')) {
    $matches = $cache->data;
  }
  else {
    // Suggestion service does not implement SOAP with a JSON response
    $matches = ting_search_autocomplete_get_suggestions($query);

    // Store the matches in cache for faster lookup next time.
    cache_set($cid, $matches, 'cache_ting_search_autocomplete', CACHE_TEMPORARY);
  }

  drupal_json_output($matches);
  drupal_exit();
}


/**
 * SuggestionService - retrieve suggestions with drupal_http_request() 
 *
 * @param string $query
 * @return array
 */
function ting_search_autocomplete_get_suggestions($query) {
  $items = array();
  $rest_url = variable_get('ting_search_autocomplete_suggestion_url', '');
  $method = variable_get('ting_search_autocomplete_method', 'facets');
  $settings = ting_search_autocomplete_settings();

  // minimumString is not an openSuggestion parameter
  unset($settings['minimumString']);

  $rest_url = $rest_url . 'rest/' . $method;
  $settings['query'] = $query;
  $url = url($rest_url, array('query' => $settings));

  $result = drupal_http_request($url, array());

  if (!empty($result->data)) {
    $result_data = drupal_json_decode($result->data);
    if (empty($result->error)) {
      if (!empty($result_data['suggestions'])) {
        foreach ($result_data['suggestions'] as $suggestion) {
          $items[truncate_utf8(strip_tags($suggestion['suggestion']), 256, TRUE, FALSE, 1)] = $suggestion['suggestion'];
        }
      }
    }
    else {
      watchdog('ting_search_autocomplete', 'Autocomplete error: ' . $result->error . ' (' . $result->code . ")\nURL: $url" , array(), $severity = WATCHDOG_ERROR);
    }
  }


  return $items;
}
