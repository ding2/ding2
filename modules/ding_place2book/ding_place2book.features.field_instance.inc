<?php
/**
 * @file
 * ding_place2book.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ding_place2book_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-ding_event-field_place2book'
  $field_instances['node-ding_event-field_place2book'] = array(
    'bundle' => 'ding_event',
    'default_value' => array(),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'ding_place2book',
        'settings' => array(),
        'type' => 'ding_p2b_formatter_default',
        'weight' => 14,
      ),
      'search_result' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_highlight' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_place2book',
    'label' => 'Place2book',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'ding_place2book',
      'settings' => array(),
      'type' => 'ding_p2b_widget_default',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Place2book');

  return $field_instances;
}
