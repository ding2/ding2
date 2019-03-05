<?php
/**
 * @file
 * The NullSearchResult class.
 */

namespace Ting\Search;

/**
 * Class NullSearchResult
 *
 * Null object implementation of TingSearchResultInterface.
 *
 * @package Ting\Search
 */
class NullSearchResult implements TingSearchResultInterface {

  /**
   * @var \Ting\Search\TingSearchRequest
   */
  protected $searchRequest;

  /**
   * NullSearchResult constructor.
   *
   * @param TingSearchRequest $search_request
   *   The search request that produced the result.
   */
  public function __construct(TingSearchRequest $search_request = NULL) {
    $this->searchRequest = $search_request;
  }

  /**
   * {@inheritdoc}
   */
  public function getNumTotalObjects() {
    return 0;
  }

  /**
   * {@inheritdoc}
   */
  public function getNumCollections() {
    return 0;
  }

  /**
   * {@inheritdoc}
   */
  public function getTingEntityCollections() {
    return [];
  }

  /**
   * {@inheritdoc}
   */
  public function hasMoreResults() {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getSearchRequest() {
    return $this->searchRequest;
  }

  /**
   * {@inheritdoc}
   */
  public function getFacets() {
    return NULL;
  }
}
