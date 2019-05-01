<?php

namespace Ting\Search;

/**
 * Groups one or more boolean statements together.
 *
 * The statements are joined by a boolean operator.
 */
class BooleanStatementGroup implements BooleanStatementInterface, FilterStatementInterface {

  /**
   * The grouped statements.
   *
   * @var TingSearchFieldFilter[]
   */
  protected $statements = [];

  /**
   * The operator to use if this group comes after another.
   *
   * @var string
   */
  protected $logicOperator;

  /**
   * Construct a BooleanStatementGroup.
   *
   * The statements is one or more groups or fields and will be joined together
   * in a single group via the $logic_operator operator.
   *
   * @param TingSearchFieldFilter[] $statements
   *   One or more instances of \Ting\Search\TingSearchFieldFilter.
   * @param string $logic_operator
   *   A TingSearchBooleanStatementInterface::OP_* operation.
   */
  public function __construct(array $statements, $logic_operator = BooleanStatementInterface::OP_AND) {
    // Let callers of getStatements() rely on getting at least one statement.
    if (empty($statements)) {
      throw new \InvalidArgumentException("Group must contain at least one statement.");
    }

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
   * @return TingSearchFieldFilter[]
   *   One or more instances of TingSearchFieldFilter.
   */
  public function &getStatements() {
    return $this->statements;
  }

  /**
   * Add a statement to the group.
   *
   * @param mixed $statements
   *   One or more implementations \Ting\Search\TingSearchFieldFilter.
   */
  public function add($statements) {
    if (!is_array($statements)) {
      $statements = [$statements];
    }
    $this->statements = $statements;
  }

}
