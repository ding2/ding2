<?php

/**
 * @file
 * The TingSearchRequest class.
 */

namespace Ting\Search;

/**
 * A search request using a search provider.
 *
 * This class is intetionally immutable. Calls to modify the state of a search
 * request will result in a new object. This avoids unnecessary side effects
 * to existing request objects if a request object is used as a basis for new
 * searches.
 *
 * @package Ting\Search
 */
class TingSearchRequest {

  /**
   * Collections within search results should contain a group of objects defined
   * as a work. Examples of objects which may be defined as a work:
   *
   * - All editions of the same title
   * - All translations of the same title
   * - A title in book, audio book, ebook and movie format.
   *
   * It is up to the individual provider to determine what constitutes a work.
   */
  const COLLECTION_TYPE_WORK = 'collection_type_work';

  /**
   * Each collection within the search result must only contain a single object.
   */
  const COLLECTION_TYPE_SINGLE_OBJECT = 'collection_type_single_object';

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
   * @see withRawQuery()
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
   * If the list of material ID's should be included or excluded.
   *
   * @var bool
   *   The flag.
   */
  protected $materialFilterInclude = TRUE;

  /**
   * @var BooleanStatementGroup[]
   *   List of grouped BooleanStatementGroup and TingSearchFieldFilter
   *   instances.
   */
  protected $filters = [];

  /**
   * The part of the query that should be interpreted as a fulltext search.
   *
   * @var string
   */
  protected $fullTextQuery;

  /**
   * Specifies whether collections in the search-result should be fully
   * populated. Eg. the returned collection may contain materials that does not
   * match the search-query, but shares collection with a material that does.
   *
   * @var bool
   */
  protected $populateCollections = FALSE;

