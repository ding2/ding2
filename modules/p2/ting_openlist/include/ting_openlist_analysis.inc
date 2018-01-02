<?php

/**
 * @file
 * Functions for analysis of local OpenList Entities
 */

function ting_openlist_get_local_analysis() {
  $data = ting_openlist_get_local_analysis_data();
  return '<pre>' . htmlentities(var_export($data, TRUE)) . '</pre>';
}

function ting_openlist_get_local_analysis_data() {
  $data = array();

  // Providers.
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  $data['providers'] = $query->countQuery()->execute()->fetchField();

  // Providers openlist id
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  $query->condition('openlist_uid', NULL, 'IS NOT');
  $data['providers_openlist_id'] = $query->countQuery()->execute()->fetchField();

  // Providers openlist is sync
  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");
  $query->condition('openlist_modified', 0, '>');
  $data['providers_openlist_is_sync'] = $query->countQuery()->execute()->fetchField();

  // List counts
  $squery = db_select('field_data_field_list_type', 'flt');
  $squery->join('eck_ding_type', 'dt', 'dt.id = flt.entity_id');
  $squery->addField('flt', 'field_list_type_value', 'type');
  $squery->addExpression('COUNT(flt.entity_id)', 'cnt');
  $squery
    ->condition('flt.field_list_type_value', 'user_list', '!=')
    ->groupBy('dt.uid')
    ->groupBy('flt.field_list_type_value')
    ->orderBy('cnt', 'DESC');
  $query = db_select($squery, 's');
  $query->addExpression("CONCAT(s.type, '__', s.cnt)", 'type');
  $query->addExpression('COUNT(s.type)', 'cnt');
  $query
    ->groupBy('s.type')
    ->groupBy('s.cnt')
    ->orderBy('s.type')
    ->orderBy('s.cnt');
  $data['list_counts'] = $query->execute()->fetchAllKeyed();

  // Top users with multiple lists.
  $squery->addField('dt', 'uid');
  $squery->havingCondition('cnt', 1, '>');
  $query = db_select($squery, 's');
  $query->join('users', 'u', 'u.uid = s.uid');
  $query->addField('u', 'openlist_uid');
  $query->addField('s', 'cnt');
  $query
    ->groupBy('s.uid')
    ->groupBy('s.cnt')
    ->orderBy('cnt', 'DESC')
    ->range(0, 10);
  $data['top10_list'] = $query->execute()->fetchAllKeyed();

  // Element counts
  $squery = db_select('field_data_field_list_objects', 'flo');
  $squery->join('field_data_field_value', 'fv', 'fv.entity_id = flo.field_list_objects_target_id');
  $squery->addField('flo', 'entity_id');
  $squery->addExpression('COUNT(fv.field_value_value)', 'cnt');
  $squery
    ->groupBy('flo.entity_id')
    ->groupBy('fv.field_value_value')
    ->havingCondition('cnt', 1, '>');
  $query = db_select($squery, 's');
  $query->addExpression("CONCAT('duplicates__', s.cnt)", 'lists');
  $query->addExpression('COUNT(s.entity_id)', 'cnt');
  $query
    ->groupBy('s.entity_id')
    ->groupBy('s.cnt')
    ->orderBy('s.entity_id')
    ->orderBy('s.cnt');
  $data['elements_counts'] = $query->execute()->fetchAllKeyed();

  return $data;
}
