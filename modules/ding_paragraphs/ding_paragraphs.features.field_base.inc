<?php

/**
 * @file
 * ding_paragraphs.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ding_paragraphs_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ding_paragraphs_box_text'.
  $field_bases['field_ding_paragraphs_box_text'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ding_paragraphs_box_text',
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

  // Exported field_base: 'field_ding_paragraphs_display'.
  $field_bases['field_ding_paragraphs_display'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ding_paragraphs_display',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'full_width' => 'Full width',
        'half_right' => '1/2 width (aligned right)',
        'half_left' => '1/2 width (aligned left)',
        'one_third_right' => '1/3 width (aligned right)',
        'one_third_left' => '1/3 width (aligned left)',
      ),
      'allowed_values_function' => '',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_ding_paragraphs_image'.
  $field_bases['field_ding_paragraphs_image'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ding_paragraphs_image',
    'foreign keys' => array(
      'fid' => array(
        'columns' => array(
          'fid' => 'fid',
        ),
        'table' => 'file_managed',
      ),
    ),
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'profile2_private' => FALSE,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'field_ding_paragraphs_material'.
  $field_bases['field_ding_paragraphs_material'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ding_paragraphs_material',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'ting_reference',
    'settings' => array(
      'profile2_private' => FALSE,
    ),
    'storage' => array(
      'active' => 1,
      'module' => 'ting_reference',
      'settings' => array(),
      'type' => 'ting_reference',
    ),
    'translatable' => 0,
    'type' => 'ting_reference',
  );

  // Exported field_base: 'field_ding_paragraphs_position'.
  $field_bases['field_ding_paragraphs_position'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ding_paragraphs_position',
    'foreign keys' => array(),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'ting_object_left' => 'Image left',
        'image_top' => 'Image top',
        'image_bottom' => 'Image bottom',
      ),
      'allowed_values_function' => '',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_ding_paragraphs_text'.
  $field_bases['field_ding_paragraphs_text'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ding_paragraphs_text',
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