  /**
   * Specifies how collections should be handled within the search result.
   *
   * @see \Ting\Search\TingSearchRequest::COLLECTION_TYPE_*
   *
   * @var string
   */
  protected $collectionType = self::COLLECTION_TYPE_WORK;

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
   *   Updated search query object.
   */
  public function withCount($max) {
    $clone = clone $this;
    $clone->numResults = $max;
    return $clone;
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
   *   Updated search request object.
   */
  public function withFullTextQuery($full_text_query) {
    $clone = clone $this;
    $clone->fullTextQuery = $full_text_query;
    return $clone;
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
   *   Updated search request object.
   */
  public function withTermsPrFacet($terms_per_facet) {
    $clone = clone $this;
    $clone->termsPerFacet = $terms_per_facet;
    return $clone;
  }

  /**
   * The facets used for this search request.
   *
   * @see TingSearchRequest::setFacets() for more information.
   *
   * @return string[]
   *   The facets.
   */
  public function getFacets() {
    return $this->facets;
  }

  /**
   * Sets which facets that search request should return.
   *
   * Note that facets set will be provider dependent. Search providers are not
   * likely to have the same facets available and referencing the id of a
   * facet for a specific provider will break search request for another
   * provider. So this should be used with care or it might limit the usefulness
   * of the module using it.
   *
   * Modules specifying facets to retrieve should make the facets used
   * configurable in the site administration.
   *
   * @param string[] $facets
   *    The facets used for the search.
   *
   * @return TingSearchRequest
   *   Updated search request object.
   */
  public function withFacets(array $facets) {
    $clone = clone $this;
    $clone->facets = $facets;
    return $clone;
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
   *
   * @return TingSearchRequest
   *   Updated search request object.
   */
  public function withPage($page) {
    $clone = clone $this;
    $clone->page = $page;
    return $clone;
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
   *   Updated search request object.
   */
  public function withSort($field, $direction = TingSearchSort::DIRECTION_NONE) {
    $clone = clone $this;
    $clone->sorts[] = new TingSearchSort($field, $direction);
    return $clone;
  }

  /**
   * Add one or more sorts to the query.
   *
   * @param TingSearchSort[] $sorts
   *   List of TingSearchSort instances.
   *
   * @return TingSearchRequest
   *   Updated search request object.
   */
  public function withSorts($sorts) {
    if (!is_array($sorts)) {
      $sorts = [$sorts];
    }
    $clone = clone $this;
    $clone->sorts += $sorts;
    return $clone;
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
   *   Updated search request object.
   */
  public function withRawQuery($query) {
    $clone = clone $this;
    $clone->rawQuery = $query;
    return $clone;
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
   * If the id's are included or excluded.
   *
   * @return bool
   *   The flag.
   */
  public function isMaterialFilterInclude() {
    return $this->materialFilterInclude;
  }

  /**
   * Set the list of provider-specific material ids the query is constrained to.
   *
   * The ID can be received from a TingObjectInterface instance via getId().
   *
   * @param string[]|string $material_ids
   *   One or more ids.
   *
   * @param bool $include
   *   Includes the materials if true and excludes them if false.
   *
   * @return TingSearchRequest
   *   Updated search request object.
   */
  public function withMaterialFilter($material_ids, $include = TRUE) {
    if (!is_array($material_ids)) {
      $material_ids = [$material_ids];
    }

    $clone = clone $this;
    $clone->materialFilterIds = $material_ids;
    $clone->materialFilterInclude = $include;
    return $clone;
  }

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
   *   Updated search request object.
   */
  public function withPopulateCollections($populate_collections) {
    $clone = clone $this;
    $clone->populateCollections = $populate_collections;
    return $clone;
  }

  /**
   * Determine whether a collection should be used for the request.
   *
   * @see TingSearchRequest::COLLECTION_TYPE_*
   *
   * @return bool
   *   Whether to use the specified collection type
   */
  public function useCollectionType($type) {
    return $this->collectionType === $type;
  }

  /**
   * Sets the collection type to use for the request.
   *
   * @see TingSearchRequest::COLLECTION_TYPE_*
   *
   * @param string $collectionType
   *   The collection type.
   *
   * @return TingSearchRequest
   *   Updated search request object.
   */
  public function withCollectionType($collectionType) {
    $clone = clone $this;
    $clone->collectionType = $collectionType;
    return $clone;
  }

  /**
   * Get the list of BooleanStatementGroup instances.
   *
   * When executed the statements must be joined together with a logical AND.
   *
   * @return FilterStatementInterface[]
   *   List of BooleanStatementGroup instances used to filter field.
   */
  public function &getFilters() {
    return $this->filters;
  }

  /**
   * Filter(s) or statement group(s) to add to the query.
   *
   * If the query already contains filters, the filters specified in $filters
   * will be AND'ed with the existing filters.
   *
   * @param \Ting\Search\FilterStatementInterface[]|\Ting\Search\FilterStatementInterface $filters
   *   A single BooleanStatementGroup or TingSearchFieldFilter or a (potentially
   *   mixed) array of both.
   * @param string $logic_operator
   *   Logical operator to use for joining filters together if $filters contains
   *   more than one filter. See BooleanStatementInterface::OP_*.
   *
   * @return TingSearchRequest
   *   Updated search request object.
   *
   * @throws \Ting\Search\UnsupportedSearchQueryException
   */
  public function withFilters($filters, $logic_operator = BooleanStatementInterface::OP_AND) {
    // First off, protect against silly code.
    if (empty($filters)) {
      return $this;
    }

    // Ensure we got what we expected.
    $check_array = is_array($filters) ? $filters : [$filters];
    array_walk($check_array, function ($filter) {
      if (!(
        $filter instanceof BooleanStatementGroup ||
        $filter instanceof TingSearchFieldFilter ||
        $filter instanceof TingSearchRawFilter
      )) {
        // We got something unexpected.
        $details = is_object($filter) ? get_class($filter) : (string) $filter;
        throw new UnsupportedSearchQueryException(
          'Encountered unknown filter type ' . $details
        );
      }
    });

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

    $clone = clone $this;
    $clone->filters[] = $filters;
    return $clone;
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
   * @param mixed $value
   *   Expected field-value.
   * @param string $operator
   *   The comparison operator to use.
   *
   * @return TingSearchRequest
   *   Updated search request object.
   */
  public function withFieldFilter($name, $value, $operator = TingSearchFieldFilter::DEFAULT_OPERATOR) {
    return $this->withFilters([
      new TingSearchFieldFilter($name, $value, $operator),
    ]);
  }

}
