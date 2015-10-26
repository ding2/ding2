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
    'filter' => array(
      'handler' => 'ting_search_context_handler_filter_context_type',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string', // Maybe override to use name as summary.
    ),
  );
  $data['ting_search_context_contexts']['name'] = array(
    'title' => t('Name'),
    'help' => t('The human-readable name of the context'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['ting_search_context_contexts']['context'] = array(
    'title' => t('Context'),
    'help' => t('The machine-name of the context'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',  // ting_search_context_handler_filter_context_machine_name.
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['ting_search_context_contexts']['subjects'] = array(
    'title' => t('Subjects'),
    'help' => t('The subjects of the context'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  $data['ting_search_context_contexts']['search'] = array(
    'title' => t('Search'),
    'help' => t('The search string of the context'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  // TODO: Relationship handlers for context_id and nid.
  $data['ting_search_context_nodes_rated']['context_id'] = array(
    'title' => t('Context ID'),
    'help' => t('The ID of the rated context'),
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
    ),
  );
  $data['ting_search_context_nodes_rated']['nid'] = array(
    'title' => t('Node ID'),
    'help' => t('The ID of the rated node'),
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
    ),
  );
  $data['ting_search_context_nodes_rated']['rating'] = array(
    'title' => t('Rating'),
    'help' => t('The rating-number of the rating'),
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
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function ting_search_context_views_data_alter(&$data) {
  // Provide some special handlers on the node table as an easy way to tackle
  // the many-to-many complexity between nodes and contexts. For example, a
  // node can be rated in many contexts and a contexts can have many nodes
  // rated in it.
  $data['node']['ting_search_context_node_ratings'] = array(
    'title' => t('Node ratings'),
    'help' => t('Associates ratings with nodes'),
    'field' => array(
      'title' => t('All ratings'),
      'help' => t('Display all ratings associated with a node'),
      'handler' => 'ting_search_context_handler_field_node_ratings',
      'no group by' => TRUE,
    ),
    'filter' => array(
      'title' => t('Rating filter'),
      'help' => t('Filter to only display content rated in selected contexts'),
      'handler' => 'ting_search_context_handler_filter_node_ratings',
      'real field' => 'nid',
    ),
  );
}
