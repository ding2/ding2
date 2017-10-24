<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

use OpenSearch\OpenSearchTingObject;
use OpenSearch\OpenSearchTingObjectCollection;
use OpenSearch\OpenSearchTingSearchResult;
use Ting\Search\DingProviderStrategy;
use Ting\Search\StatementGroupRender;
use Ting\Search\TingSearchCommonFields;
use Ting\Search\TingSearchRequest;

/**
 * Get a list of material types from the Well.
 */
function opensearch_search_material_types() {
  // Ensure we have ting client.
  module_load_include('inc', 'ting', 'ting.client');

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
  // Ensure we have ting client.
  module_load_include('inc', 'ting', 'ting.client');

  // TODO BBS-SAL: At some point this function will become big enough that we
  // Should split it up - consider doing some OO "Handlers". Alternativly do a
  // OpenSearchTingSearchQuery, create a TingSearchQueryInterface and handle its
  // construction via new provider-function.
  // TODO BBS-SAL: At some point we should move the entire ting-client, and
  // ting.client.inc from the thing-module to the opensearch module.
  $query_parts = [];
  // Start off with an empty query, then attempt to construct it from what we
  // can find in $ting_query.
  // Provider-specific raw query.
  if (!empty($ting_query->getRawQuery())) {
    $query_parts[] = $ting_query->getRawQuery();
  }

  // Add a general quoted free text search.
  if (!empty($free_text_query = $ting_query->getFullTextQuery())) {
    $free_text_query = _ting_search_quote($ting_query->getFullTextQuery());
    if ($ting_query->isFuzzy()) {
      $free_text_query = '*' . $free_text_query . '*';
    }
    $query_parts[] = $free_text_query;
  }

  // Add material filter.
  if (!empty($ting_query->getMaterialFilter())) {
    $material_filter_string = implode(' OR ', $ting_query->getMaterialFilter());
    $query_parts[] .= $material_filter_string;
  }

  // Add field filter.
  if (!empty($ting_query->getFieldFilters())) {
    $render = new StatementGroupRender(new DingProviderStrategy());
    $field_filters = $render->renderStatements($ting_query->getFieldFilters());
    $query_parts[] = $field_filters;
  }

  // Join all query-parts together, wrap each part in a parentheses.
  if (!empty($query_parts)) {
    $paran_wrapper = function($part) {
      return '(' . $part . ')';
    };
    $query = implode(' AND ', array_map($paran_wrapper, $query_parts));
  }
  else {
    $query = '';
  }

  // TODO: Handle sorts.
  // Perform the Open Search search and wrap the result.
  $options = [];
  if (!empty($ting_query->getFacets())) {
    $options['facets'] = $ting_query->getFacets();
  }

  // Whether to return all materials from matched collections.
  $options['allObjects'] = $ting_query->getPopulateCollections();

  return new OpenSearchTingSearchResult(ting_do_search($query, $ting_query->getPage(), $ting_query->getCount(), $options), $query);
}

/**
 * Allows the provider to programtically filter relations.
 *
 * @return array
 *   Filtered list.
 */
function opensearch_search_filter_relations($relations) {
  $relation_types = opensearch_search_supported_relations();

  return array_filter($relations,
    function($relation) use ($relation_types) {

      if (!isset($relation_types[$relation->type])) {
        return FALSE;
      }
      // The isPartOfManifestion relation has all relation to other libraries
      // copies of the relation, so we filter the ones that do not belong to
      // current library.
      if ($relation->type == 'dbcbib:isPartOfManifestation' && is_object($relation->object) && $relation->object instanceof TingEntity && $relation->object->reply->isLocal()) {
        return FALSE;
      }
      return TRUE;
    }
  );
}

/**
 * Produce a list of relations we can handle.
 *
 * @return string[]
 *   Array of supported type-titles keyed by type name.
 */
function opensearch_search_supported_relations() {
  return [
      'dbcaddi:hasCreatorDescription' => t('Author portrait'),
      'dbcaddi:hasReview' => t('Review'),
      'dbcaddi:hasSubjectDescription' => t('Subject description'),
      'dbcaddi:hasDescriptionFromPublisher' => t('Description from publisher'),
      'dbcaddi:hasCreatorHomePage' => t('Creator homepage'),
      'dbcbib:isPartOfManifestation' => t('Is part of manifestation'),
  ];
}

/**
 * Some relations are requested NOT to load a new window.
 *
 * @param \TingRelation $relation
 *   The relation to handle.
 *
 * @return string
 *   Target attribute for link, "_blank" or "_self".
 *
 * @see http://platform.dandigbib.org/issues/378
 */
function _opensearch_search_relation_render_target(\TingRelation $relation) {
  $target = '_blank';
  $data = isset($relation->getObject()->reply->relationsData) ?
    $relation->getObject()->reply->relationsData : NULL;
  if (isset($data)) {
    if (strpos($data[0]->relationUri, '[useraccessinfomedia]') === 0) {
      $target = '_self';
    }
  }
  return $target;
}



