<?php
/**
 * @file
 * ting_oembed_features.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ting_oembed_features_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'ting_object-ting_object-field_ting_oembed_oembed'
  $field_instances['ting_object-ting_object-field_ting_oembed_oembed'] = array(
    'bundle' => 'ting_object',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
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
      'default' => array(
        'label' => 'hidden',
        'module' => 'ting_oembed',
        'settings' => array(),
        'type' => 'ting_oembed_default',
        'weight' => 69,
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
    'field_name' => 'field_ting_oembed_oembed',
    'label' => 'Material content',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'virtual_field',
      'settings' => array(),
      'type' => 'hidden',
      'weight' => 15,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Material content');

  return $field_instances;
}
