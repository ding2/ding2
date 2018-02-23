<?php

namespace Ting\Search;

/**
 * Tag interface for filter statements.
 *
 * Implementations of this interface is used as entries in a list of filter
 * statements in a Ting Query. How the individual implementations are processed
 * when the query is executed can vary greatly from provider to provider and
 * adding a new type of filter will thus require changes to each search
 * provider.
 *
 * Implementing this interface signals that the implementor has done whatever
 * work is necessary to make all relevant search providers compatible with the
 * new filter type.
 *
 * Search providers accepting implementations of this interface should likewise
 * check up front for compatibility and throw an UnsupportedSearchQueryException
 * upon encountering an unsupported type of filter.
 *
 * Current implementations of this interface:
 * <ul>
 *   <li> \Ting\Search\BooleanStatementGroup </li>
 *   <li> \Ting\Search\TingSearchFieldFilter </li>
 * </ul>
 *
 * @package Ting\Search
 */
interface FilterStatementInterface {

}
