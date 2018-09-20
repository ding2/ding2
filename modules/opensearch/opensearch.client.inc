<?php
/**
 * @file
 * Wrapper functions for Opensearch client.
 */

/**
 * Get an ting object or collection.
 *
 * Returns the search response for the given id. This will cache the
 * result, and any sub-objects, so fetching objects from a recently
 * fetched collection won't trigger another backend request.
 *
 * @param string $object_id
 *   The id to fetch.
 * @param bool $collection
 *   Whether to return a collection, if possible, or an object.
 * @param bool $with_relations
 *   Whether to return all relations. Defaults to FALSE.
 *
 * @return bool|mixed|null|\TingClientSearchResult
 *   Ting object or object collection if $collection is TRUE and a collection
 *   was found. NULL is returned if no object or collection could be retrieved.
 *
 * @throws \TingClientException
 *   This may throw this exception if the search request fails.
 */
function opensearch_get_object($object_id, $collection = FALSE, $with_relations = FALSE) {
  if (!empty($object_id)) {
    if ($collection) {
      // If this is a collection we need to do a collection request, which is
      // a search request.
      $request = opensearch_get_request_factory()->getCollectionRequest();
      $request->setAllObjects(FALSE);
    }
    else {
      $request = opensearch_get_request_factory()->getObjectRequest();
    }
    $request->setObjectId($object_id);

    // Set agency from the administration interface.
    if ($agency = variable_get('ting_agency', FALSE)) {
      $request->setAgency($agency);
    }

    // Set search profile from the administration interface.
    $profile = variable_get('opensearch_search_profile', '');
    if (!empty($profile)) {
      $request->setProfile($profile);
    }

    // Get all relations for the object.
    if ($with_relations) {
      $request->setAllRelations(TRUE);
      $request->setRelationData('full');
    }

    // Execute the request.
    $result = opensearch_execute($request);

    return $collection || is_null($result) ? $result : reset($result);
  }

  return NULL;
}

/**
 * Get a bunch of objects in one request.
 *
 * @param string[] $ids
 *   Data-well PIDs for the objects to get.
 *
 * @return bool|\TingClientSearchResult
 *   The objects fetched from the data-well.
 *
 * @throws \TingClientException
 *   This may throw this exception if the search request fails.
 */
function opensearch_get_objects(array $ids) {
  $request = opensearch_get_request_factory()->getObjectRequest();
  $request->setObjectIds($ids);

  // Set agency from the administration interface.
  if ($agency = variable_get('ting_agency', FALSE)) {
    $request->setAgency($agency);
  }

  // Set search profile from the administration interface.
  $profile = variable_get('opensearch_search_profile', '');
  if (!empty($profile)) {
    $request->setProfile($profile);
  }

  return opensearch_execute($request);
}

/**
 * Performs a search against the well.
 *
 * @param string $query
 *   The search query
 * @param int $page
 *   The page number to retrieve search results for
 * @param int $results_per_page
 *   The number of results to include per page
 * @param array $options
 *   Options to pass to the search. Possible options are:
 *    - facets: Array of facet names for which to return results. Default:
 *      facet.subject, facet.creator, facet.type, facet.date, facet.language
 *    - numFacets: The number of terms to include with each facet. Default: 10
 *    - sort: The key to sort the results by. Default: "" (corresponds to
 *      relevance). The possible values are defined by the sortType type
 *      in the XSD.
 *    - rank: The ranking type, as defined in the XSD.
 *    - supportingTypes: Whether to include supporting types such as reviews.
 *      Default: false
 *    - reply_only: Don't change the result objects to TingCollection objects.
 *    - collectionType: The type of results to return. Single
 *      manifestions(object) or works (collections). Possible values
 *      manifestion ,work or work-1. Defaults to work.
 *
 * @return TingClientSearchResult
 *   The search result.
 *
 * @throws \TingClientException
 *   This may throw this exception if the search request fails.
 */
