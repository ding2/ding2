<?php
/**
 * @file
 * ding_entity_rating.features.field_instance.inc
 */

/**
 * Implements ding_entity_rating_field_default_field_instances().
 */
function ding_entity_rating_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'ting_object-ting_object-ding_entity_rating_action'
  $field_instances['ting_object-ting_object-ding_entity_rating_action'] = array(
    'bundle' => 'ting_object',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'ding_entity_type' => 'ding_entity',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_action_default',
        'weight' => -1,
      ),
    ),
    'entity_type' => 'ting_object',
    'field_name' => 'ding_entity_rating_action',
    'label' => 'Rate this',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => -1,
    ),
  );

  // Exported field_instance: 'ting_object-ting_object-ding_entity_rating_result'
  $field_instances['ting_object-ting_object-ding_entity_rating_result'] = array(
    'bundle' => 'ting_object',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'ding_entity_type' => 'ding_entity',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_result_default',
        'weight' => -1,
      ),
    ),
    'entity_type' => 'ting_object',
    'field_name' => 'ding_entity_rating_result',
    'label' => 'Average rating',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => -1,
    ),
  );  
  
  // Translatables
  // Included for use with string extractors like potx.
  t('Rate this');
  t('Average rating');

  return $field_instances;
}
