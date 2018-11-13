<?php
/**
 * @file
 * The TingSearchFacet class.
 */

namespace Ting\Search;

/**
 * Represents a Search facet and it's terms.
 *
 * @package Ting\Search
 */
class TingSearchFacet {

  /**
   * @var string
   */
  protected $name;

  /**
   * Terms in the facet.
   *
   * Used when the facet is a part of a search result.
   *
   * The list is keyed by term name.
   *
   * @var \Ting\Search\TingSearchFacetTerm[]
   */
  protected $terms = [];

  /**
   * TingSearchFacet constructor.
   *
   * @param string $name
   *   Name of the facet.
   *
   * @param TingSearchFacetTerm[] $terms
   *   Optional list of terms.
   */
  public function __construct($name, $terms = []) {
    $this->name = $name;
    // Set via setter to store the terms by their names.
    $this->setTerms($terms);
  }

  /**
   * Gets the name of the facet.
   *
   * @return string
   *   The name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Returns all term matches in the facet.
   *
   * A facet will only contain terms if it is a part of a search result.
   *
   * @return \Ting\Search\TingSearchFacetTerm[]
   *   The term matches in the facet keyed by name.
   */
  public function getTerms() {
    return $this->terms;
  }

  /**
   * Sets one or more terms matches from the facet encountered during searching.
   *
   * @param \Ting\Search\TingSearchFacetTerm[] $terms
   *   The list of terms, empty if none were found.
   */
  public function setTerms($terms) {
    $this->terms = [];
    // Make sure to store the terms keyed by their names.
    foreach ($terms as $term) {
      $this->terms[$term->getName()] = $term;
    }
  }

  /**
   * Adds a single term match to the facet.
   *
   * @param \Ting\Search\TingSearchFacetTerm $term
   *   The term.
   */
  public function addTerm($term) {
    $this->terms[$term->getName()] = $term;
  }
}
