<?php

/**
 * @file
 * The TingSearchRequest class.
 */

namespace Ting\Search;

/**
 * Class TingSearchRequest
 *
 * A request for a search using a search provider.
 *
 * TODO BBS-SAL: TingClient has multiple types of "Request"s eg.
 * TingClientObjectRequest - We should have this in mind during the
 * implementation of SAL. On the one hand we don't want to make  eg.
 * TingSearchRequest to generic in order to handle a wide range of ways to
 * Interact with Open Search, on the other hand, we want to keep things as
 * simple as possible - if there is a simple way of handling two different use-
 * cases using the same functionality, we should prefer that over solving it
 * with complexity.
 *
 * @package Ting\Search
 */
class TingSearchRequest {

  /**
   * @var \Ting\Search\TingSearchStrategyInterface
   */
  protected $searchStrategy;

  /**
   * @var string
   *   A short query that the provider is allowed to interpret more freely than
   *   a "real" query.
   */
  protected $simpleQuery;

  /**
   * @var int
   *   Maximum number of results to return.
   */
  protected $numResults;

  /**
   * @var string[]
   *   Facets this query should query within. If empty all facets will be
   *   queried.
   */
  protected $facets = [];

  /**
   * TingSearchQuery constructor.
   *
   * @param \Ting\Search\TingSearchStrategyInterface $search_strategy
   *   The strategy to use when searching.
   */
  public function __construct($search_strategy) {
    $this->searchStrategy = $search_strategy;
  }

  /**
   * Sets the maximum number of results to return.
   *
   * @param int $max
   *   The maximum value.
   *
   * @return \Ting\Search\TingSearchRequest
   *   Current search query object.
   */
  public function setCount($max) {
    $this->numResults = $max;
    return $this;
  }

  /**
   * Performs the search-query.
   *
   * @return \Ting\Search\TingSearchResultInterface
   *   The response.
   */
  public function execute() {
    // Delegate to the strategy.
    return $this->searchStrategy->executeSearch($this);
  }

  /**
   * Perform a search with a "simple" query.
   *
   * A simple query is a query that is easy for the user to enter, and may
   * reference a specific ID.
   *
   * The underlying search-provider may return results that only match partially
   * and will attempt to match the query against any relevant identifier of the
   * materiale. Eg. a ISBN.
   *
   * @param string $query
   *   A simple string that may only match the materials partially, or may be a
   *   material-specific ID such as a ISBN
   */
  public function setSimpleQuery($query) {
    $this->simpleQuery = $query;
  }

  /**
   * Get the current simple-query string.
   *
   * @return string
   *   The querys
   */
  public function getSimpleQuery() {
    return $this->simpleQuery;
  }

  /**
   * Gets the list of facets the query should work within.
   *
   * @return string[]
   *   The facets.
   */
  public function getFacets() {
    return $this->facets;
  }

  /**
   * Sets the list of facets the query should work within.
   *
   * @param string[] $facets
   *   The facets.
   */
  public function setFacets($facets) {
    $this->facets = $facets;
  }

}
