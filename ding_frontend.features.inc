<?php
/**
 * @file
 * ding_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_frontend_ctools_plugin_api() {
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
 * Implements hook_views_api().
 */
function ding_frontend_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function ding_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: ding_attachment_large.
  $styles['ding_attachment_large'] = array(
    'name' => 'ding_attachment_large',
    'effects' => array(
      6 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '500',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_attachment_medium.
  $styles['ding_attachment_medium'] = array(
    'name' => 'ding_attachment_medium',
    'effects' => array(
      7 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '500',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_attachment_small.
  $styles['ding_attachment_small'] = array(
    'name' => 'ding_attachment_small',
    'effects' => array(
      8 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '500',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_covers_large.
  $styles['ding_covers_large'] = array(
    'name' => 'ding_covers_large',
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
          'width' => '300',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_covers_medium.
  $styles['ding_covers_medium'] = array(
    'name' => 'ding_covers_medium',
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
          'width' => '300',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_covers_small.
  $styles['ding_covers_small'] = array(
    'name' => 'ding_covers_small',
    'effects' => array(
      5 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '200',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_primary_large.
  $styles['ding_primary_large'] = array(
    'name' => 'ding_primary_large',
    'effects' => array(
      15 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '1200',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_primary_medium.
  $styles['ding_primary_medium'] = array(
    'name' => 'ding_primary_medium',
    'effects' => array(
      16 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '1000',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_primary_small.
  $styles['ding_primary_small'] = array(
    'name' => 'ding_primary_small',
    'effects' => array(
      17 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '500',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_secondary_large.
  $styles['ding_secondary_large'] = array(
    'name' => 'ding_secondary_large',
    'effects' => array(
      12 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '900',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_secondary_medium.
  $styles['ding_secondary_medium'] = array(
    'name' => 'ding_secondary_medium',
    'effects' => array(
      13 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '900',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_secondary_small.
  $styles['ding_secondary_small'] = array(
    'name' => 'ding_secondary_small',
    'effects' => array(
      14 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '500',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_tetiary_large.
  $styles['ding_tetiary_large'] = array(
    'name' => 'ding_tetiary_large',
    'effects' => array(
      9 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '600',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_tetiary_medium.
  $styles['ding_tetiary_medium'] = array(
    'name' => 'ding_tetiary_medium',
    'effects' => array(
      10 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '600',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: ding_tetiary_small.
  $styles['ding_tetiary_small'] = array(
    'name' => 'ding_tetiary_small',
    'effects' => array(
      11 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '500',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
