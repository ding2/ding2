<?php
/**
 * @file
 * The BooleanStatementInterface interface.
 */

namespace Ting\Search;

/**
 * Describes a filters that can be combined with other files with logic
 * operations.
 *
 * The operation applies to the the previous filter. That is if the previous
 * filter was "A" and that specified "OR" as a filter and the current object is
 * "B" and has specified "AND" as operation. The arrangement will be.
 * A AND B
 * Notice that the logic-operation specified for the first operation is
 * ignored.
 *
 * @package Ting\Search
 */
interface BooleanStatementInterface {

  // TODO: This could be an enum.
  const OP_OR = 'OR';
  const OP_AND = 'AND';

  /**
   * The logic operation.
   *
   * See TingSearchBooleanStatementInterface::OP_*
   *
   * @return string
   *   The logic operation.
   */
  public function getLogicOperator();
}
