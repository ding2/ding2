<?php
/**
 * @file
 * ding_sections_custom_css.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ding_sections_custom_css_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'taxonomy_term-section-field_ding_sections_custom_css'.
  $field_instances['taxonomy_term-section-field_ding_sections_custom_css'] = array(
    'bundle' => 'section',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_ding_sections_custom_css',
    'label' => 'Custom CSS',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => -2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Custom CSS');

  return $field_instances;
}
