<?php

namespace OpenSearch;

use Ting\Search\BooleanStatementGroup;
use Ting\Search\BooleanStatementInterface;
use Ting\Search\TingSearchCommonFields;
use Ting\Search\TingSearchFieldFilter;
use Ting\Search\TingSearchRawFilter;
use Ting\Search\TingSearchStrategyInterface;

/**
 * Recursively renders a statement group.
 *
 * @package Ting\Search
 */
class OpenSearchStatementGroupRender {

  /**
   * Map between TingSearchCommonFields fields and opensearch counterparts.
   *
   * @var array
   */
  protected $commonFieldMapping = [];

  /**
   * The strategy to use when interfacing with the search provider.
   *
   * @var \Ting\Search\TingSearchStrategyInterface
   */
  protected $providerStrategy;

  /**
   * StatementGroupRender constructor.
   *
   * @param \Ting\Search\TingSearchStrategyInterface $provider_strategy
   *   The strategy to use when interfacing with the search provider.
   * @param array $common_field_mapping
   *   Optional mapping between TingSearchCommonFields::* fields and their
   *   opensearch-specific counterparts. This mapping should mainly be specified
   *   during tests as it will default to a standard mapping that should work in
   *   most cases.
   */
  public function __construct(TingSearchStrategyInterface $provider_strategy, array $common_field_mapping = []) {
    $this->providerStrategy = $provider_strategy;

    // Override field mapping if specified.
    $this->commonFieldMapping = count($common_field_mapping) === 0 ? [
      TingSearchCommonFields::ACQUISITION_DATE => 'acquisitionDate',
      TingSearchCommonFields::AUTHOR => 'facet.creator',
      TingSearchCommonFields::CATEGORY => 'facet.category',
      TingSearchCommonFields::LANGUAGE => 'facet.language',
      TingSearchCommonFields::MATERIAL_TYPE => 'facet.type',
      TingSearchCommonFields::SUBJECT => 'facet.subject',
    ] : $common_field_mapping;
  }

  /**
   * Recursively renders a statement group into a string.
   *
   * @param \Ting\Search\BooleanStatementGroup $group
   *   The group to render.
   *
   * @return string
   *   The rendered group, empty string if the group is empty.
   *
   * @throws \InvalidArgumentException
   *   In case the group contains invalid members.
   */
  public function renderGroup(BooleanStatementGroup $group) {
    return $this->walk($group);
  }

  /**
   * Renders a list of statements into a single string statement.
   *
   * This is a helper-function that warps the list in a single group before
   * rendering it.
   *
   * @param \Ting\Search\FilterStatementInterface[] $statements
   *   The list of statements to render.
   * @param string $logic_operator
   *   A TingSearchBooleanStatementInterface::OP_* operation.
   *
   * @return string
   *   The rendered group, empty string if the group is empty.
   *
   * @throws \InvalidArgumentException
   *   In case the group contains invalid members.
   */
  public function renderStatements(array $statements, $logic_operator = BooleanStatementInterface::OP_AND) {
    return $this->renderGroup(new BooleanStatementGroup($statements, $logic_operator));
  }

  /**
   * Recursively process the group.
   *
   * @param \Ting\Search\BooleanStatementGroup $group
   *   The group to be rendered.
   * @param string $rendered_statement
   *   The rendered statement as it currently looks. The statement is passed by
   *   refrence and modifications are made during the traversal.
   *
   * @return string
   *   The rendered statement.
   *
   * @throws \InvalidArgumentException
   *   In case the group contains invalid members.
   */
  protected function walk(BooleanStatementGroup $group, &$rendered_statement = NULL) {
    // If this is the initial call to walk, take not of it so that we can treat
    // the outermost group differently. Eg. it should not have parenthesises
    // around it.
    if ($rendered_statement === NULL) {
      $is_outermost_group = TRUE;
      $rendered_statement = '';
    }
    else {
      $is_outermost_group = FALSE;
    }

    // We keep track of the index of the element so that we can treat the first
    // and last element differently.
    $statement_index = 0;
    $statements = $group->getStatements();
    foreach ($statements as $statement) {
      // Start of group with more than 1 element, open parenthesis.
      if (!$is_outermost_group && $statement_index === 0 && count($statements) > 1) {
        $rendered_statement .= '(';
      }

      // Add joining logic operator if we're not at the first element.
      if ($statement_index > 0) {
        // TODO: This could be an enum.
        $rendered_statement .= ' ' . $group->getLogicOperator() . ' ';
      }

      // We're at another group, recurse.
      if ($statement instanceof BooleanStatementGroup) {
        $this->walk($statement, $rendered_statement);
      }
      // If we have a raw filter then add it directly.
      elseif ($statement instanceof TingSearchRawFilter) {
        $rendered_statement .= $statement->getFilter();
      }
      // If we're at a field, render it.
      elseif ($statement instanceof TingSearchFieldFilter) {
        // Notice, this may be empty if the field is not supported in which
        // case we'll end up with empty parenthesises.
        $rendered_statement .= $this->renderField($statement);
      }
      else {
        throw new \InvalidArgumentException('Hit unexpected element-type: ' . print_r($statement, TRUE));
      }

      // Last element in group of more than 1 element, close parenthesis.
      if (!$is_outermost_group && $statement_index > 0 && $statement_index === (count($statements) - 1)) {
        $rendered_statement .= ')';
      }
      $statement_index++;
    }

    // Even though the statement is passed around by reference we still return
    // it to make it simpler for the outermost caller to just call walk()
    // without passing it an empty statement.
    return $rendered_statement;
  }

  /**
   * Render a field.
   *
   * @param \Ting\Search\TingSearchFieldFilter $field
   *   The filter.
   *
   * @return string
   *   The rendered field. Empty string if the field is a common field not
   *   supported by the current search-provider.
   */
  protected function renderField(TingSearchFieldFilter $field) {
    if (in_array($field->getName(), TingSearchCommonFields::getAll(), TRUE)) {
      if (isset($this->commonFieldMapping[$field->getName()])) {
        $field_name = $this->commonFieldMapping[$field->getName()];
      }
      else {
        // If the field is a common field and the provider does not support it
        // we ignore it silently.
        return '';
      }
    }
    else {
      // This is a provider-specific field, use the raw name.
      $field_name = $field->getName();
    }

    // Very simpel quotes. Enclose everything in double-quotes, and escape any
    // double-quotes in the value.
    $quoted_field = '"' . str_replace('"', '\"', $field->getValue()) . '"';

    // Render the full field with operator and value.
    return $field_name . $field->getOperator() . $quoted_field;
  }

}
