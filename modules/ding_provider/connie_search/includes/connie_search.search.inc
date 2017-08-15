<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

use Connie\Search\ConnieSearchResult;
use Connie\Search\ConnieTingObject;
use Connie\Search\ConnieTingObjectCollection;
use Ting\Search\TingSearchRequest;

/**
 * Get a list of material types from the Well.
 *
 * @return string[]
 *   List of material names.
 */
function connie_search_search_material_types() {
  return ['material_type_1', 'material_type_2'];
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
function connie_search_search_object_load(array $ids) {
  return [new ConnieTingObject()];
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
function connie_search_search_collection_load($id) {
  return ConnieTingObjectCollection::getSingleCollection();
}

/**
 * Perform a search.
 *
 * @param \Ting\Search\TingSearchRequest $query
 *   The query to execute.
 *
 * @return \Ting\Search\TingSearchResultInterface
 *   The search result.
 */
function connie_search_search_search(TingSearchRequest $query) {
  return new ConnieSearchResult();

}