function opensearch_do_search($query, $page = 1, $results_per_page = 10, $options = array()) {
  $request = opensearch_get_request_factory()->getSearchRequest();

  $request->setQuery($query);
  if ($agency = variable_get('ting_agency', FALSE)) {
    $request->setAgency($agency);
  }
  $request->setStart($results_per_page * ($page - 1) + 1);
  $request->setNumResults($results_per_page);

  if (!isset($options['facets']) and module_exists('ding_facetbrowser')) {
    $options['facets'] = array();
    // Populate facets with configured facets.
    foreach (variable_get('ding_facetbrowser_facets', array()) as $facet) {
      $options['facets'][] = $facet['name'];
    }
  }

  $default_facets = array(
    'facet.subject',
    'facet.creator',
    'facet.type',
    'facet.category',
    'facet.language',
    'facet.date',
    'facet.acSource',
  );
  $request->setFacets((isset($options['facets'])) ? $options['facets'] : $default_facets);
  $request->setNumFacets((isset($options['numFacets'])) ? $options['numFacets'] : ((count($request->getFacets()) == 0) ? 0 : 10));
  if (isset($options['sort']) && $options['sort']) {
    $request->setSort($options['sort']);
  }
  else {
    $sort = variable_get('opensearch_sort_default', 'rank_frequency');
    $request->setSort($sort);
  }

  if (isset($options['collectionType'])) {
    $request->setCollectionType($options['collectionType']);
  }
  $request->setAllObjects(isset($options['allObjects']) ? $options['allObjects'] : FALSE);

  // Set search profile, if applicable.
  $profile = variable_get('opensearch_search_profile', '');
  if (!empty($profile)) {
    $request->setProfile($profile);
  }

  // Apply custom ranking if enabled.
  if (variable_get('opensearch_ranking_custom', FALSE) && variable_get('opensearch_ranking_fields', array()) && !isset($options['sort'])) {
    $fields = array();
    foreach (variable_get('opensearch_ranking_fields', array()) as $field) {
      $fields[] = array(
        'fieldName' => $field['field_name'],
        'fieldType' => $field['field_type'],
        'weight' => $field['weight'],
      );
    }

    if (!empty($fields)) {
      // Add the default anyIndex boosts.
      $fields[] = array(
        'fieldName' => 'term.default',
        'fieldType' => 'phrase',
        'weight' => 2,
      );

      $fields[] = array(
        'fieldName' => 'term.default',
        'fieldType' => 'word',
        'weight' => 1,
      );

      $request->userDefinedRanking = array('tieValue' => 0.1, 'rankField' => $fields);
    }
  }
  // Apply custom boosts if any.
  $boosts = variable_get('opensearch_boost_fields', array());

  if ($boosts) {
    $uboosts = array();
    foreach ($boosts as $boost_field) {
      $uboosts[] = array(
        'fieldName' => $boost_field['field_name'],
        'fieldValue' => $boost_field['field_value'],
        'weight' => $boost_field['weight'],
      );
    }
    $request->userDefinedBoost = $uboosts;
  }

  $search_result = opensearch_execute($request);

  // Replace collections with proper TingCollection objects.
  if ($search_result && is_array($search_result->collections)) {
    $ids = array();
    foreach ($search_result->collections as &$collection) {
      if (isset($collection->objects[0])) {
        $ids[] = $collection->objects[0]->id;
      }
    }
    if (!isset($options['reply_only']) || !$options['reply_only']) {
      $search_result->collections = entity_load('ting_collection', array(), array('ding_entity_id' => $ids));
    }
  }

  return $search_result;
}

/**
 * Get a ting object from the well in marcxchange format.
 *
 * @param string $object_id
 *   Object identifier.
 *
 * @return bool|\TingClientSearchResult
 *   The search result.
 *
 * @throws \TingClientException
 *   This may throw this exception if the search request fails.
 */
function opensearch_get_object_marcxchange($object_id) {
  $request = opensearch_get_request_factory()->getMarcXchangeRequest();

  $request->setAgency(variable_get('ting_agency'));
  $request->setProfile(variable_get('opensearch_search_profile'));
  $request->setIdentifier($object_id);

  return opensearch_execute($request);
}

/**
 * Get recommendations for a given ISBN.
 *
 * @param string $isbn
 *   ISBN number to get recommendations from.
 * @param int $num_results
 *   The number of results to return.
 *
 * @return bool|\TingClientSearchResult
 *   An array of TingClientObjectRecommendation objects.
 *
 * @throws \TingClientException
 *   This may throw this exception if the search request fails.
 */
function opensearch_get_object_recommendations($isbn, $num_results = 10) {
  $request = opensearch_get_request_factory()->getObjectRecommendationRequest();
  $request->setIsbn($isbn);
  $request->setNumResults($num_results);

  return opensearch_execute($request);
}

/**
 * Retrieves an initialized Ting client request factory.
 *
 * @return TingClientRequestFactory
 *   TingClientRequestFactory object.
 *
 * @throws TingClientException
 *   If there is no end-point url defined in the configuration this exception is
 *   thrown.
 */
