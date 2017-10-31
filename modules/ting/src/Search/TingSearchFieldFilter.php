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
   * The operator used to compare the field instance and value.
   *
   * @var string
   */
  protected $operator;

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
   * TODO BBS-SAL: Consider handling the $operator via an enum.
   *
   * @param string $name
   *   The field name.
   *
   * @param mixed|TingSearchFieldFilter::BOOLEAN_FIELD_VALUE $value
   *   Field value, if omitted or set to
   *   TingSearchFieldFilter::BOOLEAN_FIELD_VALUE the field is treated as a
   *   boolean field that will be compared without an operator Eg:
   *   (myboolfield AND anotherfield=123)
   * @param string $operator
   *   Operator to use when comparing the field instance with a value.
   */
  public function __construct($name, $value = self::BOOLEAN_FIELD_VALUE, $operator = '=') {
    $this->name = $name;
    $this->operator = $operator;
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
   * Returns the operator to be used when evaluating the field.
   *
   * @return string
   *   The operator.
   */
  public function getOperator() {
    return $this->operator;
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
