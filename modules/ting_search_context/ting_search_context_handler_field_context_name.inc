<?php

/**
 * @file
 *
 * Definition of ting_search_context_handler_field_context_name.
 */

/**
 * Field handler to display name of a context.
 *
 * Enables tranlations of system context names, when displaying contexts in
 * views.
 */
class ting_search_context_handler_field_context_name extends views_handler_field {

  /**
   * Ensure the context type field is added to the query.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    $this->additional_fields['type'] = array(
      'table' => 'ting_search_context_contexts',
      'field' => 'type'
    );
  }

  /**
   * Tranlate the system context names before rendering.
   */
  function get_value($values, $field = NULL) {
    $value = parent::get_value($values, $field);

    // Get our field alias for the context type.
    $field_alias = $this->aliases['type'];

    if (!empty($values->{$field_alias}) && $values->{$field_alias} == 'system') {
      return t($value);
    }
    return $value;
  }

}
