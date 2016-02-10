<?php

/**
 * @file
 * Definition of ding_event_handler_sort_ding_event_date.
 *
 * This handler replaces default sorting of date. If lower date is lesser than
 * current date then it replaced to current date.
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

    $mapping = array(
      'minute' => 'YmdHi',
      'hour' => 'YmdH',
      'day' => 'Ymd',
      'month' => 'Ym',
      'year' => 'Y',
    );
    $alias = $this->table_alias . '.' . $this->real_field;
    if (!empty($mapping[$this->options['granularity']])) {
      $formula = views_date_sql_format($mapping[$this->options['granularity']], $alias);
      $this->query->add_orderby(NULL, $formula, $this->options['order'], $this->table_alias . '_' . $this->field . '_' . $this->options['granularity']);
    }
    else {
      $this->query->orderby[] = array(
        'field' => "CASE WHEN {$alias} < NOW() THEN NOW() ELSE {$alias} END",
        'direction' => strtoupper($this->options['order']),
      );
    }
  }
}
