<?php
/**
 * @file
 * ding_ting_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_ting_frontend_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ding_ting_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: ding_large.
  $styles['ding_large'] = array(
    'effects' => array(
      0 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 134,
          'height' => 194,
          'upscale' => 1,
        ),
        'weight' => 0,
      ),
    ),
    'name' => 'ding_large',
  );

  // Exported image style: ding_medium.
  $styles['ding_medium'] = array(
    'effects' => array(
      0 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 85,
          'height' => 132,
          'upscale' => 1,
        ),
        'weight' => 0,
      ),
    ),
    'name' => 'ding_medium',
  );

  // Exported image style: ding_small.
  $styles['ding_small'] = array(
    'effects' => array(
      0 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 55,
          'height' => 85,
          'upscale' => 1,
        ),
        'weight' => 0,
      ),
    ),
    'name' => 'ding_small',
  );

  return $styles;
}
