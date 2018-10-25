<?php

namespace Ting\Search;

/**
 * Implementation of a provider-specific strategy.
 *
 * @package Ting\Search
 */
interface TingSearchStrategyInterface {

  /**
   * Performs a search.
   *
   * @param \Ting\Search\TingSearchRequest $query
   *   The search-query to be performed.
   *
   * @return \Ting\Search\TingSearchResultInterface
   *   The result of performing the search.
   */
  public function executeSearch($query);

}
