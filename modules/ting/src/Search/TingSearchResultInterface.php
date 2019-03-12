<?php
/**
 * @file
 * The TingSearchResultInterface interface.
 */

namespace Ting\Search;

/**
 * Interface TingSearchResultInterface
 *
 * @package Ting\Search
 */
interface TingSearchResultInterface {
  /**
   * Total number of elements in the search-result (regardless of limit).
   *
   * @return int
   *   The number of objects.
   */
  public function getNumTotalObjects();

  /**
   * Number of collections in the search-result.
   *
   * A Collection contains one or more objects.
   *
   * Note that this is limited by paging.
   *
   * @return int
   *   The number of collections.
   */
  public function getNumCollections();

  /**
   * Returns a list of the collections contained within this search result.
   *
   * Note that this is not entities but plain old PHP objects.
   *
   * @return \Ting\TingObjectCollectionInterface[]
   */
  public function getCollections();

  /**
   * Returns a list of loaded TingCollections.
   *
   * Notice that TingCollection is actually a collection of Ting Entities.
   *
   * @return \TingCollection[]
   *   Collections contained in the search result.
   */
  public function getTingEntityCollections();

  /**
   * Indicates whether the the search could yield more results.
   *
   * Eg. by increasing the count or page-number.
   *
   * @return bool
   *   TRUE if the search-provider could provide more results.
   */
  public function hasMoreResults();

  /**
   * The search request that produced the resulted.
   *
   * @return \Ting\Search\TingSearchRequest
   *   The search request.
   */
  public function getSearchRequest();

  /**
   * Facet matched in the result with term matches.
   *
   * The list is keyed by facet name.
   *
   * @return \Ting\Search\TingSearchFacet[]
   *   List of facets, empty if none were found.
   */
  public function getFacets();

}
