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
 * @param string $query
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
  return ding_provider_invoke('search', 'autocomplete', $query);
}
