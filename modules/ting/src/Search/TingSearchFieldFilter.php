<?php
/**
 * @file
 * The TingSearchFieldFilter class.
 */

namespace Ting\Search;

/**
 * Class TingSearchFieldFilter
 *
 * Represents a provider-independent comparison between a field instance and a
 * value using an operator.
 *
 * @package Ting\Search
 */
class TingSearchFieldFilter {

  const BOOLEAN_FIELD_VALUE = self::class . '-MISSING-VALUE';

  /**
   * The field.
   *
   * @var string
   */
  protected $name;

  /**
   * Field value.
   *
   * If TingSearchFieldFilter::BOOLEAN_FIELD_VALUE the field is a boolean field.
   *
   * @var mixed|TingSearchFieldFilter::BOOLEAN_FIELD_VALUE
   */
  protected $value;

  /**
   * TingSearchFieldFilter constructor.
   *
   * @param string $name
   *   The field name.
   *
   * @param mixed|TingSearchFieldFilter::BOOLEAN_FIELD_VALUE $value
   *   Expected field-value, if omitted or set to
   *   TingSearchFieldFilter::BOOLEAN_FIELD_VALUE the field is treated as a
   *   boolean field that will be compared without an operator Eg:
   *   (myboolfield AND anotherfield=123)
   */
  public function __construct($name, $value = self::BOOLEAN_FIELD_VALUE) {
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

  /**
   * Whether this field can be evaluated by itself.
   *
   * @return bool
   *   TRUE if the field is boolean, FALSE if the operator and value is
   *   necessary to evaluate the field.
   */
  public function isBoolean() {
    return $this->getValue() === TingSearchFieldFilter::BOOLEAN_FIELD_VALUE;
  }
}
