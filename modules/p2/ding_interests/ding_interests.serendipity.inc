<?php

/**
 * @file
 * This module provides serendipity functions based on user lists and loans
 *
 * Description of the module.
 */

/**
 * Implements hook_serendipity_info().
 */
function ding_interests_serendipity_info() {
  return array(
    'materials' => array(
      'title' => 'Interests',
      'description' => 'Get materials based on users interests',
      'keys' => array('ting_object', 'frontpage'),
    ),
    'nodes_by_bundle' => array(
      'title' => 'Nodes by bundle',
      'description' => 'Find nodes matching the context bundle',
      'keys' => array('node', 'frontpage'),
    ),
  );
}

/**
 * Ratings by interest serendipity function.
 *
 * Select random objects from current loans,
 * and fetch recommended objecs via ADHL service.
 *
 * @param array $context
 *   Serendipity context.
 *
 * @return array
 *   Array of results.
 */
function ding_interests_materials_serendipity_add($context) {
  // These are only shown on the front page if the user is logged in.
  if (!user_is_logged_in() || !$context['frontpage']) {
    return array();
  }

  $results = array();
  // Fetch followed terms.
  if (!isset($context['interest'])) {
    $term = ding_interests_get_random_interest_term(DING_INTERESTS_LIST);
  }
  else {
    $term = taxonomy_term_load($context['interest']);
  }

  if (!empty($term)) {
    if (!empty($term->field_search_string)) {
      $query = $term->field_search_string[field_language('taxonomy_term', $term, 'field_search_string')][0]['value'];
    }
    else {
      $query = "facet.subject=\"$term->name\"";
    };

    $query = ding_list_convert_cql($query);

    // Fetch search results.
    $options = array(
      'limit' => 10,
    );
    $results = ding_serendipity_do_search($query, $options);
    // Append source info.
    foreach ($results as & $item) {
      $item['info'] = array(
        'Term' => $term->name,
        'description' => t('Because you selected !term as an interest.', array('!term' => $term->name)),
      );
    }
  }
  return $results;
}

/**
 * Ding Serendipity function for node bundles.
 *
 * @context array
 *  Serendipity context array
 *
 * @return array
 *   Array of results, each result should contain a type and an id key.
 *   - Type is the entity Type.
 *   - id the entity id.
 */
function ding_interests_nodes_by_bundle_serendipity_add($context) {
  $results = array();
  // Fetch followed terms.
  $term = ding_interests_get_random_interest_term('interests');
  if (!empty($term)) {
    // We could do this using EntityFieldQuery, but every tag field
    // has a different name for each bundle, so this approach is simpler.
    $select = db_select('taxonomy_index', 'ti');
    $select->addField('ti', 'nid');
    $select->condition('ti.tid', array($term->tid), 'IN');
    $select->join('node', 'n', 'ti.nid = n.nid');
    $select->condition('n.type', array($context['bundle']), 'IN');
    $result = $select->execute();

    $nids = array();
    foreach ($result as $row) {
      $nids[$row->nid] = $row->nid;
    }
    foreach ($nids as $nid) {
      $item = array(
        'type' => 'node',
        'id' => $nid,
        'info' => array(
          'Term' => $term->name,
          'description' => t('Because you selected @term as an interest.', array('@term' => $term->name)),
        ),
      );
      $results[] = $item;
    }
  }

  return $results;
}
