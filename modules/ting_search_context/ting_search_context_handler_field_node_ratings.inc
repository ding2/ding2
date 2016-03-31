<?php

/**
 * @file
 * Definition of ting_search_context_handler_field_node_ratings.
 */

/**
 * Field handler to display all ratings for a node.
 *
 * The Views module provides a handy base handler for fields dealing with the
 * display of multiple items in a list, so we extend that.
 *
 * @see views_handler_field_prerender_list
 */
class ting_search_context_handler_field_node_ratings extends views_handler_field_prerender_list {

  /**
   *
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
    // We need the nid field in our query.
    $this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
  }

  /**
   * Add our additional fields (nid) to the query.
   */
  function query() {
    $this->add_additional_fields();
  }

  /**
   *
   */
  function pre_render(&$values) {
    $this->field_alias = $this->aliases['nid'];

    // Collect the ids of the selected nodes.
    $nids = array();
    foreach ($values as $result) {
      if (!empty($result->{$this->field_alias})) {
        $nids[] = $result->{$this->field_alias};
      }
    }

    // Populate the items proberty as described in the class definition of
    // views_handler_field_prerender_list.
    if ($nids) {
      $query = db_select('ting_search_context_contexts', 'tsc');
      $query->join(
        'ting_search_context_nodes_rated',
        'nr',
        'tsc.context_id = nr.context_id'
      );
      $query->fields('tsc');
      $query->addField('nr', 'nid', 'nid');
      $query->addField('nr', 'rating', 'rating');
      $query->orderBy('nid');
      $query->orderBy('rating', 'DESC');
      // TODO: Ordering by machine-name to make it consistent. Should probably
      // be changed if a weight column is added to the context table.
      // See: ting_search_context_schema().
      $query->orderBy('tsc.context');
      $query->condition('nid', $nids);

      $result = $query->execute();

      // Populate each item with node ratings data retrieved from the database.
      foreach ($result as $node_rating) {
        // Enable translation of system context names.
        $context_name = $node_rating->name;
        if ($node_rating->type == 'system') {
          $context_name = t($context_name);
        }

        $nid = $node_rating->nid;
        $context_id = $node_rating->context_id;
        $item = array(
          'name' => $context_name,
          'context_type' => $node_rating->type,
          'context_machine_name' => $node_rating->context,
          'context_id' => $context_id,
          'nid' => $nid,
          'rating' => $node_rating->rating,
        );
        $this->items[$nid][$context_id] = $item;
      }
    }
  }

  /**
   *
   */
  function render_item($count, $item) {
    return $item['name'];
    // Be just returning name here we allow for greater flexibility.
    // Below is setup in the Views configuration instead.
    // return $item['name'] . ' (' . $item['rating'] . ')';.
  }

  /**
   * Add token support.
   */
  function add_self_tokens(&$tokens, $item) {
    foreach (array('name', 'rating', 'type', 'context_type', 'context_machine_name', 'context_id', 'nid') as $token) {
      // Replace _ with -.
      $tokens['[' . $this->options['id'] . '-' . str_replace('_', '-', $token) . ']'] = isset($item[$token]) ? $item[$token] : '';
    }
  }

  /**
   * Document our tokens for the UI.
   */
  function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-name' . ']'] = t('The name of the context');
    $tokens['[' . $this->options['id'] . '-rating' . ']'] = t('The rating (1-10)');
    $tokens['[' . $this->options['id'] . '-type' . ']'] = t('The type of the context (machine name)');
    $tokens['[' . $this->options['id'] . '-context-machine-name' . ']'] = t('The machine name of the context');
    $tokens['[' . $this->options['id'] . '-context-id' . ']'] = t('The ID of the context');
    $tokens['[' . $this->options['id'] . '-nid' . ']'] = t('The ID of the rated node');
  }

}
