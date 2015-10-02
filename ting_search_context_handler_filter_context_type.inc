<?php

/**
 * @file
 *
 * Definition of ting_search_context_handler_filter_context_type
 */

/**
 * Handler to filter contexts based on type.
 */
class ting_search_context_handler_filter_context_type extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Context types');
      $this->value_options = ting_search_context_get_types();
    }
  }
}
