<?php
/**
 * @file
 * Wrapper functions for Ting client.
 */

/**
 * Used to indicate that a given cache entry have return no reply from the data
 * well.
 */
define('TING_CACHE_EMPTY_ENTRY', '8e4f3ef1784c020bf7afa5b6dd69b421');

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
 * @todo Should use getObject, but the ting-client lib doesn't implement that.
 *
 * @return TingClientObject
 *   Ting object.
 */
function ting_get_object($object_id, $collection = FALSE, $with_relations = FALSE) {
  if (!empty($object_id)) {
    // Check the cache first.
    $type = TING_CACHE_TING_OBJECT;
    $cache_key = $object_id;
    if ($collection) {
      $type = TING_CACHE_COLLECTION;
      $cache_key = ting_cache_collection_key($object_id);
    }
    $object = ting_cache_get($cache_key, $type, $with_relations);
    if ($object != TING_CACHE_EMPTY_ENTRY && !$object) {
      // Put a negative reply in the cache. It will be overwritten by the
      // object, or ensure that we won't try to fetch this id again.
      ting_cache_set($object_id, TING_CACHE_EMPTY_ENTRY, $type);

      // Build request request and set object id.
      $request = ting_get_request_factory()->getObjectRequest();
      if ($collection) {
        // If this is a collection we need to do a collection request, which is
        // a search request.
        $request = ting_get_request_factory()->getCollectionRequest();
        $request->setAllObjects(FALSE);
      }
      $request->setObjectId($object_id);

      // Set agency from the administration interface.
      if ($agency = variable_get('ting_agency', FALSE)) {
        $request->setAgency($agency);
      }

      // Set search profile from the administration interface.
      $profile = variable_get('ting_search_profile', '');
      if (!empty($profile) && method_exists($request, 'setProfile')) {
        $request->setProfile($profile);
      }

      // Get all relations for the object.
      if ($with_relations) {
        $request->setAllRelations(TRUE);
        $request->setRelationData('full');
      }

      // Execute the request.
      $object = ting_execute_cache($request);

      // If this was a collection request store the collection reply to ensure
      // that there is no empty cache entry.
      if ($collection) {
        if (is_null($object)) {
          $object = TING_CACHE_EMPTY_ENTRY;
        }
        ting_cache_set($object_id, $object, $type);
      }
    }

    // If not asking for a collection, and the object is, return the
    // sub-object with the same id.
    if (!$collection && isset($object->objects)) {
      foreach ($object->objects as $sub_object) {
        if ($sub_object->id == $object_id) {
          // If not asking for a collection, and the object is, return the
          // sub-object with the same id.
          _ting_cache_update_relations_status($sub_object, $with_relations);
          return $sub_object;
        }
      }
      // No sub-object had the same id. Somethings broken.
      return NULL;
    }

    // Mark the object in cache as relations have been loaded.
    if (!$collection) {
      _ting_cache_update_relations_status($object, $with_relations);
    }

    // If not asking for a collection, and the object is, return the
    // sub-object with the same id.
    if ($object == TING_CACHE_EMPTY_ENTRY) {
      return NULL;
    }

    return $object;
  }

  return NULL;
}

/**
 * Get a bunch of objects in one request.
 *
 * @todo Should use getObject when getObject supports getting multiple.
 */
