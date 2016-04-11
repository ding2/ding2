<?php

/**
 * @file
 * Definition of views_handler_filter_equality.
 */

/**
 * Simple filter to handle equal to / not equal to filters
 *
 * @ingroup views_filter_handlers
 */
class Views_handler_filter_interests_by_history extends views_handler_filter_in_operator {
  public $value_form_type = 'checkboxes';

  // Stores all operations which are available on the form.
  public $value_options = NULL;

  /**
   * Provide some extra help to get the operator/value easier to use.
   *
   * This likely has to be overridden by filters which are more complex
   * than simple operator/value.
   */
  public function init(&$view, &$options) {
    parent::init($view, $options);

    $this->operator = $this->options['operator'];
    $this->value = ding_interests_by_history_suggested_terms();
    $this->group_info = $this->options['group_info']['default_group'];

    // Compatibility: The new UI changed several settings.
    if (!empty($options['exposed']) && !empty($options['expose']['optional']) && !isset($options['expose']['required'])) {
      $this->options['expose']['required'] = !$options['expose']['optional'];
    }
    if (!empty($options['exposed']) && !empty($options['expose']['single']) && !isset($options['expose']['multiple'])) {
      $this->options['expose']['multiple'] = !$options['expose']['single'];
    }
    if (!empty($options['exposed']) && !empty($options['expose']['operator']) && !isset($options['expose']['operator_id'])) {
      $this->options['expose']['operator_id'] = $options['expose']['operator_id'] = $options['expose']['operator'];
    }

    if ($this->multiple_exposed_input()) {
      $this->group_info = array_filter($options['group_info']['default_group_multiple']);
      $this->options['expose']['multiple'] = TRUE;
    }

    // If there are relationships in the view, allow empty should be true
    // so that we can do IS NULL checks on items. Not all filters respect
    // allow empty, but string and numeric do and that covers enough.
    if ($this->view->display_handler->get_option('relationships')) {
      $this->definition['allow empty'] = TRUE;
    }
  }

  /**
   * Default construct.
   */
  public function construct() {
    parent::construct();
    $this->value_title = t('Options');
    $this->value_options = NULL;
  }

  /**
   * Child classes should be used to override this function and set the
   * 'value options', unless 'options callback' is defined as a valid function
   * or static public method to generate these values.
   *
   * This can use a guard to be used to reduce database hits as much as
   * possible.
   *
   * @return
   *   Return the stored values in $this->value_options if someone expects it.
   */
  public function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    if (isset($this->definition['options callback']) && is_callable($this->definition['options callback'])) {
      if (isset($this->definition['options arguments']) && is_array($this->definition['options arguments'])) {
        $this->value_options = call_user_func_array($this->definition['options callback'], $this->definition['options arguments']);
      }
      else {
        $this->value_options = call_user_func($this->definition['options callback']);
      }
    }
    else {
      $this->value_options = array(t('Yes'), t('No'));
    }

    return $this->value_options;
  }

  public function expose_options() {
    parent::expose_options();
  }

  public function expose_form(&$form, &$form_state) {
    parent::expose_form($form, $form_state);
  }

  public function option_definition() {
    $options = parent::option_definition();

    $options['operator']['default'] = 'in';
    $options['value']['default'] = array();

    return $options;
  }

  /**
   * This kind of construct makes it relatively easy for a child class
   * to add or remove functionality by overriding this function and
   * adding/removing items from this array.
   */
  public function operators() {
    $operators = array(
      'in' => array(
        'title' => t('Is one of'),
        'short' => t('in'),
        'short_single' => t('='),
        'method' => 'op_simple',
        'values' => 1,
      ),
      'not in' => array(
        'title' => t('Is not one of'),
        'short' => t('not in'),
        'short_single' => t('<>'),
        'method' => 'op_simple',
        'values' => 1,
      ),
    );
    
    // If the definition allows for the empty operator, add it.
    if (!empty($this->definition['allow empty'])) {
      $operators += array(
        'empty' => array(
          'title' => t('Is empty (NULL)'),
          'method' => 'op_empty',
          'short' => t('empty'),
          'values' => 0,
        ),
        'not empty' => array(
          'title' => t('Is not empty (NOT NULL)'),
          'method' => 'op_empty',
          'short' => t('not empty'),
          'values' => 0,
        ),
      );
    }

    return $operators;
  }

  /**
   * Build strings from the operators() for 'select' options
   */
  public function operator_options($which = 'title') {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      $options[$id] = $info[$which];
    }

    return $options;
  }

  public function operator_values($values = 1) {
    $options = array();
    foreach ($this->operators() as $id => $info) {
      if (isset($info['values']) && $info['values'] == $values) {
        $options[] = $id;
      }
    }

    return $options;
  }

  public function value_form(&$form, &$form_state) {
    $form['value'] = array();
    $options = array();

    if (empty($form_state['exposed'])) {
      // Add a select all option to the value form.
      $options = array('all' => t('Select all'));
    }

    $this->get_value_options();
    $options += $this->value_options;
    $default_value = (array) $this->value;

    $which = 'all';
    if (!empty($form['operator'])) {
      $source = ($form['operator']['#type'] == 'radios') ? 'radio:options[operator]' : 'edit-options-operator';
    }
    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];

      if (empty($this->options['expose']['use_operator']) || empty($this->options['expose']['operator_id'])) {
        // Exposed and locked.
        $which = in_array($this->operator, $this->operator_values(1)) ? 'value' : 'none';
      }
      else {
        $source = 'edit-' . drupal_html_id($this->options['expose']['operator_id']);
      }

      if (empty($this->options['expose']['multiple'])) {
        if (empty($this->options['expose']['required']) && (empty($default_value) || !empty($this->options['expose']['reduce']))) {
          $default_value = 'All';
        }
        elseif (empty($default_value)) {
          $keys = array_keys($options);
          $default_value = array_shift($keys);
        }
        else {
          $copy = $default_value;
          $default_value = array_shift($copy);
        }
      }
    }
  }

  public function accept_exposed_input($input) {
    // A very special override because the All state for this type of
    // filter could have a default:
    if (empty($this->options['exposed'])) {
      return TRUE;
    }

    // If this is non-multiple and non-required, then this filter will
    // participate, but using the default settings, *if* 'limit is true.
    if (empty($this->options['expose']['multiple']) && empty($this->options['expose']['required']) && !empty($this->options['expose']['limit'])) {
      $identifier = $this->options['expose']['identifier'];
      if ($input[$identifier] == 'All') {
        return TRUE;
      }
    }

    return parent::accept_exposed_input($input);
  }

  public function value_submit($form, &$form_state) {
    // Prevent value submit
  }

  public function admin_summary() {
    if ($this->is_a_group()) {
      return t('grouped');
    }
    if (!empty($this->options['exposed'])) {
      return t('exposed'3);
    }
    $info = $this->operators();

    $this->get_value_options();

    if (!is_array($this->value)) {
      return;
    }

    $operator = check_plain($info[$this->operator]['short']);
    $values = ' terms from historical loans';

    return $operator . (($values !== '') ? ' ' . $values : '');
  }

  public function op_simple() {
    $this->ensure_my_table();
    $this->value = ding_interests_by_history_suggested_terms();

    if (empty($this->value)) {
      return;
    }
    // We use array_values() because the checkboxes keep keys and that can cause
    // array addition problems.
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", array_keys($this->value), $this->operator);
  }
}

