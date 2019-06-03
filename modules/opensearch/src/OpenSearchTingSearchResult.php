<?php
/**
 * @file
 * The OpenSearchTingSearchResult class.
 */

namespace OpenSearch;


use Ting\Search\TingSearchFacet;
use Ting\Search\TingSearchFacetTerm;
use Ting\Search\TingSearchRequest;
use Ting\Search\TingSearchResultInterface;
use TingClientSearchResult;

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
  public $openSearchResult;

  /**
   * The query that produced the result.
   *
   * @var \Ting\Search\TingSearchRequest
   */
  protected $tingSearchRequest;

  /**
   * OpenSearchTingSearchResponse constructor.
   *
   * @param \TingClientSearchResult $open_search_result
   *   Embedded provider-specific search result.
   *
   * @param \Ting\Search\TingSearchRequest $search_request
   *   The query that should produce the result.
   */
  public function __construct(TingClientSearchResult $open_search_result, TingSearchRequest $search_request) {
    $this->openSearchResult = $open_search_result;
    $this->tingSearchRequest = $search_request;
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
  public function getNumCollections() {
    return $this->openSearchResult->numTotalCollections;
  }

  /**
   * {@inheritdoc}
   */
  public function getTingEntityCollections() {
    return $this->openSearchResult->collections;
  }

  /**
   * {@inheritdoc}
   */
  public function hasMoreResults() {
    // The raw value is 0/1 so cast.
    return (bool) $this->openSearchResult->more;
  }

  /**
   * {@inheritdoc}
   */
  public function getSearchRequest() {
    return $this->tingSearchRequest;
  }

  /**
   * {@inheritdoc}
   */
  public function getFacets() {
    $facets = [];

    // Bail out if we don't have any facets.
    if (empty($this->openSearchResult->facets)) {
      return $facets;
    }

    /** @var \TingClientFacetResult $open_search_facet */
    foreach ($this->openSearchResult->facets as $open_search_facet) {
      // For each facet, extract data on the facet itself and its terms.
      $facet = new TingSearchFacet($open_search_facet->name);

      $terms = [];
      foreach ($open_search_facet->terms as $term_name => $term_count) {
        $terms[] = new TingSearchFacetTerm($term_name, $term_count);
      }
      $facet->setTerms($terms);

      // Set the facet type, depending on it's name.
      switch ($facet->getName()) {
        case 'facet.date':
          $facet->setType($facet::TYPE_INTERVAL);
          break;
      }

      // Finish off by adding the facet to the list, keyed by its name as
      // required by the interface.
      $facets[$open_search_facet->name] = $facet;
    }

    return $facets;
  }
}
