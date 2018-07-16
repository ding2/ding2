<?php

namespace Ting\Search;

/**
 * Class TingSearchRawFilter.
 *
 * Represents a raw textual representation of a filter. Since such filters may
 * depend on features, syntax etc. that a specific to a individual provider they
 * are usually not provider dependant.
 *
 * @package Ting\Search
 */
class TingSearchRawFilter implements FilterStatementInterface {

  /**
   * The textual representation of the filter.
   *
   * @var string
   */
  protected $filter;

  /**
   * TingSearchRawFilter constructor.
   *
   * @param $filter
   *  A textual representation of the filter.
   */
  public function __construct($filter) {
    $this->filter = $filter;
  }

  /**
   * Returns the textual representation of the filter.
   *
   * @return string
   *   The textual representation of the filter.
   */
  public function getFilter() {
    return $this->filter;
  }

}
