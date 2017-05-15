<?php
/**
 * @file
 * ding_place2book.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ding_place2book_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_place2book'
  $field_bases['field_place2book'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_place2book',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ding_place2book',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'ding_p2b',
  );

  // Exported field_base: 'field_place2book_tickets'
  $field_bases['field_place2book_tickets'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_place2book_tickets',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
