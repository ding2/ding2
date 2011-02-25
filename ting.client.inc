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

function ting_get_object($object_id, $collection = FALSE) {
  if (empty($object_id)) { return FALSE; }
  static $cache = array();

  if (isset($cache[$object_id])) {
    $object = $cache[$object_id];
  }
  else {
    $request = ting_get_request_factory()->getCollectionRequest();
    $request->setObjectId($object_id);
    $request = ting_add_agency($request);
    // $request = ting_add_relations($request, 'uri');
    $object = ting_execute($request);
  }

  $cache[$object_id] = $object;

  if (!$collection) {
    return $object->objects[0];
  }
  return $object;
}


/**
 * Return a ting object, using a cache that's settable from the outside.
 *
 * This is a stopgap measure until refactoring this file.
 */
function ting_object_cache($id = NULL, $objects = NULL) {
  static $cache = array();
  if ($objects) {
    foreach ($objects as $object) {
      $cache[$object->id] = $object;
    }
  }
  if ($id) {
    if (isset($cache[$id])) {
      return $cache[$id];
    }
    else {
      $object = ting_get_object_by_id($id, TRUE);
      if ($object) {
        $cache[$object->id] = $object;
        return $object;
      }
    }
  }
  return NULL;
}

/**
 * Load an object from Ting by ID.
 *
 * @param string $object_id
 *    Ting object ID.
 * @param bool $enrich
 *    Whether to enrich the object with additional information, covers etc.
 * @return mixed
 *    Object, if found - boolean FALSE if not.
 */
function ting_get_object_by_id($object_id, $enrich = FALSE) {
  if (empty($object_id)) { return FALSE; }
  static $cache = array();

  if (isset($cache[$object_id])) {
    $object = $cache[$object_id];
  }
  else {
    $request = ting_get_request_factory()->getObjectRequest();
    $request->setObjectId($object_id);
    $request = ting_add_agency($request);
    if ($enrich) {
      $request = ting_add_relations($request);
    }
    $object = ting_execute($request);

    if ($object) {
      $object = ting_add_object_info($object);
    }
  }

  if ($object && $enrich && empty($object->enriched)) {
    if (class_exists('AdditionalInformationService')) {
      $object = array_shift(ting_add_additional_info(array($object)));
    }
    $object->enriched = TRUE;
  }

  $cache[$object_id] = $object;

  return $object;
}

/**
 * Load an object from Ting by local ID (faust number).
 *
 * @param string $local_id
 *    Local identifier
 * @param bool $enrich
 *    Whether to enrich the object with additional information, covers etc.
 * @return mixed
 *    TingClientObject if found, FALSE if not.
 */
function ting_get_object_by_local_id($local_id, $enrich = FALSE) {
  if (empty($local_id)) { return FALSE; }
  $request = ting_get_request_factory()->getObjectRequest();
  $request->setLocalId($local_id);
  $request = ting_add_agency($request);
  if ($enrich) {
    $request = ting_add_relations($request);
  }
  $object = ting_execute($request);

  if ($object) {
    $object = ting_add_object_info($object);
    $object = ($enrich) ? array_shift(ting_add_additional_info(array($object))) : $object;
  }
  return ($object) ? $object : FALSE;
}

/**
 * Display a Ting collection of objects.
 *
 * @param string $collection_id
 *    Ting collection ID.
 * @param bool $enrich
 *    Whether to enrich objects in the collection with additional information, covers etc.
 * @return mixed
 *    Collection object, if found - boolean FALSE if not.
 */
function ting_get_collection_by_id($object_id, $enrich = FALSE) {
  // If passed object_id is empty, save ourselves the trouble of trying
  // to load the Ting client, do a request, etc. Big speedup for empty
  // Ting reference fields.
  if (empty($object_id)) { return FALSE; }

  static $cache = array();

  if (isset($cache[$object_id])) {
    $collection = $cache[$object_id];
  }
  else {
    $request = ting_get_request_factory()->getCollectionRequest();
    $request->setObjectId($object_id);
    $request = ting_add_agency($request);
    $collection = ting_execute($request);

    if ($collection) {
      $collection = ting_add_collection_info($collection);
    }
  }

  if ($collection && $enrich && empty($collection->enriched)) {
    $collection = ting_add_additional_info($collection);
    $collection->enriched = TRUE;
  }

  $cache[$object_id] = $collection;

  return $collection;
}

/**
 * Return the possible sort keys and their corresponding labels.
 *
 * @return
 *   A key/value array of sort keys and labels.
 */
