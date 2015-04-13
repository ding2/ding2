<?php

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

  module_load_include('client.inc', 'ting');

  $query = strtolower($query);

  $settings = variable_get('ting_search_autocomplete_settings', array());

  $minimum_string = (!empty($settings['minimumString'])) ? $settings['minimumString'] : 3;

  if (strlen($query) < $minimum_string) {
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

    // Suggestion service does not yet implement SOAP with a JSON response :-(
    // Until then, we'll do it as REST
    $matches = ting_search_autocomplete_get_suggestions_rest($query);

    // Store the matches in cache for faster lookup next time.
    cache_set($cid, $matches, 'cache_ting_search_autocomplete', CACHE_TEMPORARY);
  }

  drupal_json_output($matches);
  drupal_exit();

}


/**
 * SuggestionService - retrieve suggestions with REST
 *
 * @param string $query
 * @return TingClientSuggestionFacet
 */

function ting_search_autocomplete_get_suggestions_rest($query) {

  $items = array();
  $request = ting_get_request_factory()->getSuggestionRequest();
  $settings = variable_get('ting_search_autocomplete_settings', array());
  unset($settings['minimumString']);

  foreach ($settings as $parameter => $value) {
    $setter = 'set' . ucfirst($parameter);
    if (method_exists('TingClientSuggestionRequest', $setter)) {
      $request->$setter($value);
    }
    else {
      watchdog('ting_search_autocomplete', 'Request initialized with nonexisting method: %n', array('%n' => $setter), WATCHDOG_WARNING);
    }
  }
 
  $request->setQuery($query);
  $request->getRequest();
  $rest_url = $request->getWsdlUrl();
  $parameters = $request->getParameters();
  unset($parameters['action']);
  $rest_url = (!empty($parameters['facetIndex'])) ? $rest_url . 'rest/facets' : $rest_url . 'rest/terms';
  $url = url($rest_url, array('query' => $parameters));

  try {
    $client = new NanoSOAPClient($url, array());
    $result = json_decode($client->curlRequest($url));
  } catch (NanoSOAPcURLException $e) {
    throw new TingClientException($e->getMessage(), $e->getCode());
  }

  if (!empty($result->suggestions)) {
    foreach ($result->suggestions as $suggestion) {
      $items[ting_search_autocomplete_truncate(html_entity_decode(strip_tags($suggestion->suggestion)), 64)] = $suggestion->suggestion;
    }
  }

  return $items;

}


/**
 * helper function for bibdk_autocomplete()
 * truncate $string to $width at whitespace
 * @param string $string
 * @param string $width
 * @return array
 */
function ting_search_autocomplete_truncate($string, $width) {
  $parts = preg_split('/([\s\n\r]+)/', $string, null, PREG_SPLIT_DELIM_CAPTURE);
  $parts_count = count($parts);

  $length = 0;
  $last_part = 0;
  for (; $last_part < $parts_count; ++$last_part) {
    $length += strlen($parts[$last_part]);
    if ($length > $width) {
      break;
    }
  }

  return implode(array_slice($parts, 0, $last_part));
}

