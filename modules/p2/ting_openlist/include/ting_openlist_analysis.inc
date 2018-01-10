<?php

/**
 * @file
 * Functions for analysis of local OpenList Entities
 */

/**
 * Get provider users.
 *
 * @return int
 *   Number of provider users.
 */
function ting_openlist_local_analysis_data_providers() {
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  return $query->countQuery()->execute()->fetchField();
}

/**
 * Get provider users with an openlist uid.
 *
 * @return int
 *   Number of provider users.
 */
function ting_openlist_local_analysis_data_providers_id() {
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  $query->condition('openlist_uid', NULL, 'IS NOT');
  return $query->countQuery()->execute()->fetchField();
}

/**
 * Get provider users which are synced.
 *
 * @return int
 *   Number of synced users.
 */
function ting_openlist_local_analysis_data_providers_openlist_is_sync() {
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  $query->condition('openlist_modified', 0, '>');
  return $query->countQuery()->execute()->fetchField();
}

/**
 * Count the types of lists, grouped by users.
 *
 * @return array
 *   An associative array, where the key indicates how many instances there is
 *   of a list type (list_type__X), and the value is the number of users that
 *   has that many lists.
 *
 *   If the installation has 3 users, and 1 of these users has a duplicate of
 *   the books_read type, the output would be:
 *   [
 *     'books_read__1' => '2',
 *     'books_read__2' => '1',
 *   ]
 */
function ting_openlist_local_analysis_data_list_counts() {
  $sub_query = db_select('field_data_field_list_type', 'flt');
  $sub_query->join('eck_ding_type', 'dt', 'dt.id = flt.entity_id');
  $sub_query->addField('flt', 'field_list_type_value', 'type');
  $sub_query->addExpression('COUNT(flt.entity_id)', 'cnt');
  $sub_query
    ->condition('flt.field_list_type_value', 'user_list', '!=')
    ->groupBy('dt.uid')
    ->groupBy('flt.field_list_type_value')
    ->orderBy('cnt', 'DESC');
  $query = db_select($sub_query, 's');
  $query->addExpression("CONCAT(s.type, '__', s.cnt)", 'type');
  $query->addExpression('COUNT(s.type)', 'cnt');
  $query
    ->groupBy('s.type')
    ->groupBy('s.cnt')
    ->orderBy('s.type')
    ->orderBy('s.cnt');
  return $query->execute()->fetchAllKeyed();
}

/**
 * Get the top 10 users, with duplicate lists, ordered by number duplicates.
 *
 * @return array
 *   Keyed array, where they key is the openlist_uid and value the number of
 *   list duplicates.
 */
function ting_openlist_local_analysis_data_top10_list() {
  $sub_query = db_select('field_data_field_list_type', 'flt');
  $sub_query->join('eck_ding_type', 'dt', 'dt.id = flt.entity_id');
  $sub_query->addField('dt', 'uid');
  $sub_query->addExpression('COUNT(flt.entity_id)', 'cnt');
  $sub_query
    ->condition('flt.field_list_type_value', 'user_list', '!=')
    ->groupBy('dt.uid')
    ->groupBy('flt.field_list_type_value')
    ->orderBy('cnt', 'DESC')
    ->havingCondition('cnt', 1, '>');
  $query = db_select($sub_query, 's');
  $query->join('users', 'u', 'u.uid = s.uid');
  $query->addField('u', 'openlist_uid');
  $query->addField('s', 'cnt');
  $query
    ->groupBy('s.uid')
    ->groupBy('s.cnt')
    ->orderBy('cnt', 'DESC')
    ->range(0, 10);
  return $query->execute()->fetchAllKeyed();
}

/**
 * Get count of lists with duplicate elements.
 *
 * @return array
 *   An associative array, where the key tells how many duplicates there is in
 *   a list, and the value is the number of lists with this many duplicates.
 */
function ting_openlist_local_analysis_data_duplicate_elements() {
  $sub_query = db_select('field_data_field_list_objects', 'flo');
  $sub_query->join('field_data_field_value', 'fv', 'fv.entity_id = flo.field_list_objects_target_id');
  $sub_query->addField('flo', 'entity_id');
  $sub_query->addExpression('COUNT(fv.field_value_value)', 'cnt');
  $sub_query
    ->groupBy('flo.entity_id')
    ->groupBy('fv.field_value_value')
    ->havingCondition('cnt', 1, '>');
  $query = db_select($sub_query, 's');
  $query->addExpression("CONCAT('duplicates__', s.cnt)", 'elements');
  $query->addExpression('COUNT(s.entity_id)', 'cnt');
  $query
    ->groupBy('s.entity_id')
    ->groupBy('s.cnt')
    ->orderBy('s.entity_id')
    ->orderBy('s.cnt');
  return $query->execute()->fetchAllKeyed();
}

/**
 * Get the analysis data.
 *
 * @return array
 *   The associated array of data. Check the documentation for each of the
 *   functions for more information about the specific key.
 */
function ting_openlist_get_local_analysis_data() {
  return array(
    'providers' => ting_openlist_local_analysis_data_providers(),
    'providers_openlist_id' => ting_openlist_local_analysis_data_providers_id(),
    'providers_openlist_is_sync' => ting_openlist_local_analysis_data_providers_openlist_is_sync(),
    'list_counts' => ting_openlist_local_analysis_data_list_counts(),
    'top10_list' => ting_openlist_local_analysis_data_top10_list(),
    'duplicate_elements' => ting_openlist_local_analysis_data_duplicate_elements(),
  );
}