function ting_search_sort_options() {
  return array(
    '' => t('Relevance'),
    'title_ascending' => t('Title – A → Z'),
    'title_descending' => t('Title – Z → A'),
    'creator_ascending' => t('Author – A → Z'),
    'creator_descending' => t('Author – Z → A'),
    'date_descending' => t('Year of publication – newest first'),
    'date_ascending' => t('Year of publication – oldest first'),
  );
}

/**
 * Performs a search agains the
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
 * @return TingClientSearchResult
 *    The search result
 */
function ting_do_search($query, $page = 1, $resultsPerPage = 10, $options = array()) {
  $request = ting_get_request_factory()->getSearchRequest();
  $request->setQuery($query);
  $request = ting_add_agency($request);
  $request->setStart($resultsPerPage * ($page - 1) + 1);
  $request->setNumResults($resultsPerPage);

  $request = (!isset($options['supportingTypes']) || !$options['supportingTypes']) ? ting_remove_supporting_types($request) : $request;
  $request->setFacets((isset($options['facets'])) ? $options['facets'] : array('facet.subject', 'facet.creator', 'facet.type', 'facet.category', 'facet.language', 'facet.date', 'facet.acSource'));
  $request->setNumFacets((isset($options['numFacets'])) ? $options['numFacets'] : ((sizeof($request->getFacets()) == 0) ? 0 : 10));
  $request->setSort((isset($options['sort'])) ? $options['sort'] : '');
  $request->setAllObjects(isset($options['allObjects']) ? $options['allObjects'] : FALSE);

  $searchResult = ting_execute($request);

  //Decorate search result with additional information
  if (is_array($searchResult->collections)) {
    foreach ($searchResult->collections as &$collection) {
      $collection = ting_add_collection_info($collection, $query);
      if (isset($options['enrich']) && $options['enrich']) {
        $collection = ting_add_additional_info($collection);
      }
    }
  }

  return $searchResult;
}

/**
 * @param string $query The prefix to scan for
 * @param int $numResults The numver of results to return
 * @return TingClientScanResult
 */
