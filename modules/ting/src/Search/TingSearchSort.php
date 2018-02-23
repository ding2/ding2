<?php
/**
 * @file
 * The TingSearchSort class.
 */

namespace Ting\Search;

/**
 * Class TingSearchSort
 *
 * Represents a provider-independent sort-order for a query.
 *
 * @package Ting\Search
 */
class TingSearchSort {
  protected $direction;
  protected $field;

  // TODO: Could be an enum.
  const DIRECTION_ASCENDING = 'asc';
  const DIRECTION_DESCENDING = 'desc';
  // "NONE" should be used in situations where the it doesn't make sense to
  // specify a direction for a sort. This can be necessary in cases where the
  // provider simply does not support a direction for the sort, or where it
  // does not make sense ie. a random sort.
  const DIRECTION_NONE = '_none';

  /**
   * TingSearchSort constructor.
   *
   * @param string $field
   *   Provider-specific name of the field sort by.
   *
   * @param string $direction
   *   TingSearchSort::DIRECTION_*.
   */
  public function __construct($field, $direction = self::DIRECTION_NONE) {
    $this->direction = $direction;
    $this->field = $field;
  }

  /**
   * Gets the sort direction.
   *
   * @return string
   *   The direction.
   */
  public function getDirection() {
    return $this->direction;
  }

  /**
   * Gets the provider-specific name of the field sort by.
   *
   * @return string
   *   The name.
   */
  public function getField() {
    return $this->field;
  }
}