/**
 * Finds the best title for a relation based on the relation type.
 *
 * @param \TingRelation $relation
 *   The relation entity to get title from.
 *
 * @return string|bool
 *   The title found in the object or FALSE if non found.
 */
function _opensearch_search_relation_render_title(\TingRelation $relation) {
  // Set default fallback title.
  $title = isset($relation->object->title) ? $relation->object->title : FALSE;

  // Find better title based on relation type.
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
      // If the relation has "isPartOf" it's always a better title than the one
      // in  object title as it is always "Anmeldelse".
      $is_part_of = $relation->object->getIsPartOf();
      if (!empty($is_part_of)) {
        $title = reset($is_part_of);
      }
      break;
  }

  return $title;
}

/**
 * Get the abstract from a TingRelation entity based on its type.
 *
 * @param \TingRelation $relation
 *   The relation entity to get abstract from.
 *
 * @return string|bool
 *   The abstract found or FALSE if non found.
 */
function _opensearch_search_relation_render_abstract(\TingRelation $relation) {
  $abstract = FALSE;
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
    case 'dbcaddi:hasSubjectDescription':
    case 'dbcaddi:hasCreatorDescription':
    case 'dbcaddi:hasDescriptionFromPublisher':

      $abstract = $relation->object->getDescription();
      if (empty($abstract)) {
        $abstract = $relation->object->getAbstract();
      }
      break;

    case 'dbcaddi:hasCreatorHomePage':
      // This type of relation is basically a link without an object in the
      // data well.
      $abstract = t('You can find more information about the material on the creators homapge.');
      break;

    case 'dbcbib:isPartOfManifestation':
      $abstract = $relation->object->getSerieDescription();
      break;
  }

  return empty($abstract) ? FALSE : $abstract;
}

/**
 * Get the online url from a TingRelation entity based on its type.
 *
 * @param \TingRelation $relation
 *   The relation entity to get abstract from.
 *
 * @return array|bool
 *   The online url found or FALSE if non found.
 */
function _opensearch_search_relation_render_online_url(\TingRelation $relation) {
  $url = FALSE;
  $title = '';
  switch ($relation->type) {
    case 'dbcaddi:hasReview':
    case 'dbcaddi:hasSubjectDescription':
    case 'dbcaddi:hasCreatorDescription':
      // Reservable sources is library material.
      $reservable_sources = variable_get('ting_reservable_sources', _ting_default_reservable_sources());
      if (in_array(strtolower($relation->object->getAc_source()), $reservable_sources)) {
        $title = t('Read more about the material');
        $url = '/ting/object/' . $relation->object->id;
      }
      else {
        $title = t('Read more at %source', array('%source' => $relation->object->getAc_source()));
        $url = $relation->object->getOnline_url();
        $url = empty($url) ? FALSE : $url;

        // Try to make a better link text as part of can contain series
        // information etc.
        $is_part_of = $relation->object->getIsPartOf();
        if (!empty($is_part_of)) {
          $title = reset($is_part_of);
        }
      }
      break;

    case 'dbcaddi:hasDescriptionFromPublisher':
      // This type have a doc-book "read more" link, which is handled by
      // ting_fulltext.
      break;

    case 'dbcaddi:hasCreatorHomePage':
      // This type of relation is basically a link without an object in the
      // data well.
      $url = $relation->uri;
      $title = $relation->uri;
      break;

    case 'dbcbib:isPartOfManifestation':
      $uri = entity_uri('ting_object', $relation->getObject());
      $url = '/' . $uri['path'];
      $title = $relation->object->getTitle();
      break;
  }

  // If url was found return an array with the url and title.
  if ($url) {
    return array(
      'url' => $url,
      'title' => $title,
    );
  }

  // No url found so return FALSE;
  return $url;
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
function opensearch_search_render_inline_relation(TingRelation $relation) {
  return [
    '#theme' => 'ting_relation',
    '#title' => _opensearch_search_relation_render_title($relation),
    '#abstract' => _opensearch_search_relation_render_abstract($relation),
    '#online' => _opensearch_search_relation_render_online_url($relation),
    '#target' => _opensearch_search_relation_render_target($relation),
    '#relation' => $relation,
  ];
}

/**
 * Mapping between common fields and their provider-specific name.
 *
 * @return array
 *   Mapping between TingSearchCommonFields::* fields and their provider-
 *   specific counterpart.
 */
function opensearch_search_map_common_fields() {
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
function opensearch_search_prepare_reference_query($query_string) {
  $query = ting_start_query();

  // Try to build the best search query based on the inputted string.
  if (preg_match('/(^\d+$)|(^\d+:\d+$)|(=)/', $query_string)) {
    // The query is either ISBN, tid or CQL search expression.
    // Add as raw (eg non-escaped) string.
    $query->setRawQuery($query_string);
  }
  else {
    // Do a full-text search.
    $query->setFuzzy(TRUE);
    $query->setFullTextQuery($query_string);
  }

  return $query;
}
