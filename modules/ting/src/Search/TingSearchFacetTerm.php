<?php
/**
 * @file
 * The TingSearchFacetTerm class.
 */

namespace Ting\Search;


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
   * Sets the name of the term.
   *
   * @param string $name
   *   The term name.
   */
  public function setName($name) {
    $this->name = $name;
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

  /**
   * Sets the match count.
   *
   * @param int $count
   *   The count.
   */
  public function setCount($count) {
    $this->count = $count;
  }
}
