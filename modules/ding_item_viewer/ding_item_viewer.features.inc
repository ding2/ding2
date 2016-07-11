<?php
/**
 * @file
 * ding_item_viewer.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function ding_item_viewer_image_default_styles() {
  $styles = array();

  // Exported image style: ding_item_viewer_image_big.
  $styles['ding_item_viewer_image_big'] = array(
    'name' => 'ding_item_viewer_image_big',
    'label' => 'Ding item viewer (big)',
    'effects' => array(
      4 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '160',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_item_viewer_image_small.
  $styles['ding_item_viewer_image_small'] = array(
    'name' => 'ding_item_viewer_image_small',
    'label' => 'Ding item viewer (small)',
    'effects' => array(
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '120',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
