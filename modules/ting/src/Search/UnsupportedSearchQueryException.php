<?php
/**
 * @file
 * The UnsupportedSearchQueryException class.
 */

namespace Ting\Search;

/**
 * Thrown when a search-provider detects an unsupported query.
 *
 * Eg. If a provider does not support joining statements involving multiple
 * fields with OR, it can throw this exception if such a query is encountered.
 */
class UnsupportedSearchQueryException extends SearchProviderException {

}
