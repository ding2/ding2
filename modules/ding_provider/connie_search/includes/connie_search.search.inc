<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

use Connie\Search\ConnieSearchResult;
use Connie\Search\ConnieTingObject;
use Connie\Search\ConnieTingObjectCollection;
use Ting\Search\TingSearchRequest;
use Ting\Search\TingSearchSort;

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
 * Get a list of search sources.
 *
 * @return string[]
 *   List of search sources.
 */
function connie_search_search_sources() {
  return ['source A', 'source B'];
}

/**
 * Load objects from the search system.
 *
 * @param string[] $ids
 *   Array of ids to load from the search system.
 *
 * @return Ting\TingObjectInterface[]
 *   An array of loaded objects.
 */
function connie_search_search_object_load(array $ids) {
  $objects = array_map(function($id) {
    return new ConnieTingObject($id);
  }, $ids);
  return array_combine($ids, $objects);
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
  return ConnieTingObjectCollection::getSingleCollection($id);
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
    function ($entry) use ($supported) {
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
    $query = $query->withMaterialFilter($query_string);
  }
  elseif (strpos($query_string, '=') !== FALSE) {
    // The query seems to contain something advanced, process it as a raw query.
    $query = $query->withRawQuery($query_string);
  }
  else {
    // Just perform a general full text search.
    $query = $query->withFullTextQuery($query_string);
  }
  return $query;
}

/**
 * Provide additional sort options.
 *
 * The provider could return an array of 0 or more "sorts" where each sort is
 * keyed by a machine-name. Each entry must specify a label that will be used
 * for the "long" description of the sort, eg. in <option> elements, a
 * label_short that will be used in messages, and finally an instance of
 * TingSearchSort that describes the sort direction and field.
 *
 * @return array
 *   List of sort options represented by their labels and a TingSearchSort
 *   instance. Keyed by a machine-name.
 */
function connie_search_search_sort_options() {
  return [
    'duck_type' => [
      // General label for the option typically used in <option> elements.
      'label' => t('Sort on type of duck'),
      // Short label for the option, typically used in messages.
      'label_short' => t('Ducktype'),
      'sort' => new TingSearchSort('connie_duck_type', TingSearchSort::DIRECTION_DESCENDING),
    ],
  ];
}

/**
 * Provide standard object ID's for connie provider.
 *
 * @param mixed $ids
 *   Array with multiple ID's or a single ID.
 *
 * @return array|string
 *   Array with multiple ID's. ID/faust as key and object ID as value.
 *   If a string is provided as parameter, a string with object ID.
 */
function connie_search_search_object_ids($ids) {
  if (is_array($ids) && !empty($ids)) {
    $translated_ids = array();
    /** @var array $ids */
    foreach ($ids as $id) {
      $translated_ids[$id] = '1337-test:' . $id;
    }
    return $translated_ids;
  }

  if (is_numeric($ids)) {
    return '1337-test:' . $ids;
  }
}

/**
 * Auto-complete callback for the ting search block.
 *
 * @param string $query
 *   The string to search suggestion with.
 *
 * @return string[]
 *   Items similar to the query.
 */
function connie_search_search_autocomplete($query) {
  $items = array();

  $results = array(
    'Harry Potter and the Goblet of Fire',
    'The Hobbit',
    'The Da Vinci Code',
    '1984',
    'The Hunger Games',
    'Game of Thrones',
    'The Inside',
    'The Shining',
    'Dracula',
    'Time Travellers Wife',
  );

  if (!empty($results)) {
    foreach ($results as $result) {
      if (similar_text($query, $result) > 3) {
        $items[] = $result;
      }
    }
  }
  else {
    $message = t('Autocomplete error: @error (@error_code) using following URL: @url');
    watchdog('connie_search', $message, array(
      '@error' => 'Woops, something went wrong!',
      '@error_code' => '500',
      '@url' => 'http://localhost/rest/autocomplete',
    ), WATCHDOG_ERROR);
  }

  return $items;
}

/**
 * Generate a query string corresponding to a query.
 *
 * @param \Ting\Search\TingSearchRequest $ting_query
 *   The query to base the string on.
 *
 * @return string
 *   The query in string form.
 */
function connie_search_search_query_string(TingSearchRequest $query) {
  return $query->getFullTextQuery();
}
