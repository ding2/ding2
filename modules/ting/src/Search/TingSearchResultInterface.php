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
  // TODO BBS-SAL: this interface might need to built out, see
  // https://opensource.dbc.dk/services/open-search-web-service for details on
  // what Open Search returns, and TingClientSearchResult for the current
  // Ting client response.

  /**
   * Total number of elements in the search-result (regardless of limit).
   *
   * TODO BBS-SAL: Consider renaming this hits() - see
   * https://github.com/rvk-utd/ding2/pull/25#discussion_r133373710
   *
   * @return int
   *   The number of objects.
   */
  public function getNumTotalObjects();

  /**
   * Total number of collections in the search-result.
   *
   * A Collection contains one or more objects.
   *
   * TODO BBS-SAL: Consider renaming this count() - see
   * https://github.com/rvk-utd/ding2/pull/25#discussion_r133373710
   *
   * @return int
   *   The number of collections.
   */
  public function getNumTotalCollections();

  /**
   * Returns a list of loaded TingCollections.
   *
   * Notice that TingCollection is actually a collection of Ting Entities.
   *
   * @return \TingCollection[]
   *   Collections contained in the search result.
   */
  public function getTingEntityCollections();

}
