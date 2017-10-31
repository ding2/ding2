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

  /**
   * TingSearchSort constructor.
   *
   * @param string $field
   *   Provider-specific name of the field sort by.
   *
   * @param string $direction
   *   TingSearchSort::DIRECTION_ASCENDING ||
   *   TingSearchSort::DIRECTION_DESCENDING.
   */
  public function __construct($field, $direction = self::DIRECTION_ASCENDING) {
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
