<?php
/**
 * @file
 * bpi_features.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function bpi_features_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_bpi_workflow'
  $field_bases['field_bpi_workflow'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_bpi_workflow',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'workflowfield',
    'settings' => array(
      'allowed_values_function' => 'workflowfield_allowed_values',
      'allowed_values_string' => '1 | (creation)
2 | Local content
3 | Pre-sending to BPI
4 | Sent to BPI
5 | Sent, updated locally
6 | Created from BPI
7 | Deleted from BPI',
      'history' => array(
        'history_tab_show' => 1,
        'roles' => array(
          -1 => 0,
          3 => 3,
          4 => 4,
          6 => 6,
          7 => 7,
        ),
      ),
      'profile2_private' => FALSE,
      'watchdog_log' => 1,
      'wid' => 1,
      'widget' => array(
        'comment' => 1,
        'hide' => 0,
        'name_as_title' => 1,
        'options' => 'buttons',
        'schedule' => 0,
        'schedule_timezone' => 1,
      ),
    ),
    'translatable' => 0,
    'type' => 'workflow',
  );

  return $field_bases;
}
