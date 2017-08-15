<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

use OpenSearch\OpenSearchTingObject;
use OpenSearch\OpenSearchTingObjectCollection;
use OpenSearch\OpenSearchTingSearchResult;

/**
 * Get a list of material types from the Well.
 */
function opensearch_search_material_types() {
  // Get a list of types by executing a null query and look at the facets
  // result.
  $options = [
    'facets' => ['facet.type'],
    'numFacets' => 99,
    'reply_only' => TRUE,
    'sort' => 'random',
  ];
  module_load_include('client.inc', 'ting');
  // TODO: search via the abstraction-layer (to be implemented).
  $result = ting_do_search("*", 0, 0, $options);

  $types = [];
  foreach ($result->facets['facet.type']->terms as $term => $count) {
    $types[drupal_strtolower($term)] = $count;
  }

  return $types;
}

/**
 * Load objects from Open Search.
 *
 * @param string[] $ids
 *   Array of ids to load from Open Search.
 *
 * @return Ting\TingObjectInterface[]
 *   An array of loaded objects.
 */
function opensearch_search_object_load(array $ids) {
  $objects = ting_get_objects($ids);
  foreach ($objects as $id => $object) {
    if (!empty($object)) {
      $objects[$id] = new OpenSearchTingObject($object);
    }
  }
  return $objects;
}

/**
 * Load a collection from Open Search.
 *
 * @param string $id
 *   Id of material to load as a collection.
 *
 * @return Ting\TingObjectCollectionInterface
 *   The collection.
 */
function opensearch_search_collection_load($id) {
  $reply = ting_get_object($id, TRUE);
  return new OpenSearchTingObjectCollection($reply);
}

/**
 * Perform a search.
 *
 * @param \Ting\Search\TingSearchRequest $ting_query
 *   The query to execute.
 *
 * @return \Ting\Search\TingSearchResultInterface
 *   The search result.
 */
function opensearch_search_search(TingSearchRequest $ting_query) {
  // TODO BBS-SAL: At some point this function will become big enough that we
  // Should split it up - consider doing some OO "Handlers". Alternativly do a
  // OpenSearchTingSearchQuery, create a TingSearchQueryInterface and handle its
  // construction via new provider-function.
  // TODO BBS-SAL: At some point we should move the entire ting-client, and
  // ting.client.inc from the thing-module to the opensearch module.
  $query = '';
  // Start off with an empty query, then attempt to construct it from what we
  // can find in the $query.
  if (!empty($simple_query_string = $ting_query->getSimpleQuery())) {
    // Try to build the best search query based on the inputted string.
    if (preg_match('/(^\d+$)|(^\d+:\d+$)|(=)/', $simple_query_string)) {
      // The query is either ISBN, tid or CQL search expression.
      $query = $simple_query_string;
    }
    else {
      // Add wildcard to the search string.
      $query  = _ting_search_quote($simple_query_string) . '*';
    }
  }

  // Perform the Open Search search and wrap the result.
  return new OpenSearchTingSearchResult(ting_do_search($query, 1, 10, array('facets' => $ting_query->getFacets(), 'all Objects' => FALSE)));

}
