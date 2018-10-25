<?php

namespace Ting\Search;

/**
 * Class TingSearchFieldFilter.
 *
 * Represents a provider-independent comparison between a field instance and a
 * value using an operator.
 *
 * @package Ting\Search
 */
class TingSearchFieldFilter implements FilterStatementInterface {

  /**
   * The field.
   *
   * @var string
   */
  protected $name;

  /**
   * Field value.
   *
   * @var mixed
   */
  protected $value;

  /**
   * TingSearchFieldFilter constructor.
   *
   * @param string $name
   *   The field name.
   * @param mixed $value
   *   Expected field-value.
   */
  public function __construct($name, $value) {
    $this->name = $name;
    $this->value = $value;
  }

  /**
   * Returns the name of the field.
   *
   * @return string
   *   The name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Returns the valued the field-instance will be compared to.
   *
   * @return mixed
   *   The value.
   */
  public function getValue() {
    return $this->value;
  }

}
