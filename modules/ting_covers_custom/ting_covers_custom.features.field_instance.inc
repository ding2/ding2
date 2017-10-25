<?php
/**
 * @file
 * ting_covers_custom.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ting_covers_custom_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'ting_covers_custom-cover-field_ting_covers_custom_image'
  $field_instances['ting_covers_custom-cover-field_ting_covers_custom_image'] = array(
    'bundle' => 'cover',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'file',
          'image_style' => 'thumbnail',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'ting_covers_custom',
    'field_name' => 'field_ting_covers_custom_image',
    'label' => 'Cover image',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'ting_covers_custom',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '350x500',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'manualcrop_crop_info' => 1,
        'manualcrop_default_crop_area' => 1,
        'manualcrop_enable' => 0,
        'manualcrop_inline_crop' => 0,
        'manualcrop_instant_crop' => 0,
        'manualcrop_instant_preview' => 1,
        'manualcrop_keyboard' => 1,
        'manualcrop_maximize_default_crop_area' => 0,
        'manualcrop_require_cropping' => array(),
        'manualcrop_styles_list' => array(),
        'manualcrop_styles_mode' => 'include',
        'manualcrop_thumblist' => 0,
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 32,
    ),
  );

  // Exported field_instance: 'ting_covers_custom-cover-field_ting_covers_custom_object'
  $field_instances['ting_covers_custom-cover-field_ting_covers_custom_object'] = array(
    'bundle' => 'cover',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'ting_reference',
        'settings' => array(
          'view_mode' => 'teaser',
        ),
        'type' => 'ting_reference_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'module' => 'ting_carousel',
        'settings' => array(
          'view_mode' => 'reference_teaser',
        ),
        'type' => 'ting_carousel',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'ting_covers_custom',
    'field_name' => 'field_ting_covers_custom_object',
    'label' => 'Object',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'ting_reference',
      'settings' => array(),
      'type' => 'ting_reference_advanced',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Cover image');
  t('Object');

  return $field_instances;
}
