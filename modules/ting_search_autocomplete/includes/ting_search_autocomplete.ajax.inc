<?php
/**
 * @file
 * AJAX functions bibliotek.dk autocomplete.
 */

/**
 * Auto-complete callback for the ting search block.
 *
 * The function returns JSON and ends the execution.
 *
 * @param string $query
 *   The string to search suggestion with.
 * @param bool $reset
 *   If TRUE the cache is reset. Defaults to FALSE.
 */
function ting_search_autocomplete_callback($query = '', $reset = FALSE) {
  $query = check_plain(strtolower($query));

  // Try to use cache for the search string.
  $cid = md5($query);
  if (!$reset && $cache = cache_get($cid, 'cache_ting_search_autocomplete')) {
    $matches = $cache->data;
  }
  else {
    // Suggestion service does not implement SOAP with a JSON response
    $matches = ding_provider_invoke('search', 'autocomplete', $query);

    // Store the matches in cache for faster lookup next time.
    cache_set($cid, $matches, 'cache_ting_search_autocomplete', CACHE_TEMPORARY);
  }

  drupal_json_output($matches);
  drupal_exit();
}
