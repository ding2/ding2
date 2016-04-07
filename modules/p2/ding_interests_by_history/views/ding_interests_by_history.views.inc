<?php

/**
 * @file
 * ding_interests.views_default.inc
 */

/**
 * Implements hook_views_data().
 */
function ding_interests_by_history_views_data() {
  $data = array();
  // Status.
  $data['taxonomy_term_data']['ding_interests_by_history'] = array(
    'group' => t('Ding'),
    'title' => t('Interests by loan history'),
    'help' => t('Filter by subjects, genres and material types of the users loan history'),
    'table_alias' => 'taxonomy_term_data',
    'real field' => 'tid',
    'filter' => array(
      'handler' => 'views_handler_filter_interests_by_history',
      'label' => t('Interests'),
    ),
  );

  return $data;
}
