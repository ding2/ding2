<?php

/**
 * @file
 * ding_sections_custom_css.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ding_sections_custom_css_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ding_sections_custom_css'.
  $field_bases['field_ding_sections_custom_css'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ding_sections_custom_css',
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
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
