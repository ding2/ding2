<?php

/**
 * @file
 * Functions for analysis of local OpenList Entities
 */

function ting_openlist_local_analysis_data_providers() {
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  return $query->countQuery()->execute()->fetchField();
}

function ting_openlist_local_analysis_data_providers_id() {
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  $query->condition('openlist_uid', NULL, 'IS NOT');
  return $query->countQuery()->execute()->fetchField();
}

function ting_openlist_local_analysis_data_providers_openlist_is_sync() {
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  $query->condition('openlist_modified', 0, '>');
  return $query->countQuery()->execute()->fetchField();
}

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

function ting_openlist_local_analysis_data_elements_counts() {
  $sub_query = db_select('field_data_field_list_objects', 'flo');
  $sub_query->join('field_data_field_value', 'fv', 'fv.entity_id = flo.field_list_objects_target_id');
  $sub_query->addField('flo', 'entity_id');
  $sub_query->addExpression('COUNT(fv.field_value_value)', 'cnt');
  $sub_query
    ->groupBy('flo.entity_id')
    ->groupBy('fv.field_value_value')
    ->havingCondition('cnt', 1, '>');
  $query = db_select($sub_query, 's');
  $query->addExpression("CONCAT('duplicates__', s.cnt)", 'lists');
  $query->addExpression('COUNT(s.entity_id)', 'cnt');
  $query
    ->groupBy('s.entity_id')
    ->groupBy('s.cnt')
    ->orderBy('s.entity_id')
    ->orderBy('s.cnt');
  return $query->execute()->fetchAllKeyed();
}

function ting_openlist_get_local_analysis_data() {
  $data = array(
    'providers' => ting_openlist_local_analysis_data_providers(),
    'providers_openlist_id' => ting_openlist_local_analysis_data_providers_id(),
    'providers_openlist_is_sync' => ting_openlist_local_analysis_data_providers_openlist_is_sync(),
    'list_counts' => ting_openlist_local_analysis_data_list_counts(),
    'top10_list' => ting_openlist_local_analysis_data_top10_list(),
    'elements_counts' => ting_openlist_local_analysis_data_elements_counts(),
  );

  return $data;
}
