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
   *  Specify number of terms to return for each facet.
   */
  protected $termsPerFacet = NULL;

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
   * @see setRawQuery()
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

  /**
   * @var BooleanStatementGroup[]
   *   List of grouped BooleanStatementGroup and TingSearchFieldFilter
   *   instances.
   */
  protected $fieldFilters;

  /**
   * The part of the query that should be interpreted as a fulltext search.
   *
   * @var string
   */
  protected $fullTextQuery;

  /**
   * Whether in particular fulltext searches are fuzzy.
   *
   * @var bool
   */
  protected $fuzzy = FALSE;

  /**
   * Specifies whether collections in the search-result should be fully
   * populated. Eg. the returned collection may contain materials that does not
   * match the search-query, but shares collection with a material that does.
   *
   * @var bool
   */
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
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function setPopulateCollections($populate_collections) {
    $this->populateCollections = $populate_collections;
    return $this;
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
   * The part of the query that should be interpreted as a fulltext query.
   *
   * @return string
   *   The query fragment.
   */
  public function getFullTextQuery() {
    return $this->fullTextQuery;
  }

  /**
   * Sets a string that should be interpreted as a fulltext query.
   *
   * The query may still contain more "advanced" parts such as a field filter.
   *
   * @param string $full_text_query
   *   Any string.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function setFullTextQuery($full_text_query) {
    $this->fullTextQuery = $full_text_query;
    return $this;
  }

  /**
   * Sets list of facets the query will return results for alongside materials.
   *
   * @param string[] $facets
   *   The facets.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function setFacets($facets) {
    $this->facets = $facets;
    return $this;
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
   * Returns whether searches should be fuzzy.
   *
   * @return bool
   *   Whether the search should be fuzzy.
   */
  public function isFuzzy() {
    return $this->fuzzy;
  }

  /**
   * Sets whether searches should be fuzzy.
   *
   * This will in particular affect full-text queries specified via
   * setFullTextQuery()
   *
   * @param bool $fuzzy
   *   The flag.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function setFuzzy($fuzzy) {
    $this->fuzzy = $fuzzy;
    return $this;
  }

  /**
   * Maximum number of terms to return per facet.
   *
   * @return int
   *   The maximum.
   */
  public function getTermsPerFacet() {
    return $this->termsPerFacet;
  }

  /**
   * Sets the maximum number of terms to return per facet.
   *
   * @param int $terms_per_facet
   *   The maximum number of terms to return pr facet.
   *
   * @return TingSearchRequest
   *   The current query object.
   */
  public function setTermsPrFacet($terms_per_facet) {
    $this->termsPerFacet = $terms_per_facet;
    return $this;
  }

  /**
   * Get the page the search result should start at.
   *
   * @return int
   *   The page-number, defaults to 1.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function getPage() {
    return $this->page;
  }

  /**
   * Sets the page the search result should start at.
   *
   * @param int $page
   *   The page-number, defaults to 1.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function setPage($page) {
    $this->page = $page;
    return $this;
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
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function addSort($field, $direction) {
    $this->sorts[] = new TingSearchSort($field, $direction);
    return $this;
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
   * Sets a raw provider-specific query-string to be added to the final query.
   *
   * The query will not be processed in any way and will be AND'ed together with
   * any other statements added to the query.
   * It is up to the caller of this method to ensure that the query is
   * compatible with the currently enabled search provider.
   *
   * @param string $query
   *   The query.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function setRawQuery($query) {
    $this->rawQuery = $query;
    return $this;
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
   * Set the list of provider-specific material ids the query is constrained to.
   *
   * The ID can be received from a TingObjectInterface instance via getId().
   *
   * TODO BBS-SAL: This should support both including and excluding. Eg.
   * setMaterialFilter($material_ids, <indcation of include/exclude> and it
   * should just add a new boolean filter group. When done this can replace
   * ding_serendipity_exclude.
   *
   * @param string[]|string $material_ids
   *   One or more ids.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function setMaterialFilter($material_ids) {
    if (!is_array($material_ids)) {
      $material_ids = [$material_ids];
    }

    $this->materialFilterIds = $material_ids;
    return $this;
  }

  /**
   * Get the list of BooleanStatementGroup instances.
   *
   * @return BooleanStatementGroup[]
   *   List of BooleanStatementGroup intances used to filter field.
   */
  public function getFieldFilters() {
    return $this->fieldFilters;
  }

  /**
   * Filter(s) or statement group(s) to add to the query.
   *
   * @param mixed[]|\Ting\Search\BooleanStatementGroup|\Ting\Search\TingSearchFieldFilter $filters
   *   A single BooleanStatementGroup or TingSearchFieldFilter or a (potentially
   *   mixed) array of both.
   *
   * @param string $logic_operator
   *   Operator to apply if this is not the first statement. See
   *   BooleanStatementInterface::OP_*
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function addFieldFilters($filters, $logic_operator = BooleanStatementInterface::OP_AND) {
    // First off, protect against silly code.
    if (empty($filters)) {
      return $this;
    }

    // If this is not already a group, well have to do some work before adding
    // it.
    if (!($filters instanceof BooleanStatementGroup)) {
      // We're about to wrap the filter in a group - make sure it is an array
      // before doing so.
      if (!is_array($filters)) {
        // Wrap in an array if it's not already.
        $filters = [$filters];
      }

      // Wrap the array in an group.
      $filters = new BooleanStatementGroup($filters, $logic_operator);
    }

    $this->fieldFilters[] = $filters;
    return $this;
  }

  /**
   * Utility function for adding a single field filter.
   *
   * The field will be AND'ed together with any other filters added to the
   * query. If you need OR or any more complex grouping of filters and groups
   * use addFieldFilters().
   *
   * @param string $name
   *   The field name.
   *
   * @param mixed|TingSearchFieldFilter::BOOLEAN_FIELD_VALUE $value
   *   Field value, if omitted or set to
   *   TingSearchFieldFilter::BOOLEAN_FIELD_VALUE the field is treated as a
   *   boolean field that will be compared without an operator Eg:
   *   (myboolfield AND anotherfield=123)
   * @param string $operator
   *   Operator to use when comparing the field instance with a value.
   *
   * @return TingSearchRequest
   *   the current query object.
   */
  public function addFieldFilter($name, $value = TingSearchFieldFilter::BOOLEAN_FIELD_VALUE, $operator = '=') {
    $this->addFieldFilters([new TingSearchFieldFilter($name, $value, $operator)]);
    return $this;
  }
}
