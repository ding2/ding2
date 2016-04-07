<?php

/**
 * @file
 * Definition of views_handler_sort_group_by_numeric.
 */

/**
 * Handler for GROUP BY on simple numeric fields.
 *
 * @ingroup views_sort_handlers
 */
class views_handler_sort_group_by_loan_history extends views_handler_sort_group_by_numeric {

  /**
   * Default init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // Initialize the original handler.
    $this->handler = views_get_handler($options['table'], $options['field'], 'sort');
    $this->handler->init($view, $options);
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();

    $params = array(
      'function' => $this->options['group_type'],
    );
  }

  function ui_name($short = FALSE) {
    return $this->get_field(parent::ui_name($short));
  }

  /**
   * Creates a new temporary table from a Drupal table definition.
   *
   * @param (string) $table
   *   A Schema API table definition array.
   *
   * @return
   *   The name of the temporary table.
   */
  function db_create_temporary_table($table) {
    static $index = 0;

    $connection = Database::getConnection();
    $schema = $connection->schema();
    $method = new ReflectionMethod($schema, 'createTableSql');
    $method->setAccessible(TRUE);

    $tablename = "_db_temporary_" . $index++;
    $statements = $method->invoke($schema, $tablename, $table);
    $statements[0] = preg_replace('/^CREATE TABLE /', 'CREATE TEMPORARY TABLE ', $statements[0]);
    foreach ($statements as $statement) {
      $connection->query($statement);
    }
    return $tablename;
  }
}
