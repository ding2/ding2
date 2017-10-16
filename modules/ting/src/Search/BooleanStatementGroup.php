<?php
/**
 * @file
 * The BooleanStatementGroup class
 */

/**
 * Groups one or more boolean statements together. The statements are joined by
 * a boolean operator.
 */
namespace Ting\Search;

/**
 * Class BooleanStatementGroup
 *
 * Joins multiple logic statements into a group.
 *
 * @package Ting\Search
 */
class BooleanStatementGroup implements BooleanStatementInterface {

  /**
   * The grouped statements.
   *
   * @var mixed[]
   */
  protected $statements = [];

  /**
   * The operator to use if this group comes after another.
   * @var string
   */
  protected $logicOperator;

  /**
   * Construct a BooleanStatementGroup.
   *
   * The statements is one or more groups or fields and will be joined together
   * in a single group via the $logic_operator operator.
   *
   * @param mixed[] $statements
   *   Instances of \Ting\Search\BooleanStatementGroup and
   *   \Ting\Search\TingSearchFieldFilter
   *
   * @param string $logic_operator
   *   A TingSearchBooleanStatementInterface::OP_* operation.
   */
  public function __construct(array $statements, $logic_operator = BooleanStatementInterface::OP_AND) {
    $this->add($statements);
    $this->logicOperator = $logic_operator;
  }

  /**
   * {@inheritdoc}
   */
  public function getLogicOperator() {
    return $this->logicOperator;
  }

  /**
   * Set the logic-operator used to join the members of the group.
   *
   * @param string $logic_operator
   *   A TingSearchBooleanStatementInterface::OP_* operation.
   */
  public function setLogicOperator($logic_operator) {
    $this->logicOperator = $logic_operator;
  }

  /**
   * The grouped statements.
   *
   * @return mixed[]
   *   The statements, instances of BooleanStatementGroup and
   *   TingSearchFieldFilter.
   */
  public function getStatements() {
    return $this->statements;
  }

  /**
   * Add a statement to the group.
   *
   * @param mixed[] $statements
   *   One or more implementations of \Ting\Search\BooleanStatementGroup and
   *   \Ting\Search\TingSearchFieldFilter.
   */
  public function add($statements) {
    if (!is_array($statements)) {
      $statements = [$statements];
    }
    foreach ($statements as $statement) {
      if ($statement instanceof self || $statement instanceof TingSearchFieldFilter) {
        $this->statements[] = $statement;
      }
      else {
        throw new \InvalidArgumentException(
          "Unsupported type, only BooleanStatementInterface and TingSearchFieldFilter is supported"
        );
      }
    }
  }
}
