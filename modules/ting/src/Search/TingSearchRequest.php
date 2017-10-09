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
   *   Facets we want to query against. If specified the search-result should
   *   enumerate facet-matches alongside the actual material matches.
   */
  protected $facets = [];

  /**
   * @var int
   *   Page offset. Defaults to 1 (first page)
   */
  protected $page = 1;

  /**
   * Sort directions.
   *
   * @var \Ting\Search\TingSearchSort[]
   */
  protected $sorts = [];

  /**
   * Raw provider-specific query string.
   *
   * @var string
   */
  protected $rawQuery;

  /**
   * Hints specific to the provider.
   *
   * Setting these hints must not affect the "business" result of doing the
   * query. That is, the query should be able to perform its purpose without
   * the hint, but given the hint it may eg. perform better.
   *
   * @var array
   */
  protected $providerSpecificHints;

  /**
   * Material IDs we what the query constrained to.
   *
   * @var string[]
   *   List of ids.
   */
  protected $materialFilterIds;

  protected $fieldFilters;

  protected $populateCollections = FALSE;

  /**
   * Gets whether the search result should contain fully populated collections.
   *
   * @return bool
   *   The flag.
   */
  public function getPopulateCollections() {
    return $this->populateCollections;
  }

  /**
   * Sets whether the search result should contain fully populated collections.
   *
   * @param bool $populate_collections
   *   The flag.
   */
  public function setPopulateCollections($populate_collections) {
    $this->populateCollections = $populate_collections;
  }

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
   * Gets the current maximum number of results to return.
   *
   * @return int|NULL
   *   The maximum value. NULL if the value has not been set.
   */
  public function getCount() {
    return $this->numResults;
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
   * Sets list of facets the query will return results for alongside materials.
   *
   * @param string[] $facets
   *   The facets.
   */
  public function setFacets($facets) {
    $this->facets = $facets;
  }

  /**
   * List of facets the query will return results for alongside materials.
   *
   * @return string[]
   *   The facets.
   */
  public function getFacets() {
    return $this->facets;
  }

  /**
   * Get the page the search result should start at.
   *
   * @return int
   *   The page-number, defaults to 1.
   */
  public function getPage() {
    return $this->page;
  }

  /**
   * Sets the page the search result should start at.
   *
   * @param int $page
   *   The page-number, defaults to 1.
   */
  public function setPage($page) {
    $this->page = $page;
  }

  /**
   * Get the current sorts.
   *
   * @return \Ting\Search\TingSearchSort[]
   *   The sorts.
   */
  public function getSorts() {
    return $this->sorts;
  }

  /**
   * Add a sort based on a field to the query.
   *
   * @param string $field
   *   The field to sort on.
   *
   * @param string $direction
   *   The direction, see TingSearchSort::DIRECTION_*
   */
  public function addSort($field, $direction) {
    $this->sorts[] = new TingSearchSort($field, $direction);
  }

  /**
   * Gets a raw-query.
   *
   * Beware that this is a query passed in via setRawQuery() and _not_ the
   * final query represented by the rest of the TingSearchRequest instance.
   *
   * @return string
   *   The query.
   */
  public function getRawQuery() {
    return $this->rawQuery;
  }

  /**
   * Sets a raw string to be added to the final query.
   *
   * Beware that the query passed in should be compatible with the currently
   * enabled provider.
   *
   * @param string $query
   *   The query.
   */
  public function setRawQuery($query) {
    $this->rawQuery = $query;
  }

  /**
   * Get list of material ids the query is constrained to.
   *
   * @return string[]
   *   The ids.
   */
  public function getMaterialFilter() {
    return $this->materialFilterIds;
  }

  /**
   * Set the list of material ids the query is constrained to.
   *
   * @param string[] $material_ids
   *   The ids.
   */
  public function setMaterialFilter($material_ids) {
    $this->materialFilterIds = $material_ids;
  }

  /**
   * Get the list of field filters.
   *
   * @return \Ting\Search\BooleanStatementInterface[]
   *   The filters.
   */
  public function getFieldFilters() {
    return $this->fieldFilters;
  }

  /**
   * Filter(s) or statement group(s) to add to the query.
   *
   * @param BooleanStatementInterface[]|BooleanStatementInterface $filters
   *   One or more filters.
   *
   * @param string $logic_operator
   *   Operator to apply if this is not the first statement. See
   *   BooleanStatementInterface::OP_*
   */
  public function addFieldFilters($filters, $logic_operator = BooleanStatementInterface::OP_AND) {
    // Wrap in an array if it's not already.
    if (!is_array($filters)) {
      $filters = [$filters];
    }
    if (!empty($filters)) {
      $this->fieldFilters[] = new BooleanStatementGroup($filters, $logic_operator);
    }
  }
}
