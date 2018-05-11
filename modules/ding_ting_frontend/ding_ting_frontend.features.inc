<?php
/**
 * @file
 * ding_ting_frontend.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ding_ting_frontend_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "pm_existing_pages" && $api == "pm_existing_pages") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "ting_field_search" && $api == "ting_field_search_default_profiles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ding_ting_frontend_image_default_styles() {
  $styles = array();

  // Exported image style: ting_cover_large.
  $styles['ting_cover_large'] = array(
    'name' => 'ting_cover_large',
    'label' => 'Ting cover large',
    'effects' => array(
      7 => array(
        'label' => 'Manual Crop: Custom crop',
        'help' => 'Crop a freely user-selected area.',
        'effect callback' => 'manualcrop_crop_effect',
        'form callback' => 'manualcrop_crop_form',
        'summary theme' => 'manualcrop_crop_summary',
        'module' => 'manualcrop',
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 500,
          'height' => '',
          'keepproportions' => 0,
          'reuse_crop_style' => '',
          'style_name' => 'ting_cover_large',
        ),
        'weight' => 0,
      ),
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
          'width' => 500,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: ting_cover_medium.
  $styles['ting_cover_medium'] = array(
    'name' => 'ting_cover_medium',
    'label' => 'Ting cover medium',
    'effects' => array(
      5 => array(
        'label' => 'Manual Crop: Custom crop',
        'help' => 'Crop a freely user-selected area.',
        'effect callback' => 'manualcrop_crop_effect',
        'form callback' => 'manualcrop_crop_form',
        'summary theme' => 'manualcrop_crop_summary',
        'module' => 'manualcrop',
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 260,
          'height' => '',
          'keepproportions' => 0,
          'reuse_crop_style' => '',
          'style_name' => 'ting_cover_medium',
        ),
        'weight' => 0,
      ),
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
          'width' => 260,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: ting_cover_small.
  $styles['ting_cover_small'] = array(
    'name' => 'ting_cover_small',
    'label' => 'Ting cover small',
    'effects' => array(
      3 => array(
        'label' => 'Manual Crop: Custom crop',
        'help' => 'Crop a freely user-selected area.',
        'effect callback' => 'manualcrop_crop_effect',
        'form callback' => 'manualcrop_crop_form',
        'summary theme' => 'manualcrop_crop_summary',
        'module' => 'manualcrop',
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 180,
          'height' => '',
          'keepproportions' => 0,
          'reuse_crop_style' => '',
          'style_name' => 'ting_cover_small',
        ),
        'weight' => 0,
      ),
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
          'width' => 180,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: ting_cover_mini.
  $styles['ting_cover_mini'] = array(
    'name' => 'ting_cover_mini',
    'label' => 'Ting cover mini',
    'effects' => array(
      1 => array(
        'label' => 'Manual Crop: Custom crop',
        'help' => 'Crop a freely user-selected area.',
        'effect callback' => 'manualcrop_crop_effect',
        'form callback' => 'manualcrop_crop_form',
        'summary theme' => 'manualcrop_crop_summary',
        'module' => 'manualcrop',
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 100,
          'height' => '',
          'keepproportions' => 0,
          'reuse_crop_style' => '',
          'style_name' => 'ting_cover_mini',
        ),
        'weight' => 0,
      ),
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 100,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
