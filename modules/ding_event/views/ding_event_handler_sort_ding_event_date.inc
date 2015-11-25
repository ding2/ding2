<?php

/**
 * @file
 * Definition of ding_event_handler_sort_ding_event_date.
 */

/**
 * Sort handler for Ding events date.
 *
 * @ingroup views_sort_handlers
 */
class ding_event_handler_sort_ding_event_date extends views_handler_sort_date {
  /**
   * Called to add the sort to a query.
   */
  function query() {
    $this->ensure_my_table();
    $this->table_alias = 'field_data_field_ding_event_date';
    $this->real_field = 'field_ding_event_date_value';
    switch ($this->options['granularity']) {
      case 'second':
      default:
        $alias = $this->table_alias . '.' . $this->real_field;
        $this->query->orderby[] = array(
          'field' => "CASE
  WHEN {$alias} < NOW() THEN NOW()
  ELSE {$alias}
END",
          'direction' => strtoupper($this->options['order']),
        );
        return;
      case 'minute':
        $formula = views_date_sql_format('YmdHi', "$this->table_alias.$this->real_field");
        break;
      case 'hour':
        $formula = views_date_sql_format('YmdH', "$this->table_alias.$this->real_field");
        break;
      case 'day':
        $formula = views_date_sql_format('Ymd', "$this->table_alias.$this->real_field");
        break;
      case 'month':
        $formula = views_date_sql_format('Ym', "$this->table_alias.$this->real_field");
        break;
      case 'year':
        $formula = views_date_sql_format('Y', "$this->table_alias.$this->real_field");
        break;
    }

    // Add the field.
    $this->query->add_orderby(NULL, $formula, $this->options['order'], $this->table_alias . '_' . $this->field . '_' . $this->options['granularity']);
  }
}
