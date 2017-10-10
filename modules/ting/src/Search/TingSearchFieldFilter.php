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
class TingSearchFieldFilter implements BooleanStatementInterface {

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
   * If NULL the field is a boolean field.
   *
   * @var mixed|NULL
   */
  protected $value;


  /**
   * The logic operator used to evaluate the field evaluation against the
   * previous statement.
   *
   * @see BooleanStatementInterface::OP_*
   *
   * @var string
   */
  protected $logicOperator;

  /**
   * TingSearchFieldFilter constructor.
   *
   * TODO BBS-SAL: Consider handling the $operator via an enum.
   * TODO BBS-SAL: If we end up needing to compare null-values the default for
   * $value needs to be a
   *
   * @param string $name
   *   The field name.
   *
   * @param mixed|TingSearchFieldFilter::MISSING_VALUE $value
   *   Field value, if omitted or set to TingSearchFieldFilter::MISSING_VALUE
   *   the field is treated as a boolean field that will be compared without an
   *   operator Eg:
   *   (myboofield AND anotherfield=123)
   *
   * @param string $operator
   *   Operator to use when comparing the field instance with a value.
   *
   * @param string $logic_operator
   *   Operator to use when comparing the evaluated field with a previous
   *   statement.
   */
  public function __construct($name, $value = self::BOOLEAN_FIELD_VALUE, $operator = '=', $logic_operator = BooleanStatementInterface::OP_AND) {
    $this->name = $name;
    $this->operator = $operator;
    $this->logicOperator = $logic_operator;
    $this->value = $value;
  }

  /**
   * {@inheritdoc}
   */
  public function getLogicOperator() {
    return $this->logicOperator;
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
