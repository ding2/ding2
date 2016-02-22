<?php
/**
 * @file
 * Export Item List Features.
 */

/**
 * Implements hook_image_default_styles().
 */
function ding_item_list_image_default_styles() {
  $styles = array();

  // Exported image style: ding_item_list.
  $styles['ding_item_list'] = array(
    'name' => 'ding_item_list',
    'label' => 'ding_item_list',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 50,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
