<?php
/**
 * @file
 * ding_entity_rating.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
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
      'collection_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'collection_primary' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'compact' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_action_default',
        'weight' => 2,
      ),
      'default' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_action_default',
        'weight' => 7,
      ),
      'search_result' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_action_default',
        'weight' => 20,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_action_default',
        'weight' => 8,
      ),
      'ting_reference_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'user_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
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
      'collection_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'collection_primary' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'compact' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'default' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_result_default',
        'weight' => 8,
      ),
      'search_result' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_result_default',
        'weight' => 21,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'ding_entity_rating',
        'settings' => array(),
        'type' => 'ding_entity_rating_result_default',
        'weight' => 9,
      ),
      'ting_reference_preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'user_list' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
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
  t('Average rating');
  t('Rate this');

  return $field_instances;
}
