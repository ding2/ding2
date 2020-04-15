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

    return ($collection || is_null($result)) ? $result : $result[$object_id];
  }

  return NULL;
}

/**
 * Get a bunch of objects in one request.
 *
 * @param string[] $ids
 *   Data-well PIDs for the objects to get.
 * @param bool $local
 *   Flag to indicate whether $ids contains pids or local ids (fausts).
 *
 * @return bool|\TingClientSearchResult
 *   The objects fetched from the data-well.
 *
 * @throws \TingClientException
 *   This may throw this exception if the search request fails.
 */
function opensearch_get_objects(array $ids, $local = FALSE) {
  $request = opensearch_get_request_factory()->getObjectRequest();

  // Set agency from the administration interface.
  if ($agency = variable_get('ting_agency', FALSE)) {
    $request->setAgency($agency);
  }

  // Set search profile from the administration interface.
  $profile = variable_get('opensearch_search_profile', '');
  if (!empty($profile)) {
    $request->setProfile($profile);
  }

  // Opensearch getObject complains if it has to return more than 200 records,
  // with the message 'getObject can fetch up to 200 records. '. But it seems
  // it also have trouble fething over 169 records, which appears to be a bug.
  // In any case, we should be safe, if we only fetch 100 records a time.
  // See: https://platform.dandigbib.org/issues/3828#note-16.
  $objects = [];
  foreach (array_chunk($ids, 100) as $chunk) {
    if ($local) {
      $request->setLocalIds($chunk);
    }
    else {
      $request->setObjectIds($chunk);
    }
    $result = opensearch_execute($request);
    if (is_array($result)) {
      $objects += $result;
    }
  }

  return $objects;
}

/**
 * Performs a search against the well.
 *
 * @param string $query
 *   The search query.
 * @param int $page
 *   The page number to retrieve search results for.
 * @param int $results_per_page
 *   The number of results to include per page.
 * @param array $options
 *   Options to pass to the search. Possible options are:
 *    - facets: Array of facet names for which to return results. Default:
 *      facet.subject, facet.creator, facet.type, facet.date, facet.language.
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
 *    - filterLocalHoldings: Whether to filter with local agency-id.
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

  if (isset($options['filterLocalHoldings'])) {
    $request->setFilterLocalHoldings($options['filterLocalHoldings']);
  }

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
 * Get ting objects from the well in marcxchange format.
 *
 * @param array $object_ids
 *   Object identifiers.
 *
 * @return array
 *   An array of TingMarchResult objects. Empty array if nothing was found.
 *
 * @throws \TingClientException
 *   This may throw this exception if the search request fails.
 */