function opensearch_get_request_factory() {
  static $request_factory;

  if (!isset($request_factory)) {
    $url_variables = array(
      'search' => 'opensearch_url',
      'object' => 'opensearch_url',
      'collection' => 'opensearch_url',
      'recommendation' => 'opensearch_recommendation_url',
    );

    // TODO: This should probably be rethought.
    if (module_exists('ting_infomedia') && variable_get('ting_infomedia_url', FALSE)) {
      $url_variables['infomedia'] = 'ting_infomedia_url';
    }

    $urls = array();
    foreach ($url_variables as $name => $setting) {
      $urls[$name] = variable_get($setting, FALSE);
      if (!$urls[$name]) {
        throw new TingClientException('No Ting webservice url defined for ' . $name);
      }
    }

    $auth = array();
    if (variable_get('opensearch_use_auth', FALSE)) {
      $auth = array(
        'name' => variable_get('opensearch_auth_name', ''),
        'pass' => variable_get('opensearch_auth_pass', ''),
        'group' => variable_get('opensearch_auth_group', ''),
      );
    }

    $request_factory = new TingClientRequestFactory($urls, $auth);
  }

  return $request_factory;
}

/**
 * Perform a request against Ting and perform error handling if necessary.
 *
 * @param \TingClientRequest $request
 *   The request.
 *
 * @return \TingClientSearchResult|bool
 *   Result of the request or false if an error occurs.
 */
function opensearch_execute(TingClientRequest $request) {
  // Get additional parameters from other modules.
  $params = module_invoke_all('opensearch_pre_execute', $request);
  if (!empty($params)) {
    $request->setParameters($params);
  }

  // Due to the way the entity module is used to handle ting_objects a search
  // with get all relations is going to be triggered for almost all requests. So
  // to pre-heat the cache the optimal solution will be to get all relations
  // within the first search request and predict the next request and put that
  // result into the cache based on the first result. This will result in an
  // slower first request but overall a lot fewer request to the data well in
  // the search pages.
  if ($request instanceof TingClientCollectionRequest || $request instanceof TingClientObjectRequest || $request instanceof TingClientSearchRequest) {
    $request->setAllRelations(TRUE);
    $request->setRelationData('full');
  }

  // Build cache id for this request.
  $cid = _opensearch_cache_id($request);

  // Check static cache first as this is the fasts lookup. We use the fast
  // static pattern described on drupal.org in the drupal_static
  // documentation.
  static $opensearch_static_fast = array();
  if (array_key_exists($cid, $opensearch_static_fast)) {
    return $opensearch_static_fast[$cid];
  }

  // Check the database/memcached cache for the request also check that the
  // cache data has not expired before using it.
  $cache = cache_get($cid, 'cache_opensearch');
  if ($cache && ($cache->expire > REQUEST_TIME)) {
    $data = $cache->data;

    // Update the static cache with the database cache content to speed up the
    // next request for the same data.
    $opensearch_static_fast[$cid] = $data;

    return $data;
  }

  try {
    timer_start('ting');
    $res = _opensearch_get_client()->execute($request);

    // When the request is for fulltext (doc-book) the result is XML but the
    // next part expect JSON only formatted input. So this hack simply return
    // the XML for now as later on we have to work with open format and XML
    // parsing. So for now simply return the result to fulltext.
    if ($request instanceof TingClientObjectRequest && $request->getOutputType() == 'xml' && $request->getObjectFormat() == 'docbook') {
      return $res;
    }

    $response = $request->parseResponse($res);

    // Pass parsed results to other modules.
    $props = module_invoke_all('opensearch_post_execute', $request, $response, $res);
    if (!empty($props)) {
      foreach ($props as $property => $value) {
        $response->{$property} = $value;
      }
    }

    // Update the cache with the raw response object from the data well for
    // faster processing. Also set the static cache.
    _opensearch_cache_insert($request, $response, $opensearch_static_fast);

    // To speed up the entity module, which will trigger an search for each
    // collection. Try and predict the search request an warm up the cache.
    // Alternative rewrite the whole ting entity module, which currently is
    // overkill.
    if ($response instanceof TingClientSearchResult) {
      _opensearch_predict_cache($response->collections, $opensearch_static_fast, $request);
    }

    return $response;
  }
  catch (TingClientException $e) {
    if (isset($e->user_message)) {
      drupal_set_message($e->user_message, 'warning');
    }
    watchdog('ting client', 'Error performing request: ' . $e->getMessage(), NULL, WATCHDOG_ERROR, 'http://' . $_SERVER["HTTP_HOST"] . request_uri());
    return FALSE;
  }
  finally {
    timer_stop('ting');
  }
}

