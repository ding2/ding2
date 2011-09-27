<?php

/**
 * AHAH callback to retrieve carousel items
 */
function ting_search_carousel_result_ahah($search, $start, $numResults) {
	module_load_include('client.inc', 'ting');	
	
	//retrive all searches to determine which to perform
  $searches = variable_get('ting_search_carousel_searches', array());
  $search_keys = array_keys($searches);
	if (!isset($searches[$search_keys[$search]]))
	{
		drupal_not_found();
		exit;
	}
	$search = $searches[$search_keys[$search]];

	//define a carousel search with valid collections and the highest checked search
	//result index so far
	$carouselSearch = new stdClass();
	$carouselSearch->collections = array();
	$carouselSearch->lastIndex = 0;
	$carouselSearch->more = true;
	
	//retrieve cached search result if it exists
  $cache = cache_get(md5($search['query']), 'cache_ting_search_carousel');
  if ($cache)
  {
  	$carouselSearch = $cache->data;
  }
  
  //if the cached search contains less than the required number of collections
  //the try to retrieve som more
  $resultsPerPage = 10;
  $page = ceil($carouselSearch->lastIndex / $resultsPerPage);
  while ((sizeof($carouselSearch->collections) < ($start + $numResults)) && $carouselSearch->more) {
    $result = ting_do_search($search['query'], ++$page, $resultsPerPage, array('facets' => array(), 'enrich' => TRUE, 'allObjects' => FALSE));

    if (sizeof($result->collections) > 0)	{
      foreach ($result->collections as $collection) {
        foreach ($collection->objects as $object) {
          if ($object->additionalInformation->thumbnailUrl ||
              $objects->additionalInformation->detailUrl) {

            $carouselSearch->collections[] = $collection;
            break;
          }
        }
				$carouselSearch->lastIndex++;
      }
    }
    else {
      $carouselSearch->more = FALSE;
    }
		
	  //cache the updated search after each query as retrieving the requested number 
	  //of collections with cover images might take a few requests
	  cache_set(md5($search['query']), $carouselSearch, 'cache_ting_search_carousel', time()+variable_get('ting_search_carousel_cache_duration', 604800));		
	}
	
	//render the collections for the carousel
	$result = '';
	for ($i = $start; $i < ($start + $numResults); $i++)
	{
		if (isset($carouselSearch->collections[$i]))
		{
  		$result .= theme('ting_search_carousel_collection', $carouselSearch->collections[$i]);
		}
	}
	
	echo $result;
	exit;
}