function ting_get_objects($ids) {
  $objects = array();
  // Pre-fill from cache.
  foreach ($ids as $id) {
    $objects[$id] = ting_cache_get($id, TING_CACHE_TING_OBJECT);
    if (isset($objects[$id]) && isset($objects[$id]->objects)) {
      foreach ($objects[$id]->objects as $sub_object) {
        if ($sub_object->id == $id) {
          $objects[$id] = $sub_object;
          continue 2;
        }
      }
      // No sub-object had the same id. Somethings broken.
      $objects[$id] = NULL;
    }

    if ($objects[$id] == TING_CACHE_EMPTY_ENTRY) {
      $objects[$id] = NULL;
    }
  }

  // Not all object are searchable, such as relation etc. So to get over this we
  // split the request into to groups "own id's" and "others". Where the first
  // is ensured to be searchable.
  $agency = variable_get('ting_agency', FALSE);
  $query = array();
  foreach ($objects as $id => $object) {
    if ($object === FALSE) {
      // So if the agency match lets search theme as that's faster then fetching
      // them one by one.
      if (preg_match('/^(870970-basis|' . $agency . '-katalog|' . $agency . ')/', $id)) {
        $query[] = 'rec.id=' . $id;
      }
      else {
        // Get objects as it was not local.
        $objects[$id] = ting_get_object($id);
      }
    }
  }
  // Open search is limited to 50 results per call, so iterate until all results
  // have been fetched. It has a limit on the size of the query (>187 rec.id=
  // ORed together seems to break it).
  $query_chunks = array_chunk($query, 50);
  foreach ($query_chunks as $query_chunk) {
    $request = ting_get_request_factory()->getSearchRequest();
    if ($agency) {
      $request->setAgency($agency);
    }
    $profile = variable_get('ting_search_profile', '');
    if (!empty($profile) && method_exists($request, 'setProfile')) {
      $request->setProfile($profile);
    }
    $request->setQuery(implode(' OR ', $query_chunk));
    $request->setStart(1);
    $request->setNumResults(50);
    $request->setAllObjects(TRUE);

    $result = ting_execute_cache($request);

    if ($result && is_array($result->collections)) {
      foreach ($result->collections as $collection) {
        if (is_array($collection->objects) && count($collection->objects)) {
          foreach ($collection->objects as $object) {
            $objects[$object->id] = $object;
          }
        }
      }
    }
  }

  return $objects;
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
 *    - enrich: Whether to include additional information and cover images with
 *      each object. Default: false
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
 */
function ting_do_search($query, $page = 1, $results_per_page = 10, $options = array()) {
  $request = ting_get_request_factory()->getSearchRequest();

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
  else{
    $sort = variable_get('ting_sort_default', 'rank_frequency');
    $request->setSort($sort);
  }

  if (isset($options['collectionType'])) {
    $request->setCollectionType($options['collectionType']);
  }
  $request->setAllObjects(isset($options['allObjects']) ? $options['allObjects'] : FALSE);

  // Set search profile, if applicable.
  $profile = variable_get('ting_search_profile', '');
  if (!empty($profile) && method_exists($request, 'setProfile')) {
    $request->setProfile($profile);
  }

  // Apply custom ranking if enabled.
  if (variable_get('ting_ranking_custom', FALSE) && variable_get('ting_ranking_fields', array()) && !isset($options['sort'])) {
    $fields = array();
    foreach (variable_get('ting_ranking_fields', array()) as $field) {
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
  $boosts = variable_get('ting_boost_fields', array());

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

  $search_result = ting_execute_cache($request);
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
 */
function ting_get_object_marcxchange($object_id) {
  $cache_key = 'marcxchange:' . $object_id;
  $object = ting_cache_get($cache_key, TING_CACHE_TING_OBJECT, FALSE);

  if ($object != TING_CACHE_EMPTY_ENTRY && !$object) {
    ting_cache_set($cache_key, TING_CACHE_EMPTY_ENTRY, TING_CACHE_TING_OBJECT);

    $request = ting_get_request_factory()->getMarcXchangeRequest();

    $request->setAgency(variable_get('ting_agency'));
    $request->setProfile(variable_get('ting_search_profile'));
    $request->setIdentifier($object_id);

    // Have to use ting_execute directly since marc objects might collide with
    // normal dkabm objects in the cache.
    $object = ting_execute($request);
    if ($object) {
      ting_cache_set($cache_key, $object, TING_CACHE_TING_OBJECT);
    }
  }

  return $object;
}

/**
 * Calls ting_execute() and caches the result.
 *
 * Executes the request and caches sub-objects.
 *
 * @param object $request
 *   The request.
 *
 * @return object
 *   The search reply from the data well.
 */
function ting_execute_cache($request) {
  $parms = $request->getRequest()->getParameters();

  // Handle fulltext vs. dkabm caching of object.
  $type = TING_CACHE_TING_OBJECT;
  if ($parms['format'] == 'docbook') {
    $type = TING_CACHE_TING_OBJECT_FULLTEXT;
  }

  // User static cache to store request, used in another function to see if the
  // same request is made more than once.
  $calls = &drupal_static(__FUNCTION__);
  if (!isset($calls)) {
    $calls = array();
  }
  $calls[] = $parms;

  // Check if the reply have been stored in cache.
  $reply = ting_cache_get(md5(serialize($parms)), TING_CACHE_REPLY);

  if (!$reply) {
    // Reply for the request was not found, so we have to ask the data well.
    $reply = ting_execute($request);

    // Cache any sub-objects (mostly true for collections).
    if (isset($reply->objects)) {
      foreach ($reply->objects as $object) {
        ting_cache_set($object->id, $object, TING_CACHE_TING_OBJECT);
        // Cache any relations.
        if (isset($object->relations)) {
          foreach ($object->relations as $relation) {
            if (isset($relation->id)) {
              ting_cache_set($relation->id, $relation);
            }
          }
        }
      }
    }

    // Cache any collections. Done after objects to ensure that collections take
    // precedence.
    if (isset($reply->collections)) {
      foreach ($reply->collections as &$collection) {
        if (is_array($collection->objects)) {
          foreach ($collection->objects as $object) {
            // Cache any relations.
            if (isset($object->relations)) {
              foreach ($object->relations as $relation) {
                if (isset($relation->id)) {
                  ting_cache_set($relation->id, $relation);
                }
              }
            }
            ting_cache_set($object->id, $object, $type);
          }
          ting_cache_set(ting_cache_collection_key($collection->objects[0]->id), $collection, TING_CACHE_COLLECTION);
        }
      }
    }

    // Cache any relations.
    if (isset($reply->relations)) {
      foreach ($reply->relations as $relation) {
        ting_cache_set($relation->id, $relation, TING_CACHE_TING_OBJECT);
      }
    }

    // Cache the object self.
    if ($reply instanceof TingClientObject) {
      if (!empty($reply->record)) {
        ting_cache_set($reply->id, $reply);
      }
      else {
        $reply = TING_CACHE_EMPTY_ENTRY;
      }
    }

    // Store the reply for the request itself in the cache.
    if (is_null($reply)) {
      // Handle empty data well replies.
      $reply = TING_CACHE_EMPTY_ENTRY;
    }
    ting_cache_set(md5(serialize($parms)), $reply, TING_CACHE_REPLY);
  }

  if ($reply == TING_CACHE_EMPTY_ENTRY) {
    return NULL;
  }

  return $reply;
}

/**
 * Get cached version of a data well search.
 *
 * The cache can lookup ting objects, ting collections or even a replay from
 * the data well.
 *
 * To retrieve an reply simple extract the params from the request object,
 * serialize them and make a MD5 hash as id.
 *
 * @see ting_execute_cache()
 *
 * @param string $id
 *   Object id or the MD5 hash of the parameters used to execute a search
 *   against the date well.
 * @param string $type
 *   The type of data to cache, which is used to set the cache id. It should be
 *   one off: TING_CACHE_TING_OBJECT, TING_CACHE_COLLECTION,
 *   TING_CACHE_TING_OBJECT_FULLTEXT or TING_CACHE_REPLY.
 * @param bool $with_relations
 *   Is the object we are looking up with relations (addi posts).
 *
 * @return mixed
 *   The cached item based on the $type and $id given. If non found in the cache
 *   NULL is returned.
 */
function ting_cache_get($id, $type = TING_CACHE_TING_OBJECT, $with_relations = FALSE) {
  $cid = $type . ':' . $id;

  if ($ttl = variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME)) {
    $cache = cache_get($cid, 'cache_ting');
    if ($cache && ($cache->expire > REQUEST_TIME)) {
      $data = $cache->data;
      // Check if cached version has relations, if request. If it's an empty
      // array it have not been request by the server yet with relations, so
      // return FALSE to trigger a data well request.
      if ($with_relations && (isset($data->relations) && is_array($data->relations) && !count($data->relations))) {
        return FALSE;
      }

      // The data maybe NULL which means that the data well have been asked
      // about this object and no where found.
      return $data;
    }
  }
  return FALSE;
}

/**
 * Store cached version of a data well search.
 *
 * The cache can store ting objects, ting collections or even a replay from
 * the data well.
 *
 * To store an reply simple extract the params from the request object,
 * serialize them and make a MD5 hash as id.
 *
 * @see ting_execute_cache()
 *
 * @param string $id
 *   Id that the item was cached under.
 * @param mixed $value
 *   The value to store in the cache.
 * @param string $type
 *   The type of data to cache, which is used to set the cache id. It should be
 *   one off: TING_CACHE_TING_OBJECT, TING_CACHE_COLLECTION,
 *   TING_CACHE_TING_OBJECT_FULLTEXT or TING_CACHE_REPLY.
 */
function ting_cache_set($id, $value, $type = TING_CACHE_TING_OBJECT) {
  // Define the cache id.
  $cid = $type . ':' . $id;

  if ($ttl = variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME)) {
    cache_set($cid, $value, 'cache_ting', REQUEST_TIME + $ttl);
  }
  else {
    // Without proper caching, use a static cache that only works on pr.
    // request.
    $cache = &drupal_static(__FUNCTION__);
    if (!isset($cache)) {
      $cache = array();
    }
    $cache[$cid] = $value;
  }
}

/**
 * Generates a cache id (cid) for ting collection cache.
 *
 * Collections have to be indexed in cache based on the facets selected as the
 * collections changes content based on facets. This is all due to the fact that
 * collections don't have unique id's. In fact we use the first object's id in
 * the collection to id the collection.
 *
 * @param string $object_id
 *   Ting object ID also known as PID.
 *
 * @return string
 *   Cache key to retrieve and set data in the cache,
 */
function ting_cache_collection_key($object_id) {
  $cache_key = $object_id;
  if (!empty($_GET['facets'])) {
    $cache_key .= ':' . md5(serialize($_GET['facets']));
  }

  return $cache_key;
}

/**
 * Mark the object in the cache as having no relations in the data well.
 *
 * This is need as object may have been cached without relations in a search
 * request, but a get_object request may ask for the same object from cache with
 * relations. So this FALSE value is used to ensure that the data well is only
 * asked once for a object with relations even, if it do not have relations.
 *
 * Default value from the data well is an empty array, so if the array is empty
 * the ting_cache_set, function will not return the cached if relations are
 * requested.
 *
 * @param StdClass $object
 *   Ting data well object.
 * @param bool $with_relations
 *   If TRUE relations will be marked.
 */
function _ting_cache_update_relations_status($object, $with_relations = FALSE) {
  if ($with_relations && $object instanceof TingClientObject) {
    if (empty($object->relations)) {
      // Mark this object as having no relations.
      $object->relations = FALSE;
    }

    // Update cache with the object.
    ting_cache_set($object->id, $object);
  }
}

/**
 * Get recommendations for a given ISBN.
 *
 * @param string $isbn
 *   ISBN number to get recommendations from.
 * @param int $num_results
 *   The number of results to return.
 *
 * @return array
 *   An array of TingClientObjectRecommendation objects.
 */
function ting_get_object_recommendations($isbn, $num_results = 10) {
  $request = ting_get_request_factory()->getObjectRecommendationRequest();
  $request->setIsbn($isbn);
  $request->setNumResults($num_results);
  return ting_execute($request);
}

/**
 * Retrieves an initialized Ting client request factory.
 *
 * @throws TingClientException
 *   If there is no end-point url defined in the configuration this exception is
 *   thrown.
 *
 * @return TingClientRequestFactory
 *   TingClientRequestFactory object.
 */
function ting_get_request_factory() {
  static $request_factory;

  if (!isset($request_factory)) {
    $url_variables = array(
      'search' => 'ting_search_url',
      'object' => 'ting_search_url',
      'collection' => 'ting_search_url',
      'recommendation' => 'ting_recommendation_url',
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
    if (variable_get('ting_use_auth', FALSE)) {
      $auth = array(
        'name' => variable_get('ting_auth_name', ''),
        'pass' => variable_get('ting_auth_pass', ''),
        'group' => variable_get('ting_auth_group', ''),
      );
    }

    $request_factory = new TingClientRequestFactory($urls, $auth);
  }

  return $request_factory;
}

/**
 * Add relation type to a search request object.
 *
 * @param TingClientSearchRequest $request
 *   The search request to add the relation to.
 * @param string $type
 *   The type of relation add to the request.
 *
 * @return TingClientSearchRequest
 *   The request added the relation.
 */
function ting_add_relations($request, $type = 'full') {
  $request->setAllRelations(TRUE);
  $request->setRelationData($type);
  return $request;
}

/**
 * Perform a request against Ting and perform error handling if necessary.
 *
 * @param object $request
 *   The request.
 *
 * @return mixed
 *   Result of the request or false if an error occurs.
 */
function ting_execute($request) {
  // Get additional parameters from other modules.
  $params = module_invoke_all('ting_pre_execute', $request);
  if (!empty($params)) {
    $request->setParameters($params);
  }

  try {
    timer_start('ting');
    $res = ting_get_client()->execute($request);
    timer_stop('ting');

    // When the request is for fulltext (doc-book) the result is XML but the
    // next part expect JSON only formatted input. So this hack simply return
    // the XML for now as later on we have to work with open format and XML
    // parsing. So for now simply return the result to fulltext.
    if ($request instanceof TingClientObjectRequest && $request->getOutputType() == 'xml' && $request->getFormat() == 'docbook') {
      return $res;
    }

    $response = $request->parseResponse($res);

    // Pass parsed results to other modules.
    // @todo Check if it works for collection of items.
    $props = module_invoke_all('ting_post_execute', $request, $response, $res);
    if (!empty($props)) {
      foreach ($props as $property => $value) {
        $response->{$property} = $value;
      }
    }

    return $response;
  }
  catch (TingClientException $e) {
    if (isset($e->user_message)) {
      drupal_set_message($e->user_message, 'warning');
    }
    timer_stop('ting');
    watchdog('ting client', 'Error performing request: ' . $e->getMessage(), NULL, WATCHDOG_ERROR, 'http://' . $_SERVER["HTTP_HOST"] . request_uri());
    return FALSE;
  }
}

/**
 * Retrieves an initialized Ting client.
 *
 * The client returned is with appropriate request adapter and logger.
 *
 * @return TingClient
 *   The ting client object that can be used to communicate with the data well.
 */
function ting_get_client() {
  static $client;

  if (!isset($client)) {
    $logger = (variable_get('ting_enable_logging', FALSE)) ? new TingClientDrupalWatchDogLogger(ting_get_request_factory()) : new TingClientVoidLogger();
    $client = new TingClient(new TingClientRequestAdapter(), $logger);
  }

  return $client;
}
