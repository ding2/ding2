<?php

/**
 * @file
 *
 * Definition of ting_search_context_handler_filter_node_ratings
 */

/**
 * Handler to filter nodes based on the contexts they're rated in.
 *
 * To solve the many-to-one problem (one node can have many ratings), we use a
 * sub-query that is inserted into the main query. This is an easy, but
 * probably abit ineffecient, solution, because we avoid having
 * to join with the context table in the main query, which will produce
 * duplicate nodes if the node is rated more than once.
 * We tried to use views_handler_filter_many_to_one wich uses the many-to-one
 * helper, but it was just too complicated and the sub-query solution suits our
 * needs perfectly.
 */
class ting_search_context_handler_filter_node_ratings extends views_handler_filter_in_operator {

  /**
   * Override the operators
   *
   * For now we support the following operators:
   * - 'or'       : Nodes with a rating in one or more of the selected contexts.
   * - 'not'      : Nodes that aren't rated in any of the selected contexts.
   * - 'empty'    : Nodes that have no rating at all.
   * - 'not empty': Nodes that have at least one rating.
   *
   * These are pretty simple to implement. We might add more advanced ones in
   * the future.
   */
  function operators() {
    $operators = array(
      'or' => array(
        'title' => t('Rated in one of'),
        'short' => t('in'),
        'short_single' => t('='),
        'method' => 'op_rated_simple',
        'values' => 1,
      ),
      // Needs some work
      /*'and' => array(
        'title' => t('Rated in all of'),
        'short' => t('in'),
        'short_single' => t('='),
        'method' => 'op_rated_simple',
        'values' => 1,
      ),*/
      'not' => array(
        'title' => t('Not rated in any of'),
        'short' => t('not in'),
        'short_single' => t('<>'),
        'method' => 'op_rated_simple',
        'values' => 1,
      ),
      'empty' => array(
        'title' => t('Not rated at all'),
        'short' => t('empty'),
        'method' => 'op_rated_empty',
        'values' => 1,
      ),
      'not empty' => array(
        'title' => t('Rated in any'),
        'short' => t('not empty'),
        'method' => 'op_rated_empty',
        'values' => 1,
      ),
    );
    return $operators;
  }

  /**
   * The filter values. In this case Ting search contexts.
   */
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    // Override title in the admin UI.
    $this->value_title = t('Select context(s)');

    // Build the value options array with our contexts from the database.
    $contexts = ting_search_context_get_all_contexts();
    $context_options = array();
    foreach ($contexts as $context) {
      $context_options[$context->context_id] = $context->name;
    }

    $this->value_options = $context_options;
  }

  /**
   * Filtering method that handles the simple cases of 'or' and 'not'.
   */
  function op_rated_simple() {
    // We need a value here.
    if (empty($this->value)) {
      return;
    }

    // Determine which operator to use.
    $operator = 'IN';
    if ($this->operator == 'not') {
      $operator = 'NOT IN';
    }

    $this->ensure_my_table();

    // Fetch nids of nodes rated in the selected contexts.
    $subquery = db_select('ting_search_context_nodes_rated', 'nr');
    $subquery->addField('nr', 'nid');
    $subquery->condition('nr.context_id', $this->value, 'IN');

    // Insert our subquery into the view's main query.
    $this->_add_subquery($subquery, $operator);
  }

  function op_rated_empty() {
    // Determine the operator.
    $operator = 'IN';
    if ($this->operator == 'empty') {
      $operator = 'NOT IN';
    }

    $this->ensure_my_table();

    // Fetch nids of nodes in the ratings table.
    $subquery = db_select('ting_search_context_nodes_rated', 'nr');
    $subquery->addField('nr', 'nid');

    $this->_add_subquery($subquery, $operator);
  }

  /**
   * TODO: Doesn't work yet. Will need multiple joins??
   */
  function op_rated_advanced() {
    if (empty($this->value)) {
      return;
    }

    $this->ensure_my_table();

    $subquery = db_select('ting_search_context_nodes_rated', 'nr');
    $subquery->addField('nr', 'nid');
    foreach ($this->value as $context_id) {
      $subquery->condition('nr.context_id', $context_id);
    }

    $this->_add_subquery($subquery, $operator);
  }

  function _add_subquery($subquery, $operator) {
    $this->query->add_where(
      $this->options['group'],
      "$this->table_alias.$this->real_field",
      $subquery,
      $operator
    );
  }

}
