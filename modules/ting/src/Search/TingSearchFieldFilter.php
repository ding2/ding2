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
   * Default comparison operator.
   */
  const DEFAULT_OPERATOR = '=';

  /**
   * Equal comparison operator.
   */
  const OP_EQUAL = '=';

  /**
   * Greater than or equal to comparison operator.
   */
  const OP_GT_EQUAL = '>=';

  /**
   * Lesser than or equal to comparison operator.
   */
  const OP_LT_EQUAL = '<=';

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
   * Comparison operator to use.
   *
   * @var string
   */
  protected $operator;

  /**
   * TingSearchFieldFilter constructor.
   *
   * @param string $name
   *   The field name.
   * @param mixed $value
   *   Expected field-value.
   * @param string $operator
   *   The comparison operator to use.
   */
  public function __construct($name, $value, $operator = self::DEFAULT_OPERATOR) {
    $this->name = $name;
    $this->value = $value;
    $this->operator = $operator;
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
   * Returns the compare operator to use.
   *
   * @return string
   *   The operator.
   */
  public function getOperator() {
    return $this->operator;
  }

  /**
   * Check if an operator is an accepted comparison operator.
   *
   * @param string $operator
   *   Operator to check.
   *
   * @return bool
   *   TRUE if the operator is valid.
   */
  public static function validOperator($operator) {
    $accepted_operators = array(
      self::OP_EQUAL, self::OP_GT_EQUAL, self::OP_LT_EQUAL,
    );
    return in_array($operator, $accepted_operators);
  }

}
