<?php
/**
 * The BooleanStatementGroup class.
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
   * @var \Ting\Search\BooleanStatementInterface[]
   */
  protected $statements = [];

  /**
   * The operator to use if this group comes after another.
   * @var string
   */
  protected $logicOperator;

  /**
   * BooleanStatementGroup constructor.
   *
   * @param \Ting\Search\TingSearchFieldFilter[] $statements
   *   The grouped statements
   *
   * @param string                               $logic_operator
   *   A TingSearchBooleanStatementInterface::OP_* operation.
   */
  public function __construct(array $statements, $logic_operator = BooleanStatementInterface::OP_AND) {
    $this->statements = $statements;
    $this->logicOperator = $logic_operator;
  }

  /**
   * {@inheritdoc}
   */
  public function getLogicOperator() {
    return $this->logicOperator;
  }

  /**
   * The grouped statements.
   *
   * @return \Ting\Search\BooleanStatementInterface[]
   *   The statements.
   */
  public function getStatements() {
    return $this->statements;
  }

  /**
   * Add a statement to the group.
   *
   * @param \Ting\Search\BooleanStatementInterface $statement
   *   The statement.
   */
  public function add(BooleanStatementInterface $statement) {
    $this->statements[] = $statement;
  }
}
