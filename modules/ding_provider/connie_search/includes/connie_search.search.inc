<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

use Connie\Search\ConnieSearchResult;
use Connie\Search\ConnieTingObject;
use Connie\Search\ConnieTingObjectCollection;
use Ting\Search\TingSearchCommonFields;
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
  return new ConnieSearchResult($query);
}

/**
 * Given a list of relations, return the relations supported by the provider.
 *
 * @param \TingRelation[] $relations
 *   List of relations.
 *
 * @return \TingRelation[]
 *   List of relations with unsupported relations removed.
 */
function connie_search_search_filter_relations(array $relations) {
  $supported = array_keys(connie_search_search_supported_relations());
  return array_filter($relations,
    function($entry) use ($supported) {
      return in_array($entry->type, $supported);
    }
  );
}

/**
 * Returns a list of relation-types supported by the provider.
 *
 * The array is a list of human-readable titles of the relations keyed by
 * relation types (TingRelation->type).
 *
 * @return string[]
 *   The list of types and titles.
 */
function connie_search_search_supported_relations() {
  return [
    'type1' => 'Relation type 1',
    'type3' => 'Relation type 3',
  ];
}

/**
 * Returns a ting_relation render-array given a TingRelation.
 *
 * @param \TingRelation $relation
 *   The relation to render.
 *
 * @return array
 *   The render array.
 */
function connie_search_search_render_inline_relation(\TingRelation $relation) {
  return [
    '#theme' => 'ting_relation',
    '#title' => 'En anmeldelse',
    '#abstract' => 'Duis pellentesque, sem in luctus interdum, nisl ipsum luctus nulla, vitae tincidunt risus augue ut erat. Vestibulum purus lectus, hendrerit sit amet scelerisque tempus, blandit vel quam. Quisque ac venenatis magna. Sed blandit viverra leo, maximus fringilla augue. Ut rutrum massa ac enim tincidunt, ut volutpat lorem tincidunt. Praesent rhoncus sit amet eros eget tempor. Maecenas dapibus ultricies neque. Curabitur elementum, diam sit amet ullamcorper bibendum, dui lorem porta neque, nec faucibus tellus nibh at elit. Nam sagittis luctus lectus sagittis efficitur.',
    '#online' => FALSE,
    '#target' => '_blank',
    '#relation' => $relation,
  ];
}

/**
 * Mapping of common fields used in conditions to provider-specific names.
 *
 * Condition fields are fields that are used for boolean condition such as
 * dc.type = "something" AND facet.creator = "someone"
 *
 * @return array
 *   Mapping between TingSearchCommonFields::* fields and their provider-
 *   specific counterpart.
 */
function connie_search_search_map_common_condition_fields() {
  return [
    TingSearchCommonFields::ACQUISITION_DATE => 'acquisitionDate',
    TingSearchCommonFields::AUTHOR => 'facet.creator',
    TingSearchCommonFields::CATEGORY => 'facet.category',
    TingSearchCommonFields::LANGUAGE => 'facet.language',
    TingSearchCommonFields::MATERIAL_TYPE => 'dc.type',
    TingSearchCommonFields::SUBJECT => 'facet.subject',
  ];
}

/**
 * Constructs a TingSearchRequest based on a "reference" search query.
 *
 * The implementation should assume that the user has entered a string with the
 * express purpose of finding a specific material. That is, if the string seems
 * to match the pattern of a unique material ID, the query should be constructed
 * to look up by id.
 *
 * The provider can also choose to support advanced provider-specific querying.
 *
 * @param string $query_string
 *   The user-provided search query.
 *
 * @return \Ting\Search\TingSearchRequest
 *   The prepared query object.
 */
function connie_search_search_prepare_reference_query($query_string) {
  $query = ting_start_query();

  if (is_numeric($query_string)) {
    $query->setMaterialFilter($query_string);
  }
  elseif (strpos($query_string, '=') !== FALSE) {
    // The query seems to contain something advanced, process it as a raw query.
    $query->setRawQuery($query_string);
  }
  else {
    // Just perform a general fuzzy search.
    $query->setFuzzy(TRUE);
    $query->setFullTextQuery($query_string);
  }
  return $query;
}