function ting_do_scan($query, $numResults = 10) {
  $request = ting_get_request_factory()->getScanRequest();
  $request->setField('phrase.anyIndexes');
  $request->setLower($query);
    $request = ting_add_agency($request);
  $request->setNumResults($numResults);
  return ting_execute($request);
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

/**
 * @param string $isbn ISBN number to get recommendations from
 * @param $numResults The number of results to return
 * @return array An array of TingClientObjectRecommendation objects
 */
function ting_get_object_recommendations($isbn, $numResults = 10) {
  $request = ting_get_request_factory()->getObjectRecommendationRequest();
  $request->setIsbn($isbn);
  $request->setNumResults($numResults);
  return ting_execute($request);
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
    $logger = (variable_get('ting_enable_logging', false)) ? new TingClientDrupalWatchDogLogger() : new TingClientVoidLogger();
    $client = new TingClient(new TingClientDrupal6HttpRequestAdapter(), $logger);
  }

  return $client;
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

function ting_add_collection_info(TingClientObjectCollection $collection, $query = NULL) {
  $types = array();
  $subject_count = array();

  foreach ($collection->objects as $object) {
    $object = ting_add_object_info($object);
    $types[] = $object->type;
    foreach ($object->subjects as $subject) {
      if (!isset($subject_count[$subject])) {
        $subject_count[$subject] = 0;
      }
      $subject_count[$subject]++;
    }
  }
  $collection->types = array_unique($types);

  asort($subject_count);
  // All subjects from all objects with the most common ones first.
  $collection->subjects = array_keys($subject_count);

  $common_object = $collection->objects[0];

  $collection->id = $common_object->id;
  $collection->title = $common_object->title;
  $collection->abstract = $common_object->abstract;
  $collection->creators = $common_object->creators;
  $collection->creators_string = $common_object->creators_string;
  $collection->date = $common_object->date;

  if (sizeof($collection->objects) > 1) {
    $collection->url = url('ting/collection/' . $collection->id . ($query ? '/' . $query : ''), array('absolute' => true));
  }
  else {
    // Link collections of one object to the object.
    $collection->url = url('ting/object/' . $collection->id, array('absolute' => true));
  }

  return $collection;
}

function ting_add_object_info(TingClientObject $object) {
  $object->type     = !empty($object->record['dc:type']) ? $object->record['dc:type']['dkdcplus:BibDK-Type'][0] : FALSE;
  $object->language = !empty($object->record['dc:language'][''][0]) ? $object->record['dc:language'][''][0] : FALSE;
  $object->title    = !empty($object->record['dc:title']) ? $object->record['dc:title'][''][0] : FALSE;
  $object->abstract = !empty($object->record['dcterms:abstract'][''][0]) ? $object->record['dcterms:abstract'][''][0] : FALSE;
  $object->date     = !empty($object->record['dc:date'][''][0]) ? $object->record['dc:date'][''][0] : FALSE;

  $object->creators = array();
  if (!empty($object->record['dc:creator'])) {
    foreach ($object->record['dc:creator'] as $type => $dc_creator) {
      if ($type != 'oss:sort') {
        $object->creators = array_merge($object->creators, $dc_creator);
      }
    }
  }
  $object->creators_string = implode(', ', $object->creators);

  $object->subjects = array();
  if (!empty($object->record['dc:subject'])) {
    foreach ($object->record['dc:subject'] as $type => $dc_subject) {
      if (in_array($type, array('dkdcplus:DBCF', 'dkdcplus:DBCS', 'dkdcplus:DBCM', 'dkdcplus:DBCO', 'dkdcplus:DBCN'))) {
        $object->subjects = array_merge($object->subjects, $dc_subject);
      }
    }
  }

  $object->url = url('ting/object/'.$object->id, array('absolute' => TRUE));

  if (!empty($object->record['dc:identifier']['dcterms:URI'])) {
    foreach ($object->record['dc:identifier']['dcterms:URI'] as $url) {
      $object->online_url = ting_rewrite_download_url($url);
    }
  }

  if ($object->relations) {
    // Add details to relation objects.
    foreach ($object->relations as $key => $relation) {
      $object->relations[$key] = ting_add_object_info($relation);
    }
  }

  return $object;
}

/**
 * Add additional information info for cover images.
 *
 * @param object $collection
 * @return object
 */
function ting_add_additional_info($collection) {
  $faust_numbers = array();

  $objects = (isset($collection->objects)) ? $collection->objects : $collection;

  foreach ($objects as $object) {
    if ($object->localId) {
      $faust_numbers[] = $object->localId;
    }
  }

  if (sizeof($faust_numbers) > 0) {
    foreach (ting_get_additional_info($faust_numbers) as $faust_number => $ai) {
      foreach ($objects as &$object) {
        if ($faust_number == $object->localId) {
          $object->additionalInformation = $ai;
        }
      }
    }
  }

  if (isset($collection->objects)) {
    $collection->objects = $objects;
  }
  else {
    $collection = $objects;
  }

  return $collection;
}

/**
 * Get additional info for a number of FAUST numbers.
 *
 * @param array $faust_numbers
 *    Array of the FAUST numbers to look up.
 * @return array
 *    Additional info keyed by FAUST number.
 */
function ting_get_additional_info($faust_numbers) {
  $addiVariables = array(
    'wsdlUrl' => 'addi_wdsl_url',
    'username' => 'addi_username',
    'group' => 'addi_group',
    'password' => 'addi_password',
  );

  foreach ($addiVariables as $name => &$setting) {
    $setting = variable_get($setting, false);
    if (!$name) {
      watchdog('TingClient', 'Additional Information service setting '.$name.' not set', array(), WATCHDOG_WARNING);
      return $collection;
    }
  }

  extract($addiVariables);

  $additionalInformationService = new AdditionalInformationService($wsdlUrl, $username, $group, $password);

  try {
    return $additionalInformationService->getByFaustNumber($faust_numbers);
  }
  catch (AdditionalInformationServiceException $e) {
    watchdog('TingClient', 'Error retrieving additional information and covers: '.$e->getMessage(), $isbns, WATCHDOG_ERROR);
  }
  // TODO: SoapFault should probably be catched within the Ting client.
  catch (SoapFault $e) {
    watchdog('TingClient', 'Error retrieving additional information and covers: '.$e->getMessage(), $isbns, WATCHDOG_ERROR);
  }

  return array();
}

function ting_add_agency(TingClientAgentRequest $request) {
  if ($agency = variable_get('ting_agency', false))
  {
    $request->setAgency($agency);
  }
  return $request;
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
 * Rewrite the download URL of external restricted-access ressources.
 *
 * This allow access to the ressources through the library's proxy server.
 *
 * Only URLs refererring to sites specified on the Ting settings page are
 * modified; other URLs are returned unmodified.
 */
function ting_rewrite_download_url($url) {
  $host = parse_url($url, PHP_URL_HOST);
  if (in_array($host, variable_get('restricted_access_proxy_hostnames', array()))) {
    $prefix = variable_get('restricted_access_proxy_prefix', '');
    if ($prefix) {
      $url = $prefix . $url;
    }
  }
  return $url;
}

