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
   * OpenSearchTingSearchResponse constructor.
   *
   * @var \TingClientSearchResult $open_search_result
   */
  public function __construct($open_search_result) {
    $this->openSearchResult = $open_search_result;
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
}
