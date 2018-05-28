<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

use OpenSearch\OpenSearchStatementGroupRender;
use OpenSearch\OpenSearchTingObject;
use OpenSearch\OpenSearchTingObjectCollection;
use OpenSearch\OpenSearchTingSearchResult;
use Ting\Search\DingProviderStrategy;
use Ting\Search\SearchProviderException;
use Ting\Search\TingSearchCommonFields;
use Ting\Search\TingSearchRequest;
use Ting\Search\TingSearchSort;

/**
 * Get a list of material types from the Well.
 */
function opensearch_search_material_types() {
  return _opensearch_get_facet_values('facet.type');
}

/**
 * Get a list of sources from OpenSearch.
 */
function opensearch_search_sources() {
  return _opensearch_get_facet_values('facet.acSource');
}

/**
 * Gets possible values for a facet from OpenSearch.
 *
 * @param string $facet_name
 *   The name of the facet.
 *
 * @return array
 *   A map from facet names to number of results matching that facet.
 */
function _opensearch_get_facet_values($facet_name) {
  // Ensure we have the OpenSearch client loaded.
  module_load_include('inc', 'opensearch', 'opensearch.client');

  // Get a list of types by executing a null query and look at the facets
  // result.
  $options = [
    'facets' => [$facet_name],
    'numFacets' => 99,
    'reply_only' => TRUE,
  ];
  $result = opensearch_do_search("*", 0, 0, $options);

  // Terms is a map from term names to result frequencies.
  $term_names = array_keys($result->facets[$facet_name]->terms);
  return array_map('drupal_strtolower', $term_names);
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
  // Ensure we have OpenSearch client.
  module_load_include('inc', 'opensearch', 'opensearch.client');

  $objects = opensearch_get_objects($ids);
  foreach ($objects as $id => $object) {
    // OpenSearch may return empty entries e.g. for invalid ids. Do not
    // process these.
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
 * @return Ting\TingObjectCollectionInterface|NULL
 *   The collection or NULL if there is no collection for the id.
 */
function opensearch_search_collection_load($id) {
  // Ensure we have OpenSearch client.
  module_load_include('inc', 'opensearch', 'opensearch.client');

  $reply = opensearch_get_object($id, TRUE);
  if ($reply instanceof TingClientObjectCollection) {
    return new OpenSearchTingObjectCollection($reply);
  }
  else {
    return NULL;
  }
}

/**
 * Perform a search.
 *
 * @param \Ting\Search\TingSearchRequest $ting_query
 *   The query to execute.
 *
 * @return \Ting\Search\TingSearchResultInterface
 *   The search result.
 *
 * @throws \TingClientException
 *   If an search error occurs.
 * @throws \Ting\Search\SearchProviderException
 *   If an error occurs during search.
 */
function opensearch_search_search(TingSearchRequest $ting_query) {
  $query_parts = [];
  // Start off with an empty query, then attempt to construct it from what we
  // can find in $ting_query.
  // Provider-specific raw query.
  if (!empty($ting_query->getRawQuery())) {
    $query_parts[] = $ting_query->getRawQuery();
  }

  // Add a general quoted free text search.
  if (!empty($free_text_query = $ting_query->getFullTextQuery())) {
    $cqlDoctor = new TingSearchCqlDoctor($free_text_query);
    $query_parts[] = $cqlDoctor->string_to_cql();
  }

  // Add field filter.
  if (!empty($ting_query->getFilters())) {
    $render = new OpenSearchStatementGroupRender(new DingProviderStrategy());
    try {
      $field_filters = $render->renderStatements(
        $ting_query->getFilters()
      );
    }
    catch (InvalidArgumentException $e) {
      throw new SearchProviderException("Unable to render statements", 0, $e);
    }
    $query_parts[] = $field_filters;
  }

  // Add material filter, this has to be the very last thing we do as we have
  // to handle the filter differently if $query_parts is empty.
  $material_filter = $ting_query->getMaterialFilter();
  if (!empty($material_filter)) {
    if ($ting_query->isMaterialFilterInclude()) {
      // The material filter is a list of IDs to include. Add OR conditions.
      $query_parts[] = implode(' OR ', $material_filter);
    }
    else {
      // We're excluding, meaning we need a NOT in front of all id's. We can't
      // start the query with a NOT so we add a wildcard match to the start of
      // the filter if query is empty.
      if (empty($query_parts)) {
        $query_parts[] = '* NOT ' . implode(' NOT ', $material_filter);
      }
      else {
        $query_parts[] = implode(' NOT ', $material_filter);
      }
    }
  }

  // Join all query-parts together, wrap each part in a parentheses.
  if (!empty($query_parts)) {
    $paran_wrapper = function ($part) {
      return '(' . $part . ')';
    };
    $query = implode(' AND ', array_map($paran_wrapper, $query_parts));
  }
  else {
    $query = '';
  }

  // Prepare options.
  $options = [];

  // Set sort options.
  $field_mapping = _opensearch_search_map_common_sort_fields();
  if (count($ting_query->getSorts()) > 0) {
    // We currently only support a single sort so we pick the first.
    $instance = $ting_query->getSorts()[0];

    // Map from common field back to our sort field.
    if (isset($field_mapping[$instance->getField()])) {
      $field = $field_mapping[$instance->getField()];
    }
    else {
      // Not a common field, so we can assume the field has been provided by
      // opensearch_search_sort_options so no need to map it.
      $field = $instance->getField();
    }

    // First map sort instances to opensearch compatible search strings.
    if ($instance->getDirection() === TingSearchSort::DIRECTION_ASCENDING) {
      $direction = '_ascending';
    }
    elseif ($instance->getDirection() === TingSearchSort::DIRECTION_DESCENDING) {
      $direction = '_descending';
    }
    else {
      $direction = '';
    }

    $opensearch_sort_field = $field . $direction;
    $options['sort'] = $opensearch_sort_field;
  }

  // Set the number of terms we request to get back per facet.
  if ($ting_query->getTermsPerFacet() !== NULL) {
    $options['numFacets'] = $ting_query->getTermsPerFacet();
  }

  if (!empty($ting_query->getFacets())) {
    $options['facets'] = $ting_query->getFacets();
  }

  // Whether to return all materials from matched collections.
  $options['allObjects'] = $ting_query->getPopulateCollections();

  // Determine which collection type to use. Work is default for OpenSearch and
  // we only support one other type.
  if ($ting_query->useCollectionType(TingSearchRequest::COLLECTION_TYPE_SINGLE_OBJECT)) {
    $options['collectionType'] = 'manifestation';
  }

  // Ensure we have OpenSearch client.
  module_load_include('inc', 'opensearch', 'opensearch.client');
  $search_result = opensearch_do_search($query, $ting_query->getPage(), $ting_query->getCount(), $options);
  if (empty($search_result)) {
    throw new SearchProviderException("Unable to execute search, inspect logs for details");
  }

  // Handle the situation where OpenSearch sets a default sort.
  if (empty($ting_query->getSorts()) && !empty($search_result->sortUsed)) {
    $sort_used = $search_result->sortUsed;
    // In situations where we're configured to default to sort by "rank_general"
    // OpenSearch may choose to use rank_main_title for the actual sort. Instead
    // of introducing two different ways of ranking by title, we instead
    // interpret it as "rank_title".
    if ($sort_used === 'rank_main_title') {
      $sort_used = 'rank_title';
    }

    // If the used field is a field we already support, pretend it was picked
    // by the user all along.
    $provider_sorts = opensearch_search_sort_options();
    if (array_key_exists($sort_used, $provider_sorts)) {
      $sort_instance = $provider_sorts[$sort_used]['sort'];
      $ting_query = $ting_query->withSorts($sort_instance);
    }
  }

  return new OpenSearchTingSearchResult($search_result, $ting_query);
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
    function (\TingRelation $relation) use ($relation_types) {

      if (!isset($relation_types[$relation->getType()])) {
        return FALSE;
      }
      // The isPartOfManifestion relation has all relation to other libraries
      // copies of the relation, so we filter the ones that do not belong to
      // current library.
      $object = $relation->getObject();
      if ($relation->getType() === 'dbcbib:isPartOfManifestation' && !empty($object)) {
        $ting_object = $object->getTingObject();
        if (NULL !== $ting_object && $ting_object->isLocal()) {
          return FALSE;
        }
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

  $object = $relation->getObject();
  if (!empty($object) && !empty($object->getTingObject()->getRelations())) {
    $relations = $object->getTingObject()->getRelations();
    if (strpos($relations[0]->getURI(), '[useraccessinfomedia]') === 0) {
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
  $title = FALSE;
  $object = $relation->getObject();
  // Set default fallback title.
  if (!empty($object)) {
    $title = $object->getTitle();
  }

  // Find better title based on relation type.
  switch ($relation->getType()) {
    case 'dbcaddi:hasReview':
      // If the relation has "isPartOf" it's always a better title than the one
      // in the object title as it is always "Anmeldelse".
      $is_part_of = $object->getIsPartOf();
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
  $object = $relation->getObject();

  switch ($relation->getType()) {
    case 'dbcaddi:hasReview':
    case 'dbcaddi:hasSubjectDescription':
    case 'dbcaddi:hasCreatorDescription':
    case 'dbcaddi:hasDescriptionFromPublisher':
      if (!empty($object)) {
        $abstract = $object->getDescription();
        if (empty($abstract)) {
          $abstract = $object->getAbstract();
        }
      }
      break;

    case 'dbcaddi:hasCreatorHomePage':
      // This type of relation is basically a link without an object in the
      // data well.
      $abstract = t('You can find more information about the material on the creators homepage.');
      break;

    case 'dbcbib:isPartOfManifestation':
      if (!empty($object)) {
        $abstract = $object->getSerieDescription();
      }
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
 *   An array containing entries for url and title if found. FALSE if not found.
 */
function _opensearch_search_relation_render_online_url(\TingRelation $relation) {
  $url = FALSE;
  $title = '';

  $object = $relation->getObject();
  switch ($relation->getType()) {
    case 'dbcaddi:hasReview':
    case 'dbcaddi:hasSubjectDescription':
    case 'dbcaddi:hasCreatorDescription':
      if (empty($object)) {
        break;
      }

      // Reservable sources is library material.
      $reservable_sources = variable_get('ting_reservable_sources', _ting_default_reservable_sources());
      if (in_array(strtolower($object->getAc_source()), $reservable_sources)) {
        $title = t('Read more about the material');
        $url = '/ting/object/' . $object->id;
      }
      else {
        $title = t('Read more at %source', array('%source' => $object->getAc_source()));
        $url = $object->getOnline_url();
        $url = empty($url) ? FALSE : $url;

        // Try to make a better link text as part of can contain series
        // information etc.
        $is_part_of = $object->getIsPartOf();
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
      $url = $relation->getURI();
      $title = $relation->getURI();
      break;

    case 'dbcbib:isPartOfManifestation':
      $uri = entity_uri('ting_object', $relation->getObject());
      $url = '/' . $uri['path'];
      $title = $object->getTitle();
      break;
  }

  // If url was found return an array with the url and title.
  if ($url) {
    $url = array(
      'url' => $url,
      'title' => $title,
    );
  }

  // No url found so return FALSE.
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
function _opensearch_search_map_common_sort_fields() {
  return [
    TingSearchCommonFields::TITLE => 'title',
    TingSearchCommonFields::AUTHOR => 'creator',
    TingSearchCommonFields::DATE => 'date',
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
    $query = $query->withRawQuery($query_string);
  }
  else {
    // Do a full-text search with the wildcard character appended to expand
    // search results until we have a hit.
    $query = $query->withFullTextQuery($query_string . '*');
  }

  return $query;
}

/**
 * Provide additional sort options.
 *
 * @return array
 *   List of sort options represented by their labels and a TingSearchSort
 *   instance. Keyed by a machine-name.
 */
function opensearch_search_sort_options() {
  $options = [
    'title_ascending' => [
      'label' => t('Title (Ascending)'),
      'sort' => new TingSearchSort(TingSearchCommonFields::TITLE, TingSearchSort::DIRECTION_ASCENDING),
    ],
      'title_descending' => [
      'label' => t('Title (Descending)'),
      'sort' => new TingSearchSort(TingSearchCommonFields::TITLE, TingSearchSort::DIRECTION_DESCENDING),
    ],
    'creator_ascending' => [
      'label' => t('Creator (Ascending)'),
      'sort' => new TingSearchSort(TingSearchCommonFields::AUTHOR, TingSearchSort::DIRECTION_ASCENDING),
    ],
    'creator_descending' => [
      'label' => t('Creator (Descending)'),
      'sort' => new TingSearchSort(TingSearchCommonFields::AUTHOR, TingSearchSort::DIRECTION_DESCENDING),
    ],
    'date_ascending' => [
      'label' => t('Date (Ascending)'),
      'sort' => new TingSearchSort(TingSearchCommonFields::DATE, TingSearchSort::DIRECTION_ASCENDING),
    ],
    'date_descending' => [
      'label' => t('Date (Descending)'),
      'sort' => new TingSearchSort(TingSearchCommonFields::DATE, TingSearchSort::DIRECTION_DESCENDING),
    ],
  ];

  // Do not show sort-options specific for rank_frequency if
  // custom_ranking is enabled or another rank is selected.
  $default_sort = variable_get('opensearch_sort_default', 'rank_frequency');
  $custom_ranking = variable_get('opensearch_ranking_custom', FALSE);
  if ($default_sort === 'rank_frequency' && empty($custom_ranking)) {
    $options = array_merge($options, [
      'rank_title' => [
        'label' => t('Best match on title'),
        'label_short' => t('Title'),
        'sort' => new TingSearchSort('rank_title'),
      ],
      'rank_creator' => [
        'label' => t('Best match on creator'),
        'label_short' => t('Creator'),
        'sort' => new TingSearchSort('rank_creator'),
      ],
      'rank_subject' => [
        'label' => t('Best match on subject'),
        'label_short' => t('Subject'),
        'sort' => new TingSearchSort('rank_subject'),
      ],
    ]);
  }

  return $options;
}

/**
 * Helper function to create data well 3 PID's from faust/record id.
 *
 * This function is placed in the provider and not "ting" module as the
 * providers uses it and we don't want to have a binding from providers to ting.
 *
 * @param mixed $ids
 *   A string with a single faust to be translated.
 *   An array with multiple faust to be translated.
 *
 * @return mixed
 *   Single faust: A string with data well PID.
 *   Array of fausts: An array with data well PIDs keyed be the original faust.
 *   In both cases, if a faust couldn't be translated, the PID will be the
 *   original faust with the standard DBC namespace "870970-basis:".
 */
function opensearch_search_object_ids($ids) {
  if (is_array($ids) && !empty($ids)) {
    $translated_ids = array();

    // Open search is limited to 50 results per call, so split up in chunks to
    // ensure we get PIDs for all passed local IDs.
    foreach (array_chunk($ids, 50) as $chunk) {
      $query = 'rec.id any "' . implode(" ", $chunk) . '" AND facet.acSource=bibliotekskatalog';
      // Ensure that the work match in opensearch doesn't hide ids for us.
      $options['collectionType'] = 'manifestation';

      // Ensure we have OpenSearch client.
      module_load_include('inc', 'opensearch', 'opensearch.client');
      $res = opensearch_do_search($query, 1, count($chunk), $options);

      // Sometimes the well will be unreachable or not even one of the ids in
      // chunk was searchable. In any case, this protects against a notice.
      if (empty($res)) {
        continue;
      }

      foreach ($res->collections as $pid => $collection) {
        $faust = explode(':', $pid)[1];
        if ($key = array_search($faust, $ids)) {
          $translated_ids[$faust] = $pid;
          unset($ids[$key]);
        }
      }
    }

    // The faust left in ids array where not searchable and we could therefore
    // not determine the proper namespace. Since it's possible to load objects
    // separately, that are not searchable with the library's agencyid, the best
    // we can do here is to use the standard DBC agency id, which is used for
    // basis-records. The providers can then try ting_get_object with this PID,
    // which may work (if it's not an inter-library loan of a local post).
    // TODO: We should provide a separate mechanism for translating faust
    // without holdingsitem.agencyid filter. This way the providers will know
    // which materials can be searched with the current agency id and generate
    // a link to them.
    //
    foreach ($ids as $faust) {
      $translated_ids[$faust] = '870970-basis:' . $faust;
    }

    return $translated_ids;
  }
  elseif (is_numeric($ids)) {
    module_load_include('client.inc', 'opensearch');
    $obj = opensearch_do_search('rec.id=' . $ids . ' AND facet.acSource=bibliotekskatalog');
    return !empty($obj) ? key($obj->collections) : '870970-basis:' . $ids;
  }
  return FALSE;
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
function opensearch_search_autocomplete($query) {
  $items = array();

  $rest_url = variable_get('opensearch_search_autocomplete_suggestion_url', '');
  $method = variable_get('ting_search_autocomplete_method', 'facets');
  $settings = opensearch_search_autocomplete_settings();

  if (drupal_strlen($query) < $settings['minimumString']) {
    return $items;
  }
  unset($settings['minimumString']);

  if (empty($settings['index'])) {
    watchdog('opensearch', 'Autocomplete index not defined ', array(), $severity = WATCHDOG_WARNING);
    return $items;
  }

  $rest_url = $rest_url . 'rest/' . $method;
  $settings['query'] = $query;
  $url = url($rest_url, array('query' => $settings));

  $result = drupal_http_request($url);

  if (!empty($result->data)) {
    $result_data = drupal_json_decode($result->data);
    if (empty($result->error)) {
      if (!empty($result_data['suggestions'])) {
        foreach ($result_data['suggestions'] as $suggestion) {
          if ($method === 'facetSpell') {
            $items[truncate_utf8(strip_tags($suggestion['phrase']), 256, TRUE, FALSE, 1)] = $suggestion['phrase'];
          }
          else {
            $items[truncate_utf8(strip_tags($suggestion['suggestion']), 256, TRUE, FALSE, 1)] = $suggestion['suggestion'];
          }
        }
      }
    }
    else {
      $message = t('Autocomplete error: @error (@error_code) using following URL: @url');
      watchdog('opensearch', $message, array(
        '@error' => $result->error,
        '@error_code' => $result->code,
        '@url' => $url,
      ), WATCHDOG_ERROR);
    }
  }

  return $items;
}
