<?php
// $Id$

/**
 * @file ting.client.inc
 * Wrapper functions for Ting client.
 */

// Ting client has a ton of includes. Let's load them.
$includes = array(
  'ting-client/lib/TingClient.php',
  'ting-client/lib/adapter/http/TingClientDrupal6HttpRequestAdapter.php',
  'ting-client/lib/request/rest-json/RestJsonTingClientRequestFactory.php',
  'ting-client/lib/log/TingClientDrupalWatchDogLogger.php',
  // 'addi-client/AdditionalInformationService.php'
);

$path = drupal_get_path('module', 'ting') . '/lib/';

foreach ($includes as $include) {
  require_once($path . $include);
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
 * @param $query use the given query when fetching, to trigger collection
 *   ordering.
 */
function ting_get_object($object_id, $collection = FALSE, $query = NULL) {
  if (empty($object_id)) {
    return FALSE;
  }

  // Check the cache first.
  $object = ting_cache_get($object_id);
  if (!$object) {
    // Put a negative reply in the cache. It will be overwritten by the
    // object, or ensure that we won't try to fetch this id again.
    ting_cache_set($object_id, NULL);

    if ($query) {
      $result = ting_do_search('rec.id=' . $object_id . ' AND (' . $query . ')', 1, 1, array('facets' => array(), 'allObjects' => TRUE, 'query' => $query, 'reply_only' => TRUE));
      if (isset($result->collections)) {
        $object = array_shift($result->collections);
      }
    }
    if (!$object) {
      $request = ting_get_request_factory()->getCollectionRequest();
      $request->setObjectId($object_id);
      if ($agency = variable_get('ting_agency', false)) {
        $request->setAgency($agency);
      }
      $request->setAllRelations(TRUE);
      $request->setRelationData($collection ? 'uri' : 'full');
      $object = ting_execute_cache($request, $query);
    }
  }

  // If not asking for a collection, and the object is, return the
  // first sub-object.
  if (!$collection && isset($object->objects)) {
    return $object->objects[0];
  }
  return $object;
}

/**
 * Performs a search agains the well
 *
 * @param string $query
 *    The search query
 * @param int $page
 *    The page number to retrieve search results for
 * @param int $resultsPerPage
 *    The number of results to include per page
 * @param array $options
 *    Options to pass to the search. Possible options are:
 *    - facets: Array of facet names for which to return results. Default: facet.subject, facet.creator, facet.type, facet.date, facet.language
 *    - numFacets: The number of terms to include with each facet. Default: 10
 *    - enrich: Whether to include additional information and cover images with each object. Default: false
 *    - sort: The key to sort the results by. Default: "" (corresponds to relevance). The possible values are defined by the sortType type in the XSD.
 *    - supportingTypes: Whether to include supporting types such as reviews. Default: false
 *    - query: Override the query put on collections.
 *    - reply_only: Don't change the result objects to TingCollection objects.
 * @return TingClientSearchResult
 *    The search result
 */
function ting_do_search($query, $page = 1, $resultsPerPage = 10, $options = array()) {
  $request = ting_get_request_factory()->getSearchRequest();
  $request->setQuery($query);
  if ($agency = variable_get('ting_agency', false)) {
    $request->setAgency($agency);
  }
  $request->setStart($resultsPerPage * ($page - 1) + 1);
  $request->setNumResults($resultsPerPage);

  $request = (!isset($options['supportingTypes']) || !$options['supportingTypes']) ? ting_remove_supporting_types($request) : $request;
  $request->setFacets((isset($options['facets'])) ? $options['facets'] : array('facet.subject', 'facet.creator', 'facet.type', 'facet.category', 'facet.language', 'facet.date', 'facet.acSource'));
  $request->setNumFacets((isset($options['numFacets'])) ? $options['numFacets'] : ((sizeof($request->getFacets()) == 0) ? 0 : 10));
  $request->setSort((isset($options['sort'])) ? $options['sort'] : '');
  $request->setAllObjects(isset($options['allObjects']) ? $options['allObjects'] : FALSE);

  $searchResult = ting_execute_cache($request, (isset($options['query']) ? $options['query'] : $query));
  // Replace collections with proper TingCollection objects.
  if ($searchResult && is_array($searchResult->collections)) {
    $ids = array();
    foreach ($searchResult->collections as &$collection) {
      if (isset($collection->objects[0])){
        $ids[] = $collection->objects[0]->id;
      }
    }
    if (!isset($options['reply_only']) || !$options['reply_only']) {
      $searchResult->collections = entity_load('ting_collection', array(), array('ding_entity_collection_id' => $ids, 'query' => $query));
    }
  }

  return $searchResult;
}

/**
 * Calls ting_execute() and caches the result.
 *
 * Executes the request and caches sub-objects.
 *
 * @param $request the request.
 * @param $query a query to put on collections, for making links later.
 */
function ting_execute_cache($request, $query = NULL) {
  static $calls = array();
  $calls[] = $query;
  if (sizeof($calls) > 1) {
      watchdog('ting', 'Warning, ting_execute called @x times:<br />"@queries"', array('@x' => sizeof($calls), '@queries' => join('" "', $calls)), WATCHDOG_WARNING);
    if (function_exists('dpm') && user_access('access devel information')) {
      drupal_set_message(t('Warning, ting_execute called @x times:<br />"@queries"', array('@x' => sizeof($calls), '@queries' => join('" "', $calls))), 'error');
    }
  }
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
      // Set the query used to load the collection on the collection itself,
      // so it can create links that ensures that the objects is in the same
      // order.
      $collection->load_query = $query;
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
function ting_cache_get($id) {
  if ($ttl = variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME)) {
    $cache = cache_get('ting-object:' . $id);
    if (isset($cache) && ($cache->expire > REQUEST_TIME)) {
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
    // Using array_key_exists, as we might contain NULL values (which is
    // !isset()).
    if (array_key_exists($id, $cache)) {
      return $cache[$id];
    }
    return NULL;
  }
}

/**
 * Put item in the static cache.
 */
function ting_cache_set($id, $value) {
  if ($ttl = variable_get('ting_cache_lifetime', TING_DEFAULT_CACHE_LIFETIME)) {
    $cache = cache_set('ting-object:' . $id, $value, 'cache', REQUEST_TIME + $ttl);
  }
  else {
    // Without proper caching, use a request cache.
    $cache = &drupal_static(__FUNCTION__);
    if (!isset($cache)) {
      $cache = array();
    }
    $cache[$id] = $value;
  }
}

/**
 * Retrieves an initialized Ting client request factory.
 *
 * @return TingClientRequestFactory
 */
function ting_get_request_factory() {
  static $requestFactory;

  if (!isset($requestFactory))
  {
    $urlVariables = array(  'search' => 'ting_search_url',
                            'scan' => 'ting_scan_url',
                            'object' => 'ting_search_url',
                            'collection' => 'ting_search_url',
                            'spell' => 'ting_spell_url',
                            'recommendation' => 'ting_recommendation_url');

    $urls = array();
    foreach ($urlVariables as $name => $setting)
    {
      $urls[$name] = variable_get($setting, false);
      if (!$urls[$name]) {
        throw new TingClientException('No Ting webservice url defined for '.$name);
      }
    }

    $requestFactory = new RestJsonTingClientRequestFactory($urls);
  }

  return $requestFactory;
}

function ting_add_relations($request, $type = 'full') {
  $request->setAllRelations(TRUE);
  $request->setRelationData($type);
  return $request;
}

function ting_remove_supporting_types(TingClientSearchRequest $request) {
  $supportingTypes = array('materialevurdering*', 'anmeldelse');
  foreach ($supportingTypes as &$type)
  {
    $type = 'facet.type='.$type;
  }

  $request->setQuery($request->getQuery().' NOT ('.implode(' OR ', $supportingTypes).')');
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
    return ting_get_client()->execute($request);
  } catch (TingClientException $e) {
      watchdog('ting client', 'Error performing request: '.$e->getMessage(), NULL, WATCHDOG_ERROR, 'http://'.$_SERVER["HTTP_HOST"].$_SERVER["REQUEST_URI"]);
    return false;
  }
}

/**
 * Retrieves an initialized Ting client with appropriate request adapter and logger
 *
 * @return TingClient
 */
function ting_get_client() {
  static $client;

  if (!isset($client))
  {
    $logger = (variable_get('ting_enable_logging', FALSE)) ? new TingClientDrupalWatchDogLogger() : new TingClientVoidLogger();
    $client = new TingClient(new TingClientDrupal6HttpRequestAdapter(), $logger);
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
 * @param int $numResults The numver of results to return
 * @return TingClientScanResult
 */
function ting_do_scan($query, $phrase = 'anyIndexes', $numResults = 10) {
  $request = ting_get_request_factory()->getScanRequest();
  $request->setField('phrase.' . $phrase);
  $request->setLower($query);
  $request = ting_add_agency($request);
  $request->setNumResults($numResults);
  return ting_execute($request);
}

/**
 * @param object $request - The TingClient object
 * @return TingClientAgentRequest
 */
function ting_add_agency(TingClientAgentRequest $request) {
  if ($agency = variable_get('ting_agency', false))
  {
    $request->setAgency($agency);
  }
  return $request;
}

/**
 * @param string $word The word to get spell suggestions for
 * @param $numResults The number of results to return
 * @return array An array of TingClientSpellSuggestion objects
 */
function ting_get_spell_suggestions($word, $numResults = 10) {
  $request = ting_get_request_factory()->getSpellRequest();
  $request->setWord($word);
  $request->setNumResults($numResults);
  return ting_execute($request);
}