/**
 * Try and predict future search requests and warm up cache.
 *
 * Base on the collections given and the entity model for ting objects we expect
 * the next search requests to be getCollectionRequest and getObjectRequest. The
 * information to populate the cache with response to this exists in the first
 * search request.
 *
 * So the cache can be warm-up based on the first TingClientSearchResult object.
 *
 * @param array $collections
 *   The collections found in TingClientSearchResult object.
 * @param array $opensearch_static_fast
 *   The fast static cache used by opensearch_execute().
 * @param TingClientRequest $request
 *   The request used to get the collections.
 *
 * @throws \TingClientException
 *   If the search client request fails.
 */
function _opensearch_predict_cache(array $collections, array &$opensearch_static_fast, TingClientRequest $request) {
  foreach ($collections as $collection) {
    if (is_object($collection->objects[0])) {
      $object = reset($collection->objects);

      $collection_request = opensearch_get_request_factory()->getCollectionRequest();
      $collection_request->setAllObjects(FALSE);
      $collection_request->setObjectId($object->id);
      $collection_request->setQuery('*:*');

      // See opensearch_execute() for description of always getting all relations.
      $collection_request->setAllRelations(TRUE);
      $collection_request->setRelationData('full');

      // Set agency from the administration interface.
      if ($agency = variable_get('ting_agency', FALSE)) {
        $collection_request->setAgency($agency);
      }

      // Set search profile from the administration interface.
      $profile = variable_get('opensearch_search_profile', '');
      if (!empty($profile)) {
        $collection_request->setProfile($profile);
      }

      // Get additional parameters from other modules.
      $params = module_invoke_all('opensearch_pre_execute', $collection_request);
      if (!empty($params)) {
        $collection_request->setParameters($params);
      }

      // Build the response that matches the request and put it into cache.
      $collection_response = new TingClientObjectCollection($collection->objects);
      _opensearch_cache_insert($collection_request, $collection_response, $opensearch_static_fast);

      $object_request = opensearch_get_request_factory()->getObjectRequest();
      $object_request->setObjectId($object->id);

      // See opensearch_execute() for description of always getting all relations.
      $object_request->setAllRelations(TRUE);
      $object_request->setRelationData('full');

      // Set agency from the administration interface.
      if ($agency = variable_get('ting_agency', FALSE)) {
        $object_request->setAgency($agency);
      }

      // Set search profile from the administration interface.
      $profile = variable_get('opensearch_search_profile', '');
      if (!empty($profile)) {
        $object_request->setProfile($profile);
      }

      // Build the response that matches the request and put it into cache.
      $object_response = array();
      $object_response[$object->id] = clone $object;
      _opensearch_cache_insert($object_request, $object_response, $opensearch_static_fast);
    }
    else {
      watchdog('opensearch', 'Predict cache found collection with empty objects. Search query: @query', array('@query' => $request->getQuery()), WATCHDOG_WARNING);
    }
  }
}

/**
 * Insert search response based on request.
 *
 * @param TingClientRequest $request
 *   The search request that gives the response.
 * @param \TingClientObject|\TingClientObjectCollection|array $response
 *   The response to the request.
 * @param array $opensearch_static_fast
 *   The fast static cache used by opensearch_execute().
 */
function _opensearch_cache_insert(TingClientRequest $request, $response, array &$opensearch_static_fast) {
  $cid = _opensearch_cache_id($request);

  // Update the cache with the raw response object from the data well for
  // faster processing. Also set the static cache.
  $opensearch_static_fast[$cid] = $response;
  if ($ttl = variable_get('opensearch_cache_lifetime', OPENSEARCH_DEFAULT_CACHE_LIFETIME)) {
    cache_set($cid, $response, 'cache_opensearch', REQUEST_TIME + $ttl);
  }
}

/**
 * Build cache id for this request.
 *
 * The whole object it serialized to ensure that the request type is part of the
 * cache key. This may lead to the same results being cached more than once, but
 * doing this way simplifies the code and the overhead is minimal.
 *
 * @param TingClientRequest $request
 *   The request that should be used to build the cache id.
 *
 * @return string
 *   The cache id.
 */
function _opensearch_cache_id(TingClientRequest $request) {
  $cid = md5(serialize($request));
  drupal_alter('opensearch_cache_key', $cid, $request);

  return $cid;
}

/**
 * Retrieves an initialized Ting client.
 *
 * The client returned is with appropriate request adapter and logger.
 *
 * @return TingClient
 *   The ting client object that can be used to communicate with the data well.
 */
function _opensearch_get_client() {
  static $client;

  if (!isset($client)) {
    $logger = (variable_get('opensearch_enable_logging', FALSE)) ? new TingClientDrupalWatchDogLogger() : new TingClientVoidLogger();
    $client = new TingClient(new TingClientRequestAdapter(), $logger);
  }

  return $client;
}
