<?php
/**
 * @file
 * The TingSearchFacetTerm class.
 */

namespace Ting\Search;

/**
 * Class that represents a single facet term and it's count.
 */
class TingSearchFacetTerm {
  /**
   * Term name.
   *
   * @var string
   */
  protected $name;

  /**
   * Count of how many matches of the term was encountered.
   *
   * @var int
   */
  protected $count;

  /**
   * TingSearchFacetTerm constructor.
   *
   * @param string $name
   *   Name of the term.
   *
   * @param int $count
   *   Count of how many matches of the term was encountered.
   */
  public function __construct($name, $count) {
    $this->name = $name;
    $this->count = $count;
  }

  /**
   * Get the name of the term.
   *
   * @return string
   *   The term name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Set the match count of the term.
   *
   * @return int
   *   The count.
   */
  public function getCount() {
    return $this->count;
  }
}
