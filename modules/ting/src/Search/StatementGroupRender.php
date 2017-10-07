<?php
/**
 * @file
 * The StatementGroupRender class.
 */

namespace Ting\Search;

/**
 * Class TingFilterGroupRendere
 * Recursivly renders a statement group
 *
 * @package Ting\Search
 */
class StatementGroupRender {

  // Provider-specific mapping, intialized during field rendering.
  protected static $commonFieldMapping = NULL;

  /**
   * Recursively renders a statement group into a string.
   *
   * @param \Ting\Search\BooleanStatementGroup $group
   *   The group to render.
   *
   * @return string
   *   The rendered group, empty string if the group is empty.
   *
   * @throws \Exception
   *   In case the group contains invalid members.
   */
  public static function renderGroup($group) {
    return self::walk($group);
  }

  /**
   * Renders a list of statements into a single string statement.
   *
   * This is a helper-function that warps the list in a single group before
   * rendering it.
   *
   * @param \Ting\Search\BooleanStatementInterface[] $statements
   *   The list of statements to render.
   *
   * @return string
   *   The rendered group, empty string if the group is empty.
   *
   * @throws \Exception
   *   In case the group contains invalid members.
   */
  public static function renderStatements($statements) {
    return self::renderGroup(new BooleanStatementGroup($statements));
  }

  /**
   * Recursively process the group.
   *
   * @param \Ting\Search\BooleanStatementGroup $group
   *   The group to be rendered.
   *
   * @param string                             $rendered_statement
   *   The rendered statement as it currently looks. The statement is passed by
   *   refrence and modifications are made during the traversal.
   *
   * @return string
   *   The rendered statement.
   *
   * @throws \InvalidArgumentException
   *   In case the group contains invalid members.
   */
  protected static function walk($group, &$rendered_statement = NULL) {
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
        $rendered_statement .= ' ' . $statement->getLogicOperator() . ' ';
      }

      // We're at another group, recurse.
      if ($statement instanceof BooleanStatementGroup) {
        self::walk($statement, $rendered_statement);
      }
      // If we're at a field, render it.
      elseif ($statement instanceof TingSearchFieldFilter) {
        // Notice, this may be empty if the field is not supported in which
        // case we'll end up with empty parenthesises.
        $rendered_statement .= self::renderField($statement);

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
   * @param TingSearchFieldFilter $field
   *   The filter.
   *
   * @return string
   *   The rendered field. Empty string if the field is a common field not
   *   supported by the current search-provider.
   */
  protected static function renderField($field) {
    if (self::$commonFieldMapping === NULL) {
      self::$commonFieldMapping = ding_provider_invoke('search', 'map_common_fields');
    }
    // TODO BBS-SAL: use provider to map common fields and maybe also to do the
    // full render.
    // TODO BBS-SAL: escape field value - again using the provider.

    // Map the field if it is a common-field.
    if (TingSearchCommonFields::isCommonField($field->getName())) {
      if (isset(self::$commonFieldMapping[$field->getName()])) {
        $field_name = self::$commonFieldMapping[$field->getName()];
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
    return $field_name . $field->getOperator() . $field->getValue();
  }
}
