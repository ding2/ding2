<?php
/**
 * @file
 * The ConnieSearchResult class.
 */

namespace Connie\Search;

use Ting\Search\TingSearchResultInterface;

class ConnieSearchResult implements TingSearchResultInterface {

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
    return [ConnieTingObjectCollection::getSingleCollection()];
  }
}
