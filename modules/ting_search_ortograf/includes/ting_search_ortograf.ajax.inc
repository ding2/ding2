<?php
/**
 * @file
 * AJAX functions ting search ortograf autocomplete.
 */

/**
 * Auto-complete callback for the ting search block.
 *
 * The function returns JSON and ending execution.
 *
 * @param string $string
 *   The string to search suggestion with.
 */
function ting_search_ortograf_callback($string = '') {
  $matches = array();

  $query['q'] = check_plain(strtolower($string));
  $query['type'] = 'all';
  $query['rows'] = variable_get('ting_search_ortograf_rows', 10);

  $minimum_string = variable_get('ting_search_ortograf_minimum_string', 3);
  if (drupal_strlen($string) < $minimum_string) {
    drupal_json_output(array());
    drupal_exit();
  }

  // Try to use cache for the search string.
  $cid = md5(serialize($query));
  if ($cache = cache_get($cid, 'cache_ting_search_ortograf')) {
    $matches = $cache->data;
  }
  else {
    $suggestions = ting_search_ortograf_get_suggestions($query);
    // Maximum space in suggestions dropdown is 62 characters.
    // Maximum characters for search query string is 256 characters.
    foreach ($suggestions as $suggestion) {
      $val = truncate_utf8($suggestion, 62, TRUE, TRUE, 1);
      $key = truncate_utf8($suggestion, 256, TRUE, FALSE, 1);
      $matches[$key] = $val;
    }
    // Store the matches in cache for faster lookup next time.
    cache_set($cid, $matches, 'cache_ting_search_ortograf', CACHE_TEMPORARY);
  }

  drupal_json_output($matches);
  drupal_exit();
}


/**
 * SuggestionService - retrieve suggestions with drupal_http_request() 
 *
 * @param array $query
 *   Search suggestion parameters.
 *
 * @return array
 *   Search suggestion results.
 */
function ting_search_ortograf_get_suggestions(array $query) {
  $items = array();
  $rest_url = variable_get('ting_search_ortograf_suggestion_url', '');
  $url = url($rest_url, array('query' => $query));
  $headers = array('Accept' => 'application/json');

  $result = drupal_http_request($url, $headers);

  if (!empty($result->error)) {
    watchdog(
      'ting_search_ortograf',
      "Autocomplete error: %error (%code)\nURL: !url",
      array(
        '%error' => $result->error,
        '%code' => $result->code,
        '!url' => $url,
      ),
      $severity = WATCHDOG_ERROR
    );
    return $items;
  }

  if (!empty($result->data)) {
    $result_data = drupal_json_decode($result->data);
    if (!empty($result_data['response']['docs'])) {
      foreach ($result_data['response']['docs'] as $suggestion) {
        $items[] = check_plain($suggestion['all'][0]);
      }
    }
  }

  return $items;
}
