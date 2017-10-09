<?php

/**
 * @file
 * The TingSearchStrategyInterface interface.
 */

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

  /**
   * Returns a mapping of common field name to a provider-specific names.
   *
   * @return array
   *   Associative array of provider-specific names keyed by
   *   TingSearchCommonFields::* field names.
   */
  public function mapCommonFields();
}
