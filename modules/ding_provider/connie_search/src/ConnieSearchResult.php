<?php
/**
 * @file
 * The ConnieSearchResult class.
 */

namespace Connie\Search;

use Ting\Search\TingSearchFacet;
use Ting\Search\TingSearchFacetTerm;
use Ting\Search\TingSearchResultInterface;

/**
 * Dummy implementation of a search result.
 *
 * Implemented for testing purposes.
 */
class ConnieSearchResult implements TingSearchResultInterface {

  protected $query;

  /**
   * ConnieSearchResult constructor.
   *
   * @param \Ting\Search\TingSearchRequest $query
   *   The query that should produce the result.
   */
  public function __construct($query) {
    $this->query = $query;
  }

  /**
   * Total number of elements in the search-result (regardless of limit).
   *
   * @return int
   *   The number of objects.
   */
  public function getNumTotalObjects() {
    return 1;
  }

  /**
   * Total number of collections in the search-result.
   *
   * A Collection contains one or more objects.
   *
   * @return int
   *   The number of collections.
   */
  public function getNumTotalCollections() {
    return 1;
  }

  /**
   * Returns a list of loaded TingCollections.
   *
   * Notice that TingCollection is actually a collection of Ting Entities.
   *
   * @return \TingCollection[]
   *   Collections contained in the search result.
   */
  public function getTingEntityCollections() {
    return [ConnieTingObjectCollection::getSingleCollection('object1')];
  }

  /**
   * Indicates whether the the search could yield more results.
   *
   * Eg. by increasing the count or page-number.
   *
   * @return bool
   *   TRUE if the search-provider could provide more results.
   */
  public function hasMoreResults() {
    return FALSE;
  }

  /**
   * The search request that produced the resulted.
   *
   * @return \Ting\Search\TingSearchRequest
   *   The search request.
   */
  public function getSearchRequest() {
    return $this->query;
  }

  /**
   * Facet matched in the result with term matches.
   *
   * @return \Ting\Search\TingSearchFacet[]
   *   List of facets, empty if none were found.
   */
  public function getFacets() {
    $terms = [
      new TingSearchFacetTerm('term1', 42),
      new TingSearchFacetTerm('term2', 2),
      new TingSearchFacetTerm('term3', 3),
    ];
    $facet = new TingSearchFacet('facet-name', $terms);
    return [$facet->getName() => $facet];
  }

}
