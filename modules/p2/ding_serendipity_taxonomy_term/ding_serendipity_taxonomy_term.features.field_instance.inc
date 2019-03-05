<?php

/**
 * @file
 * ding_serendipity_taxonomy_term.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ding_serendipity_taxonomy_term_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'taxonomy_term-ding_content_tags-field_taxonomy_ting_objects'.
  $field_instances['taxonomy_term-ding_content_tags-field_taxonomy_ting_objects'] = array(
    'bundle' => 'ding_content_tags',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_taxonomy_ting_objects',
    'label' => 'Materials',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 44,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Materials');

  return $field_instances;
}
