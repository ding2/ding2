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
    try {
      return ding_provider_invoke('search', 'search', $query);
    }
    catch (UnsupportedSearchQueryException $e) {
      watchdog_exception('ting', $e, 'The provider did not support the query');
      return new NullSearchResult($query);
    }
    catch (SearchProviderException $e) {
      watchdog_exception('ting', $e, 'Error while searching');
      return new NullSearchResult($query);
    }
  }

  /**
   * Mapping of common fields used in conditions to provider-specific names.
   *
   * @return array
   *   Associative array of provider-specific names keyed by
   *   TingSearchCommonFields::* field names.
   */
  // TODO BBS-SAL Remove this function and the provider call. It is only used
  // by OpenSearch and can be kept within the OpenSearchStatementGroupRender.
  public function mapCommonFields() {
    return ding_provider_invoke('search', 'map_common_condition_fields');
  }
}
