<?php
/**
 * @file
 * Export header image styles.
 */

/**
 * Implements hook_image_default_styles().
 */
function ding_sections_header_image_image_default_styles() {
  $styles = array();

  // Exported image style: section_header_image.
  $styles['section_header_image'] = array(
    'name' => 'section_header_image',
    'label' => 'section_header_image',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 90,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
