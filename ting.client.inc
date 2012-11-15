<?php
/**
 * @file
 * Wrapper functions for Ting client.
 */


function ting_get_object_request($object_id) {
  $request = ting_get_request_factory()->getObjectRequest();
  if ($agency = variable_get('ting_agency', FALSE)) {
    $request->setAgency($agency);
  }
  $request->setObjectId($object_id);
  $request->setAllRelations(TRUE);
  $request->setRelationData('full');

  // Set search profile, if applicable.
  $profile = variable_get('ting_search_profile', '');
  if (!empty($profile) && method_exists($request, 'setProfile')) {
    $request->setProfile($profile);
  }

  $object = ting_execute_cache($request);

  return $object;
}

/**
 * Get an ting object or collection.
 *
 * Returns the search response for the given id. This will cache the
 * result, and any sub-objects, so fetching objects from a recently
 * fetched collection won't trigger another backend request.
 *
 * @param $object_id The id to fetch.
 * @param $collection Whether to return a collection, if possible, or
 *   an object.
 *
 * @todo Should use getObject, but the ting-client lib doesn't implement that.
 */
function ting_get_object($object_id, $collection = FALSE) {
  if (empty($object_id)) {
    return FALSE;
  }

  // Check the cache first.
  $object = ting_cache_get($object_id, $collection);
  if (!$object) {
    // Put a negative reply in the cache. It will be overwritten by the
    // object, or ensure that we won't try to fetch this id again.
    ting_cache_set($object_id, NULL);

    if (!$object) {
      $request = ting_get_request_factory()->getCollectionRequest();
      $request->setObjectId($object_id);
      if ($agency = variable_get('ting_agency', FALSE)) {
        $request->setAgency($agency);
      }

      $profile = variable_get('ting_search_profile', '');
      if (!empty($profile) && method_exists($request, 'setProfile')) {
	$request->setProfile($profile);
      }

      $request->setAllObjects(false);
      $object = ting_execute_cache($request);
    }
  }

  // If not asking for a collection, and the object is, return the
  // sub-object with the same id.
  if (!$collection && isset($object->objects)) {
    foreach ($object->objects as $sub_object) {
      if ($sub_object->id == $object_id) {
        return $sub_object;
      }
    }
    // No sub-object had the same id. Somethings broken.
    return NULL;
  }
  return $object;
}

/**
 * Get a bunch of objects in one request.
 *
 * @todo Should use getObject when getObject supports getting multiple.
 */
