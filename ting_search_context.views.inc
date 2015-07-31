<?php

/**
 * @file
 *
 * Contains this modules Views-hook implementations.
 *
 * TODO:
 * 1. Finish describing fields
 * 2. Make a Ting seach context view
 * 3. Try to embed that view in admin interface and see how it works.
 */

/**
 * Implements hook_views_data().
 *
 * Describes our custom tables to Views.
 *
 * @see ting_search_context_schema().
 */
function ting_search_context_views_data() {
  $data = array();

  // Describe the contexts table as a Views base table.
  $data['ting_search_context_contexts']['table'] = array(
    'group' => t('Ting search context'),
    'base' => array(
      'field' => 'context_id',
      'title' => t('Ting search context contexts'),
      'help' => t('Search contexts from the Ting search context module'),
      'weight' => -10
    ),
    // Link the contexts table to the nodes_rated table and tell Views how to
    // join our table with the node table (Implicit relationship)
    'join' => array(
      'node' => array(
        'left_table' => 'ting_search_context_nodes_rated',
        'left_field' => 'context_id',
        'field' => 'context_id', // Field to join on this table
      ),
    ),
  );

  // The nodes rated table (not a Views base table)
  $data['ting_search_context_nodes_rated']['table'] = array(
    'group' => t('Ting search context'),
    'join' => array(
      'node' => array(
        'left_field' => 'nid',
        'field' => 'nid',
      ),
    ),
  );

  // Describe each of the individual fields in our tables
  $data['ting_search_context_contexts']['context_id'] = array(
    'title' => t('Context ID'),
    'help' => t('The ID of the context'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE, // Used by table display plugin
    ),
    // Information for accepting a context ID as argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );
  $data['ting_search_context_contexts']['type'] = array(
    'title' => t('Type'),
    'help' => t('The context type (system, search or subject)'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

}