function opensearch_get_objects_marcxchange(array $object_ids) {
  $request = opensearch_get_request_factory()->getMarcXchangeRequest();

  $request->setAgency(variable_get('ting_agency'));
  $request->setProfile(variable_get('opensearch_search_profile'));
  $request->setIdentifier($object_ids);

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
 * @return \TingClientSearchResult|\TingClientObjectCollection|array|bool|null
 *   Result of the request or false if an error occurs.
 *   If $request is a TingClientSearchRequest a TingClientSearchResult result
 *   object is returned.
 *   If $request is a TingClientCollectionRequest a TingClientObjectCollection
 *   result object is returned.
 *   If $request is a TingClientObjectRequest an array of TingClientObject
 *   result objects is returned or NULL if nothing was found.
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

  if ($response = _opensearch_cache($request)) {
    // Exact match for request is found in cache. Return early.
    return $response;
  }

  // If we are retrieving multiple objects then there might not be a single
  // request for all these objects combined in the cache but they might be
  // cached individually.
  $cached_objects = [];
  $original_object_ids = [];
  $original_local_ids = [];
  if ($request instanceof TingClientObjectRequest) {
    $object_ids = !empty($request->getObjectIds()) ? $request->getObjectIds() : array();
    $local_ids = !empty($request->getLocalIds()) ? $request->getLocalIds() : array();

    // Store the original object_ids and local_ids identifier arrays, so that we
    // can reconstruct the original request later on when genrating cache key
    // for the response.
    if ($object_ids) {
      $original_object_ids = $request->getObjectIds();
    }
    if ($local_ids) {
      $original_local_ids = $request->getLocalIds();
    }

    // Build maps of singular requests for objects by id or local id.
    $object_ids = array_combine($object_ids, $object_ids);
    $object_id_requests = array_map(function($id) use ($request) {
      $object_request = clone $request;
      $object_request->setObjectId($id);
      return $object_request;
    }, $object_ids);

    $local_ids = array_combine($local_ids, $local_ids);
    $local_id_requests = array_map(function($id) use ($request) {
      $object_request = clone $request;
      $object_request->setLocalId($id);
      return $object_request;
    }, $local_ids);

    // Try to retrieve a cached response for each request. Entries which does
    // not have cached data will get the value FALSE for easy subsequent
    // filtering.
    $object_ids = array_map(function ($object_request) {
      if ($cached_response = _opensearch_cache($object_request)) {
        // A response for a single object is an array with a single object so
        // just return the object.
        return array_shift($cached_response);
      }
      else {
        return FALSE;
      }
    }, $object_id_requests);
    $cached_object_ids = array_filter($object_ids);

    $local_ids = array_map(function ($object_request) {
      if ($cached_response = _opensearch_cache($object_request)) {
        // A response for a single object is an array with a single object so
        // just return the object.
        return array_shift($cached_response);
      }
      else {
        return FALSE;
      }
    }, $local_id_requests);
    $cached_local_ids = array_filter($local_ids);

    // Ids that we still need to be fetched will not be appearing in the lists
    // of cached objects.
    $uncached_object_ids = array_diff_key($object_ids, $cached_object_ids);
    if (!empty($uncached_object_ids)) {
      $request->setObjectIds(array_keys($uncached_object_ids));
    }
    $uncached_local_ids = array_diff_key($local_ids, $cached_local_ids);
    if (!empty($uncached_local_ids)) {
      $request->setLocalIds(array_keys($uncached_local_ids));
    }

    // The $cached_local_ids array is now keyed by local id and we needed that
    // to get the uncached local ids. But in the response all objects should be
    // keyed PID, so here we convert the array of cached "local" objects to be
    // keyed by their PID.
    $local_object_pids = [];
    foreach ($cached_local_ids as $object) {
      $local_object_pids[] = $object->id;
    }
    $cached_local_ids = array_combine($local_object_pids, $cached_local_ids);

    $cached_objects = $cached_object_ids + $cached_local_ids;

    // If there are no ids to fetch then there is no need to issue a request.
    // Just return the array of cached objects.
    if (empty($uncached_object_ids) && empty($uncached_local_ids)) {
      _opensearch_cache($request, $cached_objects);
      return $cached_objects;
    }
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

    // Merge any cached objecst that we found earlier with the result from the
    // request. Note that we do this after invoking post_execute, since the
    // $response and $res need to correspond.
    if ($request instanceof TingClientObjectRequest) {
      // The map uses ids as keys. Order does not matter for object requests.
      $response = array_merge($cached_objects, $response);

      // Restore the original ids on the request so that our generated cache id
      // will point to the correct response.
      if ($original_object_ids) {
        $request->setObjectIds($original_object_ids);
      }
      if ($original_local_ids) {
        $request->setLocalIds($original_local_ids);
      }

      // If response is empty array it means there was no objects found for the
      // passed ids. In this case we need to return NULL as expected by the
      // caller.
      if (empty($response)) {
        $response = NULL;
      }
    }

    // Update the cache with the raw response object from the data well for
    // faster processing. Also set the static cache.
    _opensearch_cache($request, $response);

    // To speed up the entity module, which will trigger an search for each
    // collection. Try and predict the search request an warm up the cache.
    // Alternative rewrite the whole ting entity module, which currently is
    // overkill.
    if ($response instanceof TingClientSearchResult) {
      _opensearch_predict_cache($response->collections, $request);
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
 * @param TingClientRequest $request
 *   The request used to get the collections.
 *
 * @throws \TingClientException
 *   If the search client request fails.
 */
function _opensearch_predict_cache(array $collections, TingClientRequest $request) {
  foreach ($collections as $collection) {
    foreach ($collection->objects as $object) {
      if (!is_object($object)) {
        watchdog('opensearch', 'Predict cache found collection with empty objects. Search query: @query', array('@query' => $request->getQuery()), WATCHDOG_WARNING);
        break;
      }

      $collection_request = opensearch_get_request_factory()->getCollectionRequest();
      $collection_request->setAllObjects(FALSE);
      $collection_request->setObjectId($object->id);
      $collection_request->setQuery('*:*');

      // See opensearch_execute() for description of always getting all
      // relations.
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
      _opensearch_cache($collection_request, $collection_response);

      // Create cache entry for the object as well.
      $object_request = opensearch_get_request_factory()->getObjectRequest();

      // See opensearch_execute() for description of always getting all
      // relations.
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

      // Build both requests for local id and PID.
      $object_id_request = clone $object_request;
      $object_id_request->setObjectId($object->id);
      $local_id_request = clone $object_request;
      $local_id_request->setLocalId($object->localId);

      // Build the response that matches the request and put it into cache.
      array_map(function (TingClientObjectRequest $object_request) use ($object) {
        $params = module_invoke_all('opensearch_pre_execute', $object_request);
        if (!empty($params)) {
          $object_request->setParameters($params);
        }
        $object_response = array();
        $object_response[$object->id] = clone $object;
        _opensearch_cache($object_request, $object_response);
      }, [$object_id_request, $local_id_request]);
    }
  }
}

/**
 * Cache/retrieve from cache a search response based on a request.
 *
 * @param TingClientRequest $request
 *   The search request for which to set/retrieve a cached response.
 * @param \TingClientSearchResult|\TingClientObjectCollection|\TingClientObject[]|NULL $response
 *   The response to cache. NULL to reset the cache entry for the request.
 *
 * @return \TingClientSearchResult|\TingClientObjectCollection|\TingClientObject[]|NULL
 *   The cached response. NULL if no cached entry exists.
 */
function _opensearch_cache(TingClientRequest $request, $response = NULL) {
  static $static_cache = array();
  $cid = _opensearch_cache_id($request);

  // Count the number of arguments to determine if $value has been provided.
  // This allows us to distinguish between situations where $value is not set
  // and we want to retrieve the cache value and where $value is set to NULL
  // explicitly.
  if (func_num_args() == 2) {
    // Update the cache with the provided value. If you here just assign the
    // response to the static variable here even though it's deep clone in the
    // return statement changes to the collections inside the object from
    // outside this function changes the cached object.
    $static_cache[$cid] = _opensearch_deep_clone($response);
    if ($ttl = variable_get('opensearch_cache_lifetime', OPENSEARCH_DEFAULT_CACHE_LIFETIME)) {
      cache_set($cid, $response, 'cache_opensearch', REQUEST_TIME + $ttl);
    }

    return _opensearch_deep_clone($response);
  }
  else {
    // Try to retrieve value from static cache.
    if (array_key_exists($cid, $static_cache)) {
      $data = $static_cache[$cid];

      return _opensearch_deep_clone($data);
    }

    $cache = cache_get($cid, 'cache_opensearch');
    if ($cache && ($cache->expire > REQUEST_TIME)) {
      $data = $cache->data;

      // Update the static cache with the database cache content to speed up the
      // next request for the same data.
      $static_cache[$cid] = _opensearch_deep_clone($data);

      return _opensearch_deep_clone($data);
    }
  }
}

/**
 * Deep clone data structure using serialization.
 *
 * This should be use when working with static cache data that contains objects
 * or objects in arrays. We need to do a deep clone so changes to objects
 * out-side the cache will not change the objects in the static cache.
 *
 * @param mixed $data
 *   Data structure to clone.
 *
 * @return mixed
 *   Clone off the inputted data structure.
 */
function _opensearch_deep_clone($data) {
  return unserialize(serialize($data));
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