function ting_get_objects($ids) {
  $objects = array();
  // Prefill from cache.
  foreach ($ids as $id) {
    $objects[$id] = ting_cache_get($id);
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
  }

  $query = array();
  foreach ($objects as $id => $object) {
    if (!isset($object)) {
      $query[] = 'rec.id=' . $id;
    }
  }
  if (sizeof($query)) {
    $request = ting_get_request_factory()->getSearchRequest();

    if ($agency = variable_get('ting_agency', FALSE)) {
      $request->setAgency($agency);
    }

    $profile = variable_get('ting_search_profile', '');
    if (!empty($profile) && method_exists($request, 'setProfile')) {
      $request->setProfile($profile);
    }

    $request->setQuery(join(' OR ', $query));
    $request->setStart(1);
    $request->setNumResults(1000);
    $request->setAllObjects(TRUE);

    $result = ting_execute_cache($request);

    if ($result && is_array($result->collections)) {
      foreach ($result->collections as $collection) {
        if (is_array($collection->objects) && sizeof($collection->objects)) {
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
 * Performs a search agains the well
 *
 * @param string $query
 *    The search query
 * @param int $page
 *    The page number to retrieve search results for
 * @param int $results_per_page
 *    The number of results to include per page
 * @param array $options
 *    Options to pass to the search. Possible options are:
 *    - facets: Array of facet names for which to return results. Default: facet.subject, facet.creator, facet.type, facet.date, facet.language
 *    - numFacets: The number of terms to include with each facet. Default: 10
 *    - enrich: Whether to include additional information and cover images with each object. Default: false
 *    - sort: The key to sort the results by. Default: "" (corresponds to relevance). The possible values are defined by the sortType type in the XSD.
 *    - rank: The ranking type, as defined in the XSD.
 *    - supportingTypes: Whether to include supporting types such as reviews. Default: false
 *    - reply_only: Don't change the result objects to TingCollection objects.
 * @return TingClientSearchResult
 *    The search result
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

  $request->setFacets((isset($options['facets'])) ? $options['facets'] : array('facet.subject', 'facet.creator', 'facet.type', 'facet.category', 'facet.language', 'facet.date', 'facet.acSource'));
  $request->setNumFacets((isset($options['numFacets'])) ? $options['numFacets'] : ((sizeof($request->getFacets()) == 0) ? 0 : 10));
  if (isset($options['sort']) && $options['sort']) {
    $request->setSort($options['sort']);
  }
  $request->setAllObjects(isset($options['allObjects']) ? $options['allObjects'] : FALSE);

  // Set search profile, if applicable.
  $profile = variable_get('ting_search_profile', '');
  if (!empty($profile) && method_exists($request, 'setProfile')) {
    $request->setProfile($profile);
  }

  // Apply custom ranking if enabled.
  if (variable_get('ting_ranking_custom', FALSE)) {
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
        'fieldName' => 'cql.anyIndexes',
        'fieldType' => 'phrase',
        'weight' => 1,
      );

      $fields[] = array(
        'fieldName' => 'cql.anyIndexes',
        'fieldType' => 'word',
        'weight' => 1,
      );

      $request->userDefinedRanking = array('tieValue' => 0.1, 'rankField' => $fields);
    }
  }
  // Otherwise, use the ranking setting.
  else {
    $request->setRank((isset($options['rank']) && $options['rank']) ? $options['rank'] : 'rank_general');
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
    $request->userDefinedBoost = array('boostField' => $uboosts);
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
 * Calls ting_execute() and caches the result.
 *
 * Executes the request and caches sub-objects.
 *
 * @param $request the request.
 */
function ting_execute_cache($request) {
  $calls = &drupal_static(__FUNCTION__);
  if (!isset($calls)) {
    $calls = array();
  }
  $calls[] = $request->getRequest()->getParameters();
  $reply = ting_execute($request);

  // Cache any sub-objects (mostly true for collections).
  if (isset($reply->objects)) {
    foreach ($reply->objects as $object) {
      ting_cache_set($object->id, $object);
      // Cache any relations.
      if (isset($object->relations)) {
        foreach ($object->relations as $relation) {
          if (isset($relation->id)) {
            ting_cache_set($relation->id, $relation);
          }
        }
      }
    }
    // Cache the reply as the first object's id. This is for collections.
    if (!isset($reply->id) and isset($reply->objects[0])) {
      ting_cache_set($reply->objects[0]->id, $reply);
    }
  }

  // Cache any collections. Done after objects to ensure that collections take
  // precedence.
  if (isset($reply->collections)) {
    foreach ($reply->collections as &$collection) {
      if (isset($collection->objects[0])) {
        foreach ($collection->objects as $object) {
          // Cache any relations.
          if (isset($object->relations)) {
            foreach ($object->relations as $relation) {
              if (isset($relation->id)) {
                ting_cache_set($relation->id, $relation);
              }
            }
          }
          ting_cache_set($object->id, $object);
        }

        ting_cache_set($collection->objects[0]->id, $collection);
      }
    }
  }

  // Cache any relations.
  if (isset($reply->relations)) {
    foreach ($reply->relations as $object) {
      ting_cache_set($object->id, $object);
    }
  }

  // Lastly cache the reply itself if it has an id.
  if (isset($reply->id)) {
    ting_cache_set($reply->id, $reply);
  }

  return $reply;
}

/**
 * Get item from static cache.
 */
function ting_cache_get($id, $collection = FALSE) {
  $cid = 'ting-' . ($collection ? 'collection' : 'object') . ':' . $id;
  if ($ttl = variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME)) {
    $cache = cache_get($cid);
    if ($cache && ($cache->expire > REQUEST_TIME)) {
      return $cache->data;
    }
    return NULL;
  }
  else {
    // Without proper caching, use a request cache.
    $cache = &drupal_static('ting_cache_set');
    if (!isset($cache)) {
      $cache = array();
    }
    // Using array_key_exists, as we might contain NULL values (which is !isset()).
    if (array_key_exists($cid, $cache)) {
      return $cache[$cid];
    }
    return NULL;
  }
}

/**
 * Put item in the static cache.
 */
function ting_cache_set($id, $value) {
  $cid = 'ting-object';
  if ($value instanceof TingClientObjectCollection) {
    $cid = 'ting-collection';
  }
  $cid .= ':' . $id;

  if ($ttl = variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME)) {
    $cache = cache_set($cid, $value, 'cache', REQUEST_TIME + $ttl);
  }
  else {
    // Without proper caching, use a request cache.
    $cache = &drupal_static(__FUNCTION__);
    if (!isset($cache)) {
      $cache = array();
    }
    $cache[$cid] = $value;
  }
}

/**
 * Get recommendations for a given ISBN.
 *
 * @param string $isbn
 *  ISBN number to get recommendations from.
 * @param $numResults
 *  The number of results to return.
 * @return array
 *  An array of TingClientObjectRecommendation objects.
 */
function ting_get_object_recommendations($isbn, $numResults = 10) {
  $request = ting_get_request_factory()->getObjectRecommendationRequest();
  $request->setIsbn($isbn);
  $request->setNumResults($numResults);
  return ting_execute($request);
}

/**
 * Retrieves an initialized Ting client request factory.
 *
 * @return TingClientRequestFactory
 */
function ting_get_request_factory() {
  static $request_factory;

  if (!isset($request_factory)) {
    $url_variables = array(
      'search' => 'ting_search_url',
      'scan' => 'ting_scan_url',
      'object' => 'ting_search_url',
      'collection' => 'ting_search_url',
      'spell' => 'ting_spell_url',
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

    $request_factory = new TingClientRequestFactory($urls);
  }

  return $request_factory;
}

function ting_add_relations($request, $type = 'full') {
  $request->setAllRelations(TRUE);
  $request->setRelationData($type);
  return $request;
}

/**
 * Perform a request against Ting and perform error handling if necessary
 *
 * @param $request The request
 * @return mixed Result of the request or false if an error occurs
 */
function ting_execute($request) {
  try {
    timer_start('ting');
    $res = ting_get_client()->execute($request);
    timer_stop('ting');
    return $res;
  } catch (TingClientException $e) {
    timer_stop('ting');
    watchdog('ting client', 'Error performing request: ' . $e->getMessage(), NULL, WATCHDOG_ERROR, 'http://' . $_SERVER["HTTP_HOST"] . request_uri());
    return FALSE;
  }
}

/**
 * Retrieves an initialized Ting client with appropriate request adapter and logger
 *
 * @return TingClient
 */
function ting_get_client() {
  static $client;

  if (!isset($client)) {
    $logger = (variable_get('ting_enable_logging', FALSE)) ? new TingClientDrupalWatchDogLogger(ting_get_request_factory()) : new TingClientVoidLogger();
    $client = new TingClient(new TingClientRequestAdapter(), $logger);
  }

  return $client;
}

/**
 * Use OpenScan to search for keyword, check
 * http://oss.dbc.dk/twiki/bin/view/Databroend/OpenSearchDocIndexes
 * for which phrase index to search, default is 'anyIndexes'
 *
 * @param string $query The prefix to scan for
 * @param string $phrase Which phrase index to search
 * @param int $num_results The numver of results to return
 * @return TingClientScanResult
 */
function ting_do_scan($query, $phrase = 'anyIndexes', $num_results = 10) {
  $request = ting_get_request_factory()->getScanRequest();
  $request->setField('phrase.' . $phrase);
  $request->setLower($query);
  $request = ting_add_agency($request);
  $request->setNumResults($num_results);
  return ting_execute($request);
}

/**
 * @param object $request - The TingClient object
 * @return TingClientScanRequest
 */
function ting_add_agency(TingClientScanRequest $request) {
  if ($agency = variable_get('ting_agency', FALSE)) {
    $request->setAgency($agency);
  }
  return $request;
}

/**
 * @param string $word The word to get spell suggestions for
 * @param $num_results The number of results to return
 * @return array An array of TingClientSpellSuggestion objects
 */
function ting_get_spell_suggestions($word, $num_results = 10) {
  $request = ting_get_request_factory()->getSpellRequest();
  $request->setWord($word);
  $request->setNumResults($num_results);
  return ting_execute($request);
}

