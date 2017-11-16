<?php
/**
 * @file
 * Legacy ting functions.
 *
 * All search related ting_ functions are deprecated. Code that has previously
 * used these functions should if possible be ported to the Search Abstraction
 * Layer (see ting_query_start() and the search provider type).
 *
 * Code that has a specific dependency on Open Search (ie. uses a unique Open
 * Search feature that is not feasible to see another search provider offer)
 * switch to using the opensearch_* counterpart of the function. Eg. use
 * opensearch_do_search() instead of ting_do_search().
 */

/**
 * Get an ting object or collection.
 *
 * @see opensearch_get_obect()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_get_object($object_id, $collection = FALSE, $with_relations = FALSE) {
  return opensearch_get_object($object_id, $collection, $with_relations);
}

/**
 * Get a bunch of objects in one request.
 *
 * @see opensearch_get_objects()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_get_objects($ids) {
  return opensearch_get_objects($ids);
}

/**
 * Performs a search against the well.
 *
 * @see opensearch_do_search()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_do_search($query, $page = 1, $results_per_page = 10, $options = array()) {
  return opensearch_do_search($query, $page, $results_per_page, $options);
}

/**
 * Get a ting object from the well in marcxchange format.
 *
 * @see opensearch_get_object_marcxchange()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_get_object_marcxchange($object_id) {
  return opensearch_get_object_marcxchange($object_id);
}

/**
 * Calls ting_execute() and caches the result.
 *
 * @see opensearch_execute_cache()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_execute_cache($request) {
  return opensearch_execute_cache($request);
}

/**
 * Get recommendations for a given ISBN.
 *
 * @see opensearch_get_object_recommendations()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_get_object_recommendations($isbn, $num_results = 10) {
  opensearch_get_object_recommendations($isbn, $num_results);
}

/**
 * Retrieves an initialized Ting client request factory.
 *
 * @throws TingClientException
 *   If there is no end-point url defined in the configuration this exception is
 *   thrown.
 *
 * @see opensearch_get_request_factory()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_get_request_factory() {
  return opensearch_get_request_factory();
}

/**
 * Perform a request against Ting and perform error handling if necessary.
 *
 * @see opensearch_execute()
 *
 * @deprecated Use the Search Abstraction Layer if possible. If you have
 *   a specific dependency on the opensearch provider, switch to
 *   opensearch_get_object.
 */
function ting_execute($request) {
  return opensearch_execute($request);
}
