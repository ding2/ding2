<?php
/**
 * @file
 * The OpenSearchTingSearchResult class.
 */

namespace OpenSearch;


use Ting\Search\TingSearchResultInterface;

/**
 * Class OpenSearchTingSearchResult
 *
 * Wraps a TingClientSearchResult to provide integration to Ding.
 *
 * @package OpenSearch
 */
class OpenSearchTingSearchResult implements TingSearchResultInterface {

  /**
   * The actual search-result from Ting Client.
   *
   * @var \TingClientSearchResult
   */
  protected $openSearchResult;

  /**
   * The query that produced the result.
   *
   * @var \Ting\Search\TingSearchRequest
   */
  protected $query;

  /**
   * OpenSearchTingSearchResponse constructor.
   *
   * @param \TingClientSearchResult $open_search_result
   *   Embedded provider-specific search result.
   *
   * @param \Ting\Search\TingSearchRequest $query
   *   The query that should produce the result.
   */
  public function __construct($open_search_result, $query) {
    $this->openSearchResult = $open_search_result;
    $this->query = $query;
  }

  /**
   * {@inheritdoc}
   */
  public function getNumTotalObjects() {
    return $this->openSearchResult->numTotalObjects;
  }

  /**
   * {@inheritdoc}
   */
  public function getNumTotalCollections() {
    return $this->openSearchResult->numTotalCollections;
  }

  /**
   * {@inheritdoc}
   */
  public function getTingEntityCollections() {
    return $this->openSearchResult->collections;
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
    // The raw value is 0/1 so cast.
    return (bool) $this->openSearchResult->more;
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
}
