<?php
/**
 * @file
 * The DingProviderStrategy class.
 */

namespace Ting\Search;

/**
 * Class DingProviderStrategy
 *
 * Searches using a Ding Search provider.
 *
 * @package Ting\Search
 */
class DingProviderStrategy implements TingSearchStrategyInterface {

  /**
   * Performs a search using a Search Provider.
   *
   * @param \Ting\Search\TingSearchRequest $query
   *   The search-query to be performed.
   *
   * @return \Ting\Search\TingSearchResultInterface
   *   The result of performing the search.
   */
  public function executeSearch($query) {
    return ding_provider_invoke('search', 'search', $query);
  }
}
